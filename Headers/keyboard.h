#ifndef keyboardh
#include <stdbool.h>
#define keyboardh
void keyboard_init();
void keyboard_set_reciever(void* reciever);
struct modifiers;
struct modifiers
{
  bool control, alt, shift, caps;
  char final_key;
};
#endif
