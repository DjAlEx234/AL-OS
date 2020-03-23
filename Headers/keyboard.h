#ifndef keyboardh
#define keyboardh
void keyboard_init();
void keyboard_reciever_add(void (*reciever)(char c));
void keyboard_reciever_remove();
#endif
