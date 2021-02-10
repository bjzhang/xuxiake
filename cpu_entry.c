
#include "xuxiake.h"

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
                                     : "r"(__v)                   \
                                     : "memory");                  \
        })

#define xxk_debug(a) while(0);
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

void trap_handler(struct trap_regs *t)
{
	//get arg0 and ext from trap context
	unsigned long scause;
	unsigned long sepc;
	char exception_code[0];

	xxk_debug("exception occur!\n");
	//read SCAUSE(0x142)
	__asm__ __volatile__("csrr %0, 0x142"
			     : "+r" (scause)
			     :
			     : "memory");
	if (scause == 8) {
		xxk_debug("supervisor software interrupt\n");
		//call SBI
		if (t->a7 == SBI_EXT_0_1_CONSOLE_PUTCHAR) {
			sbi_ecall(t->a7, t->a0);
			//return to SEPC(0x141) + 4.
			__asm__ __volatile__("csrr %0, 0x141\n\t"\
					     "add %0, %0, 4\n\t"\
					     "csrw 0x141, %0"
					     : "+r" (sepc)
					     :
					     : "memory");
		} else {
			while(1);
		}
	} else {
		scause = scause & (~0x80000000);
		exception_code[0] = '0' + scause;
		xxk_print("XXK: could not handle the scause(");
		xxk_print(exception_code);
		xxk_print(")\n");
		while(1);
	}
}

extern void  _trap_handler(void);
void setup_exception_vector()
{
        {
                unsigned long __v = (unsigned long)(_trap_handler);
                __asm__ __volatile__("csrw 0x105, %0"
                                     :
                                     : "r"(__v)
                                     : "memory");
        }
}

void user_program()
{
	xxk_print("try to output!\n");
}

void jump_to_user_mode()
{
	//sepc 0x141
        {
                unsigned long __v = (unsigned long)(user_program);
                __asm__ __volatile__("csrw 0x141, %0"
                                     :
                                     : "r"(__v)
                                     : "memory");
        }
	//sscratch 0x140
        {
                __asm__ __volatile__("csrw 0x140, sp\n\t"	\
				     "li  sp,  0x80400000"
                                     :
                                     :
                                     : "memory");
        }
	__asm__ __volatile__("sret" : : );
	xxk_print("XXK: should not here!\n");
	while(1);
}

void cpu_entry(void)
{
	xxk_print("XXK: Hello XU Xiake\n");
	setup_exception_vector();
	jump_to_user_mode();
	xxk_print("XXK: exit!\n");
	while(1);
}

