
#include "xuxiake.h"
#include "lib.h"
#include "gpio.h"

/* CSR definition */
#define CSR_STVEC                       0x105
#define CSR_MEPC                        0x341

//#define csr_write(csr, val)                                        \
//        ({                                                         \
//                unsigned long __v = (unsigned long)(val);          \
//                __asm__ __volatile__("csrw 0x105, %0" \
//                                     :                             \
//                                     : "r"(__v)                   \
//                                     : "memory");                  \
//        })

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
		xxk_debug("Environment call from U-mode\n");
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
	xxk_print("XXK: after set user program\n");
	//sscratch 0x140
        {
                __asm__ __volatile__("csrw 0x140, sp\n\t"	\
				     "li  sp,  0x45400000"
                                     :
                                     :
                                     : "memory");
        }
	xxk_print("XXK: after set sscratch\n");
	__asm__ __volatile__("sret" : : );
	xxk_print("XXK: should not here!\n");
	while(1);
}

