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
char buffer[99];
int bufferindex = 0;
void command_run(char* cmd)
{
	for (int i = 0; i < bufferindex - 1; i++)
		printc(cmd[i], 9, 0);
	prints("\nal-os>", 5, 0);
}
void command_key_in(struct modifiers mods)
{
	printc(mods.final_key, 2, 0);
	buffer[bufferindex] = mods.final_key;
	if (bufferindex != 99)
		bufferindex++;
	if (mods.final_key == '\n')
	{
		command_run(buffer);
		bufferindex = 0;
		return;
	}
}
void command_loop()
{
	keyboard_set_reciever(command_key_in);
	prints("al-os>", 5, 0);
	while (1);
}
