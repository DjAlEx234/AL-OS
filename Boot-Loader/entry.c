#include "interrupt.h"
#include "terminal.h"
void entry(void)
{
  terminal_init();
  interrupt_install();
  //keyboard install
  prints("AL-OS\nVersion 0.0.1\nStage Alpha", 7, 0);
  //leave to main programming loop
  error_handler("\nEnded loop, check possible exits!");
  asm("cli");
  while (1);
}
