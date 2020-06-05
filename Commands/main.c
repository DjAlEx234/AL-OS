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
int tolower(int a)
{
	if (a >= 'A' && 'Z' <= a)
		return ('a' - a + 'A');
	return a;
}
char buff[100];
int bufi = 0;
void command_run(char new[25][25])
{
	if (checkstring(new[0], "about"))
		prints("AL-OS Version 0.0.4\nStage Pre-Alpha\n", 9, 0);
	else if (checkstring(new[0], "cls"))
		terminal_clear(0);
	else if (checkstring(new[0], "help"))
		prints("about - about AL-OS\ncls - clears the screen\nhelp - lists all commands\n", 9, 0);
	else
	{
		printc('\"', 8, 0);
		prints(new[0], 12, 0);
		printc('\"', 8, 0);
		prints(" is not a valid command. Try using \"help\" to find valid commands.\n", 9, 0);
	}
}
void command_parse()
{
	char new[25][25];
	int r = 0, c = 0;
	for (int a = 0; a <= bufi; a++)
	{
		if (buff[a] == ' ' || buff[a] == '\n')
		{
			new[r][c] = '\0';
			r++;
			c = 0;
		}
		else
		{
			new[r][c] = buff[a];
			c++;
		}
	}
	command_run(new);
	prints("al-os>", 5, 0);
	bufi = 0;
}
void command_key_in(struct modifiers mods)
{
	if (mods.final_key == 0)
		return;
	if (mods.final_key == '\b')
	{
		if (bufi == 0)
			return;
		buff[bufi] = 0;
		bufi--;
		printc('\b', 2, 0);
		return;
	}
	printc(mods.final_key, 2, 0);
	if (mods.final_key >= 'A' && mods.final_key <= 'Z')
		buff[bufi] = mods.prekey;
	else
		buff[bufi] = mods.final_key;
	if (bufi != 100)
		bufi++;
	if (mods.prekey == '\n')
		command_parse();
}
void command_loop()
{
	keyboard_set_reciever(command_key_in);
	prints("al-os>", 5, 0);
	while (1);
}
