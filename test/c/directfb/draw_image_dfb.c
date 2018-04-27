//No directfb porting files and lib to compile, so this example may have some problems.
#include <stdio.h>
#include <unistd.h>
#include "directfb.h"

#define DFT_W 1920
#define DFT_H 1080

void draw_by_dfb(int zindex, int main_w, int main_h, int sub_w, int sub_h, char* image_path)
{
  // Create dfb
  DirectFBInit((int*)0, (char***)NULL);
  IDirectFB* dfb = NULL;
  DirectFBCreate(&dfb);

  // Create layer
  IDirectFBDisplayLayer* layer = NULL;
  dfb->GetDisplayLayer(dfb, zindex, &layer);
  layer->SetCooperativeLevel(layer, DLSCL_ADMINISTRATIVE);

  // Set layer config
  DFBDisplayLayerConfig layer_config;
  layer_config.flags = (DFBDisplayLayerConfigFlags)(DLCONF_WIDTH | DLCONF_HEIGHT);
  layer_config.width = main_w;
  layer_config.height = main_h;
  layer->SetConfiguration(layer, &layer_config);

  // Create main surface
  IDirectFBSurface* main_surface = NULL;
  layer->GetSuface(layer, &main_surface);

  // Create sub surface
  IDirectFBSurface* sub_surface = NULL;
  DFBSufaceDescription dsc;
  dsc.flags = DSDESC_WIDTH | DSDESC_HEIGHT | DSDESC_PIXELFORMAT | DSDESC_CAPS;
  dsc.width = sub_w;
  dsc.height = sub_h;
  dsc.caps = DSCAPS_VIDEOONLY;
  dsc.pixelformat = DSPF_ARGB;
  dfb->CreateSurface(dfb, &dsc, &sub_surface);

  // Create dfb image
  IDirectFBImageProvider* img_provider = NULL;
  int ret = dfb->CreateImageProvider(dfb, image_path, &img_provider);
  if (ret != DFB_OK) {
    printf("create image error\n");
    return;
  }

  // Render image
  img_provider->RenderTo(img_provider, sub_surface, NULL);
  img_provider->Release(img_provider);
  main_surface->SetBlittingFlags(main_surface, (DFBSurfaceBlittingFlags)(DSBLIT_NOFX));
  if (main_w != sub_w) {
    DFBRectangle src_rect = {0, 0, sub_w, sub_h};
    DFBRectangle dst_rect = {0, 0, main_w, main_h};
    main_surface->StretchBlit(main_surface, sub_surface, &src_rect, &dst_rect);
  } else {
    main_surface->StretchBlit(main_surface, sub_surface, NULL, 0, 0);
  }
  main_surface->Flip(main_surface, NULL, DSFLIP_WAITFORSYNC);

  // Release resource
  sleep(10);
  sub_surface->Release(sub_surface);
  main_surface->Release(main_surface);
  dfb->Release(dfb);
}

int main(int argc, char ** argv)
{
  if (argc < 5) {
    printf("parameters:zindex main_w sub_w image_path\n");
    return -1;
  }

  int zindex = atoi(argv[1]);
  int main_w = atoi(argv[2]);
  int main_h = 720;
  if (main_w == DFT_W)
    main_h = DFT_H;
  int sub_w = atoi(argv[3]);
  int sub_h = 720;
  if (sub_w == DFT_W)
    sub_h = DFT_H;
  draw_by_dfb(zindex, main_w, main_h, sub_w, sub_h, argv[4]);
  return 0;
}
