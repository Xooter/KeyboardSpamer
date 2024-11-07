#include "keyboard.c"
#include "keys.c"
#include <stdio.h>
#include <stdlib.h>

int searchCode(char c) {
  for (int k = 0; k < sizeof(keys) / sizeof(*keys); k++) {
    if (c == keys[k].name[0]) {
      return keys[k].code;
    }
  }
  return -1;
}

int main(int argc, char *argv[]) {
  init();

  int NUMBER_OF_SPAMS = 1;
  int delay;
  char *spam = "BESOS HOLA  QUE TAL";

  // scanf("Cuantos loops?: %d", &NUMBER_OF_SPAMS);

  // sleep(2);
  for (int i = 0; i < NUMBER_OF_SPAMS; i++) {
    push(KEY_LEFTSHIFT);

    for (int j = 0; j < strlen(spam); j++) {
      int code = searchCode(spam[j]);
      if (code != -1) {
        pushRelease(code);
      }

      release(KEY_LEFTSHIFT);
      pushRelease(KEY_ENTER);

      delay = rand() % 2 + 1;
      sleep(delay);

      refresh();
    }

    close_device();
    return 0;
  }
}
