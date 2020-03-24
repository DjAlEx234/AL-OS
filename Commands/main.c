#include <stddef.h>
#include <stdint.h>
#include "terminal.h"
#include "keyboard.h"
int string_len(const char* string)
{
	int len = 0;
	while (string[len])
		len++;
	if (string[0] == 0)
		return len - 1;
	return len;
}
void command_key_in(char c)
{
  printc(c, char_color(5, 0));
}
void command_loop()
{
	keyboard_set_reciever(command_key_in);
	while (1);
}
