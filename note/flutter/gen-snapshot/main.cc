// Copyright 2018 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <dlfcn.h>
#include <linux/limits.h>
#include <string.h>
#include <unistd.h>

#include <EGL/egl.h>
#include <EGL/fbdev_window.h>
#include <GLES2/gl2.h>

#include <iostream>
#include <thread>
#include <vector>

#include "flutter_sita.h"

static_assert(FLUTTER_ENGINE_VERSION == 1, "");

FlutterEngine engine;

fbdev_window *window_ = nullptr;
EGLDisplay display_ = EGL_NO_DISPLAY;
EGLConfig config_;
EGLContext context_ = EGL_NO_CONTEXT;
EGLSurface surface_ = EGL_NO_SURFACE;

static bool FlutterInit() {
  display_ = eglGetDisplay(EGL_DEFAULT_DISPLAY);
  if (EGL_NO_DISPLAY == display_) {
    std::cerr << __FUNCTION__ << " failed at "
              << __LINE__ << std::endl;
    eglGetError();
    return false;
  }

  eglInitialize(display_, NULL, NULL);

  const EGLint attribute_list[] = {
    EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
    EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
    EGL_RED_SIZE, 8,
    EGL_GREEN_SIZE, 8,
    EGL_BLUE_SIZE, 8,
    EGL_ALPHA_SIZE, 8,
    EGL_DEPTH_SIZE, 0,
    EGL_STENCIL_SIZE, 0,
    EGL_NONE,
  };
  EGLint num_configs;
  eglChooseConfig(display_, attribute_list, &config_, 1, &num_configs);

  const EGLint context_attrib_list[] = {
    EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE,
  };
  context_ = eglCreateContext(display_, config_, EGL_NO_CONTEXT, context_attrib_list);
  if (EGL_NO_CONTEXT == context_) {
    std::cerr << __FUNCTION__ << " failed at "
              << __LINE__ << std::endl;
    eglGetError();
    return false;
  }

  return true;
}

void FlutterWindowLoop() {
  int i = 0;
  while (i < 10) {
    sleep(3);
    i++;
    std::cout << __FUNCTION__ << ", i=" << i << std::endl;
    // TODO(awdavies): This will be deprecated soon.
    __FlutterEngineFlushPendingTasksNow();
  }
  FlutterEngineShutdown(engine);
}

static void FlutterTerminate() {
  eglMakeCurrent(display_, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
  eglDestroyContext(display_, context_);
  eglDestroySurface(display_, surface_);
  eglTerminate(display_);
  free(window_);
}

static void GLFWFramebufferSizeCallback(int width_px, int height_px) {
  FlutterWindowMetricsEvent event = {};
  event.struct_size = sizeof(event);
  event.width = width_px;
  event.height = height_px;
  event.pixel_ratio = 1.0f;
  FlutterEngineSendWindowMetricsEvent(engine, &event);
}

static void GLFWOnFlutterPlatformMessage(const FlutterPlatformMessage *message,
                                         void *user_data) {
  if (message->struct_size != sizeof(FlutterPlatformMessage)) {
    std::cerr << "Invalid message size received. Expected: "
              << sizeof(FlutterPlatformMessage) << " but received "
              << message->struct_size << std::endl;
    return;
  }
}

static bool GLFWMakeContextCurrent(void *user_data) {
  std::cout << __FUNCTION__ << ", tid=" << std::this_thread::get_id() << std::endl;
  eglMakeCurrent(display_, surface_, surface_, context_);
  return true;
}

static bool GLFWClearContext(void *user_data) {
  std::cout << __FUNCTION__ << ", tid=" << std::this_thread::get_id() << std::endl;
  eglMakeCurrent(display_, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
  return true;
}

static bool GLFWPresent(void *user_data) {
  std::cout << __FUNCTION__ << ", tid=" << std::this_thread::get_id() << std::endl;
  eglSwapBuffers(display_, surface_);
  return true;
}

static uint32_t GLFWGetActiveFbo(void *user_data) { return 0; }

// Clears the GLFW window to Material Blue-Grey.
//
// This function is primarily to fix an issue when the Flutter Engine is
// spinning up, wherein artifacts of existing windows are rendered onto the
// canvas for a few moments.
//
// This function isn't necessary, but makes starting the window much easier on
// the eyes.
static void GLFWClearCanvas() {
  eglMakeCurrent(display_, surface_, surface_, context_);
  // This color is Material Blue Grey.
  glClearColor(0.0 / 255.0, 0.0 / 255.0, 255.0 / 255.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);
  glFlush();
  eglSwapBuffers(display_, surface_);
  eglMakeCurrent(display_, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
}

// Resolves the address of the specified OpenGL or OpenGL ES
// core or extension function, if it is supported by the current context.
static void *GLFWProcResolver(void *user_data, const char *name) {
  static void* egl_lib = nullptr;
  static void* gl_lib = nullptr;

  void* proc = (void*)eglGetProcAddress(name);
  if (!proc) {
    if (!egl_lib) {
      egl_lib = dlopen("libEGL.so", RTLD_LAZY);
      if (dlerror())
	std::cerr << "dlopen libEGL.so failed";
    }

    if (!gl_lib) {
      gl_lib = dlopen("libGLESv2.so", RTLD_LAZY);
      if (dlerror())
	std::cerr << "dlopen libGLESv2.so failed";
    }

    if (0 == strcmp("eglQuerySring", name))
      return (void*)eglQueryString;
    else if (0 == strcmp("eglGetCurrentDisplay", name))
      return (void*)eglGetCurrentDisplay;
    else {
      if (egl_lib) {
        proc = dlsym(egl_lib, name);
	if (proc)
	  return proc;
      }

      if (gl_lib) {
        proc = dlsym(gl_lib, name);
	if (proc)
	  return proc;
      }

      std::cerr << "can't find " << name << std::endl;
      return proc;
    }
  }
  return proc;
}

// Spins up an instance of the Flutter Engine.
//
// This function launches the Flutter Engine in a background thread, supplying
// the necessary callbacks for rendering within a GLFWwindow.
//
// Returns a caller-owned pointer to the engine.
static FlutterEngine RunFlutterEngine(
    fbdev_window *window, const std::string &main_path,
    const std::string &assets_path, const std::string &packages_path,
    const std::string &icu_data_path,
    const std::vector<std::string> &arguments) {
  std::vector<const char *> argv;
  for (auto iter = arguments.begin(); iter != arguments.end(); iter++)
    argv.push_back(iter->c_str());
  /*std::transform(
      arguments.begin(), arguments.end(), std::back_inserter(argv),
      [](const std::string &arg) -> const char * { return arg.c_str(); });*/

  FlutterRendererConfig config = {};
  config.type = kOpenGL;
  config.open_gl.struct_size = sizeof(config.open_gl);
  config.open_gl.make_current = GLFWMakeContextCurrent;
  config.open_gl.clear_current = GLFWClearContext;
  config.open_gl.present = GLFWPresent;
  config.open_gl.fbo_callback = GLFWGetActiveFbo;
  config.open_gl.gl_proc_resolver = GLFWProcResolver;
  FlutterProjectArgs args = {};
  args.struct_size = sizeof(FlutterProjectArgs);
  args.assets_path = assets_path.c_str();
  args.main_path = main_path.c_str();
  args.packages_path = packages_path.c_str();
  args.icu_data_path = icu_data_path.c_str();
  args.command_line_argc = argv.size();
  args.command_line_argv = &argv[0];
  args.platform_message_callback = GLFWOnFlutterPlatformMessage;
  engine = nullptr;
  auto result =
      FlutterEngineRun(FLUTTER_ENGINE_VERSION, &config, &args, window, &engine);
  if (result != kSuccess || engine == nullptr) {
    return nullptr;
  }
  return engine;
}


void *CreateFlutterWindow(size_t initial_width, size_t initial_height,
                                const std::string &main_path,
                                const std::string &assets_path,
                                const std::string &packages_path,
                                const std::string &icu_data_path,
                                const std::vector<std::string> &arguments) {
  const EGLint surface_attrib_list[] = {
    EGL_NONE,
  };
  surface_ = eglCreateWindowSurface(display_, config_,
      reinterpret_cast<EGLNativeWindowType>(window_), surface_attrib_list);
  if (EGL_NO_SURFACE == surface_) {
    std::cerr << __FUNCTION__ << " failed at "
              << __LINE__ << std::endl;
    eglGetError();
    return nullptr;
  }

  GLFWClearCanvas();
  auto engine = RunFlutterEngine(window_, main_path, assets_path, packages_path,
                                 icu_data_path, arguments);
  if (engine == nullptr) {
    return nullptr;
  }

  GLFWFramebufferSizeCallback(initial_width, initial_height);
  return window_;
}

void *CreateFlutterWindowInSnapshotMode(
    size_t initial_width, size_t initial_height, const std::string &assets_path,
    const std::string &icu_data_path,
    const std::vector<std::string> &arguments) {
  return CreateFlutterWindow(initial_width, initial_height, "", assets_path, "",
                             icu_data_path, arguments);
}

namespace {

// Returns the path of the directory containing this executable, or an empty
// string if the directory cannot be found.
std::string GetExecutableDirectory() {
  char buffer[PATH_MAX + 1];
  ssize_t length = readlink("/proc/self/exe", buffer, sizeof(buffer));
  if (length > PATH_MAX) {
    std::cerr << "Couldn't locate executable" << std::endl;
    return "";
  }
  std::string executable_path(buffer, length);
  size_t last_separator_position = executable_path.find_last_of('/');
  if (last_separator_position == std::string::npos) {
    std::cerr << "Unabled to find parent directory of " << executable_path
              << std::endl;
    return "";
  }
  return executable_path.substr(0, last_separator_position);
}

}  // namespace

int main(int argc, char **argv) {
  std::cout << __FUNCTION__ << ", tid=" << std::this_thread::get_id() << std::endl;
  int initial_width = 1280;
  int initial_height = 720;
  window_ = (fbdev_window*)malloc(sizeof(fbdev_window));
  window_->width = initial_width;
  window_->height = initial_height;
  if (!FlutterInit()) {
    std::cerr << "Couldn't init egl" << std::endl;
  }

  // Resources are located relative to the executable.
  std::string base_directory = GetExecutableDirectory();
  if (base_directory.empty()) {
    base_directory = ".";
  }
  std::string data_directory = base_directory + "/data";
  std::string assets_path = data_directory + "/flutter_assets";
  std::string icu_data_path = data_directory + "/icudtl.dat";

  // Arguments for the Flutter Engine.
  std::vector<std::string> arguments;
  // First argument is argv[0] since the engine is expecting real command line
  // args.
  arguments.push_back(argv[0]);
#ifdef NDEBUG
  arguments.push_back("--disable-dart-asserts");
#endif
  // Start the engine.
  auto window = CreateFlutterWindowInSnapshotMode(
      initial_width, initial_height, assets_path, icu_data_path, arguments);
  if (window == nullptr) {
    std::cerr << __FUNCTION__ << ", create window failed" << std::endl;
    FlutterTerminate();
    return EXIT_FAILURE;
  }

  FlutterWindowLoop();
  FlutterTerminate();
  return EXIT_SUCCESS;
}
