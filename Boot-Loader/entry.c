#include "interrupt.h"
#include "terminal.h"
#include "keyboard.h"
#include "main.h"
void entry(void)
{
  interrupt_install();
  terminal_init();
  keyboard_init();
  command_loop();
  error_handler("\nEnded loop, check possible exits!");
  while (1);
}
