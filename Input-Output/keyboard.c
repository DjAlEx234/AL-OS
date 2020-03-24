#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include "asm-io.h"
#include "keyboard.h"
#include "interrupt.h"
#include "terminal.h"
#include "main.h"
unsigned char keyboard[224] =
{
    0,  27,
    '1', '2', '3', '4', '5', '6', '7', '8',	'9', '0', '-', '=',
    '\b',
    '\t',
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
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	//F1 to F10
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
    0,	//Others set to 0
};
void *keyboard_reciever;
char key;
void keyboard_call(struct modifiers mod)
{
  void (*run)(struct modifiers mods) = keyboard_reciever;
  run(mod);
}
bool control;
bool alt;
bool shift;
bool caps = false;
void keyboard_handler(__attribute__((unused)) struct regs *r)
{
  unsigned char scancode;
  scancode = inb(0x60);
  if (scancode == 0x3A)
    caps = !caps;
  if ((scancode == 0x2A) || (scancode == 0x36))
    shift = true;
  else if ((scancode == 0xAA) || (scancode == 0xB6))
    shift = false;
  if (scancode == 0x1D)
    control = true;
  else if (scancode == 0x9D)
    control = false;
  if (scancode == 0x38)
    alt = true;
  else if (scancode == 0xB8)
    alt = false;
  bool uppercase = true;
  if (shift == caps)
    uppercase = false;
  key = keyboard[scancode];
  if (uppercase)
    if (key >= 'a' && key <= 'z')
      key = key - ('a' - 'A');
  struct modifiers send;
  send.control = control;
  send.alt = alt;
  send.shift = shift;
  send.caps = caps;
  send.final_key = key;
  keyboard_call(send);
}
void keyboard_set_reciever(void* reciever)
{
  keyboard_reciever = reciever;
}
void keyboard_init()
{
  irq_install_handler(1, keyboard_handler);
}
