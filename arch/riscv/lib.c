
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