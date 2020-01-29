#ifndef terminalh
#define terminalh
enum color_list;
enum color_list {
  Black = 0,
  Blue = 1,
  Green = 2,
  Cyan = 3,
  Red = 4,
  Magenta = 5,
  Brown = 6,
  Light_Gray = 7,
  Dark_Gray = 8,
  Light_Blue = 9,
  Light_Green = 10,
  Light_Cyan = 11,
  Light_Red = 12,
  Light_Magenta = 13,
  Light_Brown = 14,
  White = 15,
};
void terminal_init(void);
void terminal_set(int r, int c);
uint16_t char_entry(unsigned char c, uint8_t color);
uint8_t char_color(enum color_list fg, enum color_list bg);
void printc(char c, int color);
void prints(char* s, enum color_list fg, enum color_list bg);
int terminal_get_row();
int terminal_get_column();
#endif
