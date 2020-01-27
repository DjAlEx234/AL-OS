#include "interrupt.h"
#include "terminal.h"
void entry(void)
{
  terminal_init();
  interrupt_install();
  //keyboard install
  //boot screen
  //leave to main programming loop
  //add ended loop catch
}
