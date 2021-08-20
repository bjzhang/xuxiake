
#include "lib.h"

int sbi_ecall(int ext, unsigned long arg0)
{
	int ret;

        register unsigned long a0 asm ("a0") = (unsigned long)(arg0);
        register unsigned long a7 asm ("a7") = ext;
        asm volatile ("ecall"
                      : "+r" (a0)
                      : "r" (a7)
                      : "memory");
        ret = a0;

        return ret;
}

void xxk_putchar(char c)
{
	sbi_ecall(SBI_EXT_0_1_CONSOLE_PUTCHAR, c);
}

void xxk_print(char *s)
{
	while(*s)
		xxk_putchar(*s++);
}

void xxk_print_hex(unsigned int num)
{
	int i;
	int n;
	char c;

	xxk_print("0x");
	for (i = (sizeof(num) * 8) - 4; i >= 0; i-=4) {
		n = (num >> i & 0xf);
		if (n >= 0 && n <= 9)
			xxk_putchar(n + '0');
		else if (n >= 0xa && n <= 0xf)
			xxk_putchar(n - 0xa + 'a');
		else
			xxk_putchar(' ');

	}
}

