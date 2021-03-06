#include <stdint.h>
#include <stddef.h>
#include "asm-io.h"
#include "terminal.h"
#include "main.h"
void disable_cursor()
{
	outb(0x3D4, 0x0A);
	outb(0x3D5, 0x20);
}
uint16_t* video_mem;
int row, column;
static const int width = 80;
static const int height = 25;
uint16_t char_entry(unsigned char c, uint8_t color)
{
  return (uint16_t) c | (uint16_t) color << 8;
}
uint8_t char_color(enum color_list fg, enum color_list bg)
{
  return fg | bg << 4;
}
int terminal_get_row()
{
	return row;
}
int terminal_get_column()
{
	return column;
}
void terminal_set(int r, int c)
{
	row = r;
	column = c;
}
void terminal_scroll()
{
	for (int num1 = 0; num1 < height; num1++)
		for (int num2 = 0; num2 < width; num2++)
			video_mem[num1 * width + num2] = video_mem[(num1 + 1) * width + num2];
}
void terminal_clear(enum color_list bg)
{
	for (int y = 0; y < height; y++)
		for (int x = 0; x < width; x++)
			video_mem[y * width + x] = char_entry('\0', char_color(0, bg));
	row = 0;
	column = 0;
}
void printc(char c, enum color_list fg, enum color_list bg)
{
	if (c == '\b')
	{
		column--;
		video_mem[row * width + column] = char_entry(0, char_color(fg, bg));
		return;
	}
	if (c == '\0')
		return;
	else if (c == '\n')
	{
		int left = 80 - column - 1;
		for (int i = 0; i != left; i++)
			printc(' ', 0, 0);
	}
	else if (c != '\n')
		video_mem[row * width + column] = char_entry(c, char_color(fg, bg));
	if (++column == width)
	{
		column = 0;
		if (++row == height)
		{
			terminal_scroll();
			row = 24;
		}
	}
}
void prints(char* s, enum color_list fg, enum color_list bg)
{
	for (int i = 0; i < string_len(s); i++)
		printc(s[i], fg, bg);
}
void terminal_init(void)
{
	disable_cursor();
	video_mem = (uint16_t*)0xB8000;
	terminal_clear(0);
}
