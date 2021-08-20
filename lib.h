
#ifndef __LIB_H__
#define __LIB_H__

#include <sys/errno.h>

/* SBI Extension IDs */
#define SBI_EXT_0_1_CONSOLE_PUTCHAR             0x1

int sbi_ecall(int ext, unsigned long arg0);

void xxk_putchar(char c);
void xxk_print(char *s);
void xxk_print_hex(unsigned int num);

#endif /* #ifndef __LIB_H__ */
