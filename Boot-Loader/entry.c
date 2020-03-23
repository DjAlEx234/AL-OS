#include "interrupt.h"
#include "terminal.h"
#include "keyboard.h"
void entry(void)
{
  interrupt_install();
  terminal_init();
  keyboard_init();
  prints("AL-OS\nVersion 0.0.2\nStage Alpha\n", 7, 0);
  //enter main programming loop
  while (1) {}
  error_handler("\nEnded loop, check possible exits!");
  while (1);
}
