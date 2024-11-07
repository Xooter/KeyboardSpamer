#include <fcntl.h>
#include <limits.h>
#include <linux/input-event-codes.h>
#include <linux/input.h>
#include <linux/uinput.h>
#include <poll.h>
#include <stdbool.h>
#include <string.h>
#include <sys/time.h>
#include <termios.h>
#include <unistd.h>

int fd;
struct uinput_setup usetup;

void create_device() {
  memset(&usetup, 0, sizeof(usetup));
  usetup.id.bustype = BUS_USB;
  usetup.id.vendor = 0x1234;
  usetup.id.product = 0x5678;
  strcpy(usetup.name, "SPAMER");

  ioctl(fd, UI_DEV_SETUP, &usetup);
  ioctl(fd, UI_DEV_CREATE);
}

void close_device() {
  ioctl(fd, UI_DEV_DESTROY);
  close(fd);
}

void emit(const int fd, const int type, const int code, const int val) {
  struct input_event ie;

  ie.type = type;
  ie.code = code;
  ie.value = val;

  ie.time.tv_sec = 0;
  ie.time.tv_usec = 0;

  write(fd, &ie, sizeof(ie));
}

void push(const int code) { emit(fd, EV_KEY, code, 1); }

void release(const int code) { emit(fd, EV_KEY, code, 0); }

void pushRelease(const int code) {
  usleep(20 * 1000);
  push(code);
  release(code);
}

void refresh() { emit(fd, EV_SYN, SYN_REPORT, 0); }

void init() {
  fd = open("/dev/uinput", O_WRONLY | O_NONBLOCK);

  ioctl(fd, UI_SET_KEYBIT, KEY_1);
  ioctl(fd, UI_SET_KEYBIT, KEY_2);
  ioctl(fd, UI_SET_KEYBIT, KEY_3);
  ioctl(fd, UI_SET_KEYBIT, KEY_4);
  ioctl(fd, UI_SET_KEYBIT, KEY_5);
  ioctl(fd, UI_SET_KEYBIT, KEY_6);
  ioctl(fd, UI_SET_KEYBIT, KEY_7);
  ioctl(fd, UI_SET_KEYBIT, KEY_8);
  ioctl(fd, UI_SET_KEYBIT, KEY_9);
  ioctl(fd, UI_SET_KEYBIT, KEY_0);

  ioctl(fd, UI_SET_KEYBIT, KEY_A);
  ioctl(fd, UI_SET_KEYBIT, KEY_B);
  ioctl(fd, UI_SET_KEYBIT, KEY_C);
  ioctl(fd, UI_SET_KEYBIT, KEY_D);
  ioctl(fd, UI_SET_KEYBIT, KEY_E);
  ioctl(fd, UI_SET_KEYBIT, KEY_F);
  ioctl(fd, UI_SET_KEYBIT, KEY_G);
  ioctl(fd, UI_SET_KEYBIT, KEY_H);
  ioctl(fd, UI_SET_KEYBIT, KEY_I);
  ioctl(fd, UI_SET_KEYBIT, KEY_J);
  ioctl(fd, UI_SET_KEYBIT, KEY_K);
  ioctl(fd, UI_SET_KEYBIT, KEY_L);
  ioctl(fd, UI_SET_KEYBIT, KEY_M);
  ioctl(fd, UI_SET_KEYBIT, KEY_N);
  ioctl(fd, UI_SET_KEYBIT, KEY_O);
  ioctl(fd, UI_SET_KEYBIT, KEY_P);
  ioctl(fd, UI_SET_KEYBIT, KEY_Q);
  ioctl(fd, UI_SET_KEYBIT, KEY_R);
  ioctl(fd, UI_SET_KEYBIT, KEY_S);
  ioctl(fd, UI_SET_KEYBIT, KEY_T);
  ioctl(fd, UI_SET_KEYBIT, KEY_U);
  ioctl(fd, UI_SET_KEYBIT, KEY_V);
  ioctl(fd, UI_SET_KEYBIT, KEY_W);
  ioctl(fd, UI_SET_KEYBIT, KEY_X);
  ioctl(fd, UI_SET_KEYBIT, KEY_Y);
  ioctl(fd, UI_SET_KEYBIT, KEY_Z);

  ioctl(fd, UI_SET_KEYBIT, KEY_MINUS);
  ioctl(fd, UI_SET_KEYBIT, KEY_EQUAL);
  ioctl(fd, UI_SET_KEYBIT, KEY_LEFTBRACE);
  ioctl(fd, UI_SET_KEYBIT, KEY_RIGHTBRACE);
  ioctl(fd, UI_SET_KEYBIT, KEY_SEMICOLON);
  ioctl(fd, UI_SET_KEYBIT, KEY_APOSTROPHE);
  ioctl(fd, UI_SET_KEYBIT, KEY_GRAVE);
  ioctl(fd, UI_SET_KEYBIT, KEY_BACKSLASH);
  ioctl(fd, UI_SET_KEYBIT, KEY_COMMA);
  ioctl(fd, UI_SET_KEYBIT, KEY_DOT);
  ioctl(fd, UI_SET_KEYBIT, KEY_SLASH);
  ioctl(fd, UI_SET_KEYBIT, KEY_SPACE);
  ioctl(fd, UI_SET_KEYBIT, KEY_TAB);
  ioctl(fd, UI_SET_KEYBIT, KEY_ENTER);
  ioctl(fd, UI_SET_KEYBIT, KEY_BACKSPACE);
  ioctl(fd, UI_SET_KEYBIT, KEY_LEFTSHIFT);
  ioctl(fd, UI_SET_KEYBIT, KEY_SPACE);

  // Activación del evento de tecla
  ioctl(fd, UI_SET_EVBIT, EV_KEY);
  create_device();
}
