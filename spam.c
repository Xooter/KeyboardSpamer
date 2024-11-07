#include "keyboard.c"
#include "keys.c"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Key *searchCode(char *c) {
  for (int k = 1; k < sizeof(keys) / sizeof(*keys); k++) {
    if (*c == keys[k].name[0]) {
      return &keys[k];
    }
  }
  return NULL;
}

int main(int argc, char *argv[]) {
  if (argc != 3) {
    printf("Usage: %s <message> <times>\n", argv[0]);
    return 2;
  }

  sleep(2);

  char *spam = argv[1];
  int NUMBER_OF_SPAMS = strtol(argv[2], NULL, 10);

  init();

  const int message_length = strlen(spam);
  Key *message_codes[message_length];

  for (int j = 0; j < message_length; j++) {
    Key *key = searchCode(&spam[j]);
    if (key != NULL) {
      message_codes[j] = key;
    } else {
      printf("Warning: Character '%c' not found in keys, skipping.\n", spam[j]);
      message_codes[j] = 0;
    }
  }

  for (int i = 0; i < NUMBER_OF_SPAMS; i++) {
    for (int j = 0; j < message_length; j++) {
      if (message_codes[j] != 0) {
        if (isupper(*message_codes[j]->name)) {
          push(KEY_LEFTSHIFT);
        }

        pushRelease(message_codes[j]->code);

        if (isupper(*message_codes[j]->name)) {
          release(KEY_LEFTSHIFT);
        }
      }
    }

    pushRelease(KEY_ENTER);

    int delay = rand() % 3;
    sleep(delay);
    refresh();
  }

  close_device();
  return 0;
}
