#ifndef asmioh
#include "../Input-Output/asm-io.c"
#define asmioh
static inline uint8_t inb(uint16_t port);
static inline void outb(uint16_t port, uint8_t val);
#endif
