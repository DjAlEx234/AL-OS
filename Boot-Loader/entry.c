#include "interrupt.h"
#include "terminal.h"
#include "keyboard.h"
#include "main.h"
void entry(void)
{
  interrupt_install();
  terminal_init();
  keyboard_init();
  prints("AL-OS\nVersion 0.0.3\nStage Pre-Alpha\n", 3, 0);
  command_loop();
  error_handler("\nEnded loop, check possible exits!");
  while (1);
}
