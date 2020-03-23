#include <stddef.h>
#include <stdint.h>
#include "asm-io.h"
#include "keyboard.h"
#include "interrupt.h"
#include "terminal.h"
#include "main.h"
unsigned char keyboard_us[128] =
{
    0,  27,
    '1', '2', '3', '4', '5', '6', '7', '8',	'9', '0', '-', '=', '\b',	//Backspace
    '\t',	//Tab
    'q', 'w', 'e', 'r', 't', 'y',
    'u', 'i', 'o', 'p', '[', ']', '\n',	//Enter
    0,  //Control
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'',
    '`', 0,	//L-Shift
    '\\', 'z', 'x', 'c', 'v', 'b', 'n',
    'm', ',', '.', '/', 0,  //R-Shift
    '*',
    0,	//Alt
    ' ',
    0,  //Caps
    0,
    0,
    0, 0, 0, 0, 0, 0, 0, 0,	//F1 to F10
    0,  //Num Lock
    0,	//Scroll
    0,	//Home
    0,	//Up
    0,	//Page Up
    '-',
    0,	//Left
    0,
    0,	//Right
    '+',
    0,	//End
    0,	//Down
    0,	//Page Down
    0,	//Insert
    0,	//Delete
    0, 0, 0,
    0, 0,  //F11 to F12
    0,	//Other keys don't matter (yet)
};
void *keyboard_reciever;
char key;
void keyboard_call()
{
  void (*run)(char c) = keyboard_reciever;
  run(key);
}
void keyboard_handler(__attribute__((unused)) struct regs *r)
{
  unsigned char scancode;
  scancode = inb(0x60);
  key = keyboard_us[scancode];
  if (scancode & 0x80)//case for shift
  {

  }
  else
  {
    keyboard_call();
  }
}
void keyboard_init()
{
  irq_install_handler(1, keyboard_handler);
  keyboard_reciever = *command_key_in;
}
