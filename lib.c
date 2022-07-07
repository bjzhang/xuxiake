
#include "lib.h"

void xxk_print(char *s)
{
	while(*s)
		xxk_putchar(*s++);
}

void xxk_print_hex(unsigned int num)
{
	int i;
	int n;

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

