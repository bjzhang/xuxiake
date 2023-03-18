
#include <type.h>

static void __raw_writel(u32 val, volatile void *addr)
{
	asm volatile("str %w0, [%1]" : : "rZ" (val), "r" (addr));
}

void xxk_putchar(u8 c)
{
	void *dr = (void*)0x09000000;
	__raw_writel(c, dr);
}

