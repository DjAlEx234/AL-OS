#include <stddef.h>
#include <stdint.h>
#include "terminal.h"
void command_key_in(char c)
{
  printc(c, char_color(2, 0));
}
