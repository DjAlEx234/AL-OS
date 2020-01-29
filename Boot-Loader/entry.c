#include "interrupt.h"
#include "terminal.h"
void entry(void)
{
  terminal_init();
  prints("AL-OS\nVersion 0.0.1\nStage Alpha", 7, 0);
  interrupt_install();
  //keyboard install
  //boot screen
  //leave to main programming loop
  //add ended loop catch
  asm("cli");
  while (1);
}
