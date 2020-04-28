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
bool checkstring(char a[], char b[])
{
	int c = string_len(b);
	for (int d = 0; d != c; d++)
	{
		if (a[d] != b[d])
			return false;
	}
	return true;
}
char buff[100];
int bufi = 0;
void command_run()
{
	char new[25][25];
	int b = 0, c = 0;
	for (int a = 0; a <= bufi; a++)
	{
		if (buff[a] == ' ' || buff[a] == '\n')
		{
			new[b][c] = '\0';
			b++;
			c = 0;
		}
		else
		{
			new[b][c] = buff[a];
			c++;
		}
	}
	prints(new[0], 9, 0);
	prints("\nal-os>", 5, 0);
	bufi = 0;
}
void command_key_in(struct modifiers mods)
{
	if (mods.final_key == 0)
		return;
	printc(mods.final_key, 2, 0);
	buff[bufi] = mods.final_key;
	if (bufi != 100)
		bufi++;
	if (mods.final_key == '\n')
		command_run();
}
void command_loop()
{
	keyboard_set_reciever(command_key_in);
	prints("al-os>", 5, 0);
	while (1);
}
