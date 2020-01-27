#ifndef interrupth
#include "asm-io.h"
#define interrupth
struct regs;
struct regs
{
	unsigned int gs, fs, es, ds;
	unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;
	unsigned int int_no, err_code;
	unsigned int eip, cs, eflags, useresp, ss;
};
void interrupt_install();
void irq_add_handler(int irq, void (*handler)(struct regs *r));
void irq_remove_handler(int irq);
void error_handler(char* errortext);
#endif
