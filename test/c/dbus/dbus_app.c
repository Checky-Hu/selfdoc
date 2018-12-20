#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <dbus/dbus.h>

#define DBUS_SENDER_BUS_NAME       "com.checky.sender"

#define DBUS_RECEIVER_BUS_NAME     "com.checky.receiver"
#define DBUS_RECEIVER_PATH         "/com/checky/object"

#define DBUS_RECEIVER_INTERFACE    "com.checky.interface"
// Pass among sender and receiver to match each other.
#define DBUS_RECEIVER_SIGNAL       "SIGNAL"
#define DBUS_RECEIVER_METHOD       "METHOD"

#define DBUS_RECEIVER_SIGNAL_RULE  "type='signal',interface='%s'"
#define DBUS_RECEIVER_REPLY_STR    "i am %d, get a message"

enum run_mode {MODE_SIGNAL, MODE_METHOD};

void reply_method_call(DBusMessage* msg, DBusConnection* conn)
{
  DBusMessage* reply;
  DBusMessageIter reply_arg;
  DBusMessageIter msg_arg;
  dbus_uint32_t serial = 0;

  pid_t pid;
  char reply_str[128];
  void* __value;
  char* __value_str;
  int __value_int;

  int ret;

  pid = getpid();

  // Create message reply
  reply = dbus_message_new_method_return(msg);
  if (!reply) {
    printf("Out of Memory!\n");
    return;
  }

  // Set parameters of message reply
  snprintf(reply_str, sizeof(reply_str), DBUS_RECEIVER_REPLY_STR, pid);
  __value_str = reply_str;
  __value = &__value_str;

  dbus_message_iter_init_append(reply, &reply_arg);
  if (!dbus_message_iter_append_basic(&reply_arg, DBUS_TYPE_STRING, __value)) {
    printf("Out of Memory!\n");
    goto out;
  }

  // Get parameters from message and consider whether append return values
  if (!dbus_message_iter_init(msg, &msg_arg)) {
    printf("Message has NO Argument\n");
    goto out;
  }

  do {
    ret = dbus_message_iter_get_arg_type(&msg_arg);
    if (DBUS_TYPE_STRING == ret) {
      dbus_message_iter_get_basic(&msg_arg, &__value_str);
      printf("I am %d, get Method Argument STRING: %s\n", pid, __value_str);

      __value = &__value_str;
      if (!dbus_message_iter_append_basic(&reply_arg, DBUS_TYPE_STRING, __value)) {
        printf("Out of Memory!\n");
        goto out;
      }
    } else if (DBUS_TYPE_INT32 == ret) {
      dbus_message_iter_get_basic(&msg_arg, &__value_int);
      printf("I am %d, get Method Argument INT32: %d\n", pid, __value_int);

      __value_int++;
      __value = &__value_int;
      if (!dbus_message_iter_append_basic(&reply_arg, DBUS_TYPE_INT32, __value)) {
        printf("Out of Memory!\n");
        goto out;
      }
    } else
      printf("Arguement Type ERROR!\n");
  } while (dbus_message_iter_next(&msg_arg));

  // Send reply message
  if (!dbus_connection_send(conn, reply, &serial)) {
    printf("Out of Memory!\n");
    goto out;
  }

  dbus_connection_flush(conn);
out:
  dbus_message_unref(reply);
}

void receive_from_dbus()
{
  DBusMessage* msg;
  DBusMessageIter arg;
  DBusConnection* connection;
  DBusError err;

  pid_t pid;
  char name[64];
  char rule[128];

  const char* path;
  char* __value_str;
  int __value_int;

  int ret;

  pid = getpid();

  dbus_error_init(&err);
  // Create session D-Bus connection
  connection = dbus_bus_get(DBUS_BUS_SESSION, &err);
  if (!connection) {
    if (dbus_error_is_set(&err))
      printf("Connection Error %s\n", err.message);

    goto out;
  }

  // Set BUS name
  snprintf(name, sizeof(name), "%s.%d", DBUS_RECEIVER_BUS_NAME, pid);
  printf("I am a receiver, PID = %d, name = %s\n", pid, name);

  ret = dbus_bus_request_name(connection, name, DBUS_NAME_FLAG_REPLACE_EXISTING, &err);
  if (ret != DBUS_REQUEST_NAME_REPLY_PRIMARY_OWNER) {
    if (dbus_error_is_set(&err))
      printf("Name Error %s!\n", err.message);

    goto out;
  }

  // Listen to signals
  snprintf(rule, sizeof(rule), DBUS_RECEIVER_SIGNAL_RULE, DBUS_RECEIVER_INTERFACE);
  dbus_bus_add_match(connection, rule, &err);
  dbus_connection_flush(connection);
  if (dbus_error_is_set(&err)) {
    printf("Match Error %s\n", err.message);
    goto out;
  }

  while (1) {
    dbus_connection_read_write(connection, 0);

    msg = dbus_connection_pop_message(connection);
    if (msg == NULL) {
      sleep(1);
      continue;
    }

    path = dbus_message_get_path(msg);
    if (strcmp(path, DBUS_RECEIVER_PATH)) {
      printf("Wrong PATH: %s\n", path);
      goto next;
    }

    printf("Get a Message\n");
    if (dbus_message_is_signal(msg, DBUS_RECEIVER_INTERFACE, DBUS_RECEIVER_SIGNAL)) {
      printf("Someone Send me a Signal\n");
      if (!dbus_message_iter_init(msg, &arg)) {
        printf("Message Has no Argument\n");
        goto next;
      }

      ret = dbus_message_iter_get_arg_type(&arg);
      if (DBUS_TYPE_STRING == ret) {
        dbus_message_iter_get_basic(&arg, &__value_str);
        printf("I am %d, Got Signal with STRING: %s\n", pid, __value_str);
      } else if (DBUS_TYPE_INT32 == ret) {
        dbus_message_iter_get_basic(&arg, &__value_int);
        printf("I am %d, Got Signal with INT32: %d\n", pid, __value_int);
      } else {
        printf("Argument Type ERROR\n");
        goto next;
      }
    } else if (dbus_message_is_method_call(msg, DBUS_RECEIVER_INTERFACE, DBUS_RECEIVER_METHOD)) {
      printf("Somenone Call My Method\n");
      reply_method_call(msg, connection);
    } else
      printf("NOT a Signal OR a Method\n");

next:
    dbus_message_unref(msg);
  }

out:
  dbus_error_free(&err);
}

void send_to_dbus(enum run_mode mode, char* type, void* value)
{
  DBusConnection* connection;
  DBusError err;
  DBusMessage* msg;
  DBusMessageIter arg;
  DBusPendingCall* pending;
  dbus_uint32_t serial;

  int __type;
  void* __value;
  char* __value_str;
  int __value_int;
  pid_t pid;
  int ret;

  pid = getpid();

  dbus_error_init(&err);

  // Connect to Bus
  connection = dbus_bus_get(DBUS_BUS_SESSION, &err);
  if (!connection) {
    if (dbus_error_is_set(&err))
      printf("Connection Err : %s\n", err.message);

    goto out1;
  }

  // Set Bus name
  ret = dbus_bus_request_name(connection, DBUS_SENDER_BUS_NAME, DBUS_NAME_FLAG_REPLACE_EXISTING, &err);
  if (DBUS_REQUEST_NAME_REPLY_PRIMARY_OWNER != ret) {
    if (dbus_error_is_set(&err))
      printf("Name Err : %s\n", err.message);

    goto out1;
  }

  if (!strcasecmp(type, "STRING")) {
    __type = DBUS_TYPE_STRING;
    __value_str = value;
    __value = &__value_str;
  } else if (!strcasecmp(type, "INT32")) {
    __type = DBUS_TYPE_INT32;
    __value_int = atoi(value);
    __value = &__value_int;
  } else {
    printf("Wrong Argument Type\n");
    goto out1;
  }

  if (mode == MODE_METHOD) {
    printf("call app[bus_name]=%s, object[path]=%s, interface=%s, method=%s\n",
        DBUS_RECEIVER_BUS_NAME, DBUS_RECEIVER_PATH,
        DBUS_RECEIVER_INTERFACE, DBUS_RECEIVER_METHOD);

    // Create a messge to invoke a method on a remote object
    msg = dbus_message_new_method_call(DBUS_RECEIVER_BUS_NAME, DBUS_RECEIVER_PATH,
        DBUS_RECEIVER_INTERFACE, DBUS_RECEIVER_METHOD);
    if (msg == NULL) {
      printf("Message NULL");
      goto out2;
    }

    dbus_message_iter_init_append(msg, &arg);
    if (!dbus_message_iter_append_basic(&arg, __type, __value)) {
      printf("Out of Memory!\n");
      goto out2;
    }

    if (!dbus_connection_send_with_reply(connection, msg, &pending, -1)) {
      printf("Out of Memory!\n");
      goto out2;
    }

    if (pending == NULL) {
      printf("Pending Call NULL: connection is disconnected\n");
      goto out2;
    }

    dbus_connection_flush(connection);
    dbus_message_unref(msg);

    // Block until the pending call is completed
    dbus_pending_call_block(pending);
    msg = dbus_pending_call_steal_reply(pending);
    if (msg == NULL) {
      printf("Reply NULL\n");
      goto out1;
    }

    dbus_pending_call_unref(pending);

    // Read the arguments
    if (!dbus_message_iter_init(msg, &arg)) {
      printf("Message had no Argument!\n");
      goto out2;
    }

    do {
      ret = dbus_message_iter_get_arg_type(&arg);
      if (DBUS_TYPE_STRING == ret) {
        dbus_message_iter_get_basic(&arg, &__value_str);
        printf("I am %d, get Method return STRING: %s\n", pid, __value_str);
      } else if (DBUS_TYPE_INT32 == ret) {
        dbus_message_iter_get_basic(&arg, &__value_int);
        printf("I am %d, get Method return INT32: %d\n", pid, __value_int);
      } else
        printf("Argument Type ERROR\n");
    } while (dbus_message_iter_next(&arg));

    printf("NO More Argument\n");
  } else if (mode == MODE_SIGNAL) {
    printf("Signal to object[path]=%s, interface=%s, signal=%s\n", DBUS_RECEIVER_PATH,
        DBUS_RECEIVER_INTERFACE, DBUS_RECEIVER_SIGNAL);

    // Send a signal
    msg = dbus_message_new_signal(DBUS_RECEIVER_PATH, DBUS_RECEIVER_INTERFACE, DBUS_RECEIVER_SIGNAL);
    if (!msg) {
      printf("Message NULL\n");
      goto out1;
    }

    dbus_message_iter_init_append(msg, &arg);
    if (!dbus_message_iter_append_basic(&arg, __type, __value)) {
      printf("Out of Memory!\n");
      goto out2;
    }

    if (!dbus_connection_send(connection, msg, &serial)) {
      printf("Out of Memory!\n");
      goto out2;
    }

    dbus_connection_flush(connection);
    printf("Signal Send\n");
  }

out2:
  dbus_message_unref(msg);
out1:
  dbus_error_free(&err);
}

void usage()
{
#define USAGE "usage: ./dbus_app [send | receive] <param>\n" \
  "  receive -- listen, wait a signal or a method call\n" \
  "    if you want to test signal broadcast, run many receivers as your wish\n" \
  "  send [mode][type][value] -- send a signal or call a method\n" \
  "    mode -- SIGNAL | METHOD\n" \
  "    type -- STRING | INT32\n" \
  "    value -- string or number\n" \
  "example:\n" \
  "./dbus_app send SIGNAL STRING hello\n" \
  "./dbus_app send METHOD INT32 123\n"

  printf(USAGE);
}

int main(int argc, char ** argv)
{
  if (argc < 2) {
    usage();
    return -1;
  }

  if (!strcmp(argv[1], "receive")) {
    receive_from_dbus();
  } else if (!strcmp(argv[1], "send")) {
    if (argc < 5) {
      usage();
      return -1;
    } else {
      if (!strcasecmp(argv[2], DBUS_RECEIVER_SIGNAL))
        send_to_dbus(MODE_SIGNAL, argv[3], argv[4]);
      else if (!strcasecmp(argv[2], DBUS_RECEIVER_METHOD))
        send_to_dbus(MODE_METHOD, argv[3], argv[4]);
      else
        usage();
    }
  } else
    usage();

  return 0;
}
