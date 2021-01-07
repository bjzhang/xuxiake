
/* SBI Extension IDs */
#define SBI_EXT_0_1_CONSOLE_PUTCHAR             0x1

/* CSR definition */
#define CSR_STVEC                       0x105
#define CSR_MEPC                        0x341

#define csr_write(csr, val)                                        \
        ({                                                         \
                unsigned long __v = (unsigned long)(val);          \
                __asm__ __volatile__("csrw 0x105, %0" \
                                     :                             \
                                     : "rK"(__v)                   \
                                     : "memory");                  \
        })

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

void exception_handler()
{
	xxk_print("exception occur!\n");
}

void setup_exception_vector()
{
        {
                unsigned long __v = (unsigned long)(exception_handler);
                __asm__ __volatile__("csrw 0x105, %0"
                                     :
                                     : "rK"(__v)
                                     : "memory");
        }
}

void user_program()
{
	xxk_print("try to output!\n");
}

void jump_to_user_mode()
{
        {
                unsigned long __v = (unsigned long)(user_program);
                __asm__ __volatile__("csrw 0x141, %0"
                                     :
                                     : "rK"(__v)
                                     : "memory");
        }
	__asm__ __volatile__("sret" : : );
	xxk_print("should not here!\n");
	while(1);
}

void cpu_entry(void)
{
	char *output = "Hello XU Xiake\n";

	xxk_print(output);
	setup_exception_vector();
	jump_to_user_mode();
	xxk_print("exit!\n");
	while(1);
}

