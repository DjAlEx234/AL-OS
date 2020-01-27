#include <stdint.h>
#include <stddef.h>
#include "terminal.h"
#include "asm-io.h"
void disable_cursor()//imported function from AlexOS
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
void printc(char c, int color, int x, int y)
{
  video_mem[y * width + x] = char_entry(c, color);
}
void terminal_init(void)
{
  disable_cursor();
  row = 0;
  column = 0;
  video_mem = (uint16_t*)0xB8000;
  for (int y = 0; y < height; y++){
    for (int x = 0; x < width; x++){
      int spot = y * width + x;
      video_mem[spot] = char_entry(' ', char_color(7, 0));
    }
  }
}
