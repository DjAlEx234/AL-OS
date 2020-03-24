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
void command_key_in(struct modifiers mods)
{
	if (mods.control == 1)
		printc(mods.final_key, char_color(8, 0));
	else if (mods.alt == 1)
		printc(mods.final_key, char_color(7, 0));
	else if (mods.shift == 1)
		printc(mods.final_key, char_color(6, 0));
	else if (mods.caps == 1)
		printc(mods.final_key, char_color(5, 0));
	else
		printc(mods.final_key, char_color(2, 0));
}
void command_loop()
{
	keyboard_set_reciever(command_key_in);
	while (1);
}
