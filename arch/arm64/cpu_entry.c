#include "xuxiake.h"
#include "lib.h"
#include "asm.h"
#include "asm/xuxiake.h"

#define EC_SHIFT	26
#define EC_MASK		0x3f
#define ISS_SHIFT	0
#define ISS_MASK	0x1ffffff

//0b01 0001
#define EC_SVC32	0x11
//0b01 0101
#define EC_SVC64	0x15
//0b10 0100
#define DA_EL_L		0x24
//0b10 0101
#define DA_EL_H		0x25

#ifdef DEBUG
#define xxk_debug(fmt) xxk_print(fmt)
#define xxk_debug_hex(fmt) xxk_print_hex(fmt)
#else
#define xxk_debug(fmt) {;}
#endif /* ifdef DEBUG */

#define NULL ( (void *) 0)

static void user_program(void);
extern void print(char *str);

void svc_handler(unsigned long esr, struct trap_regs *t)
{
	char *str = NULL;
	xxk_debug("SVC from aarch64 EE\n");
	if (t->x8 == 64) {
		xxk_debug("write syscall\n");
		str = (char*)t->x1;
		xxk_print(str);
	} else {
		xxk_print("ERROR: could not handle this syscall: ");
		xxk_print_hex(t->x8);
		xxk_print("\n");
	}
}

void da_handler(unsigned long esr, struct trap_regs *t)
{
	xxk_debug("Data abort from lower exception\n");
}

void trap_handler(unsigned long esr, struct trap_regs *t)
{
	unsigned long ec = (esr >> EC_SHIFT) & EC_MASK;
	unsigned long iss = (esr >> ISS_SHIFT) & ISS_MASK;
	xxk_debug("enter svc esr: ");
	xxk_debug_hex(esr);
	xxk_debug(", ec: ");
	xxk_debug_hex(ec);
	xxk_debug(", iss: ");
	xxk_debug_hex(iss);
	xxk_debug("\n");
	switch(ec) {
	case EC_SVC64:
		svc_handler(esr, t);
		break;
	case DA_EL_L:
		da_handler(esr, t);
		break;
	default:
		xxk_print("Could not handle such exception right now!\n");
		break;
	}

	xxk_print("exit svc\n");
}

void setup_exception_vector()
{
	unsigned long __v = (unsigned long)(_vectors);
	__asm__ __volatile__("msr VBAR_EL1, %0\n\t"	\
			     :
			     : "r"(__v)
			     : "memory");

}

static void user_program(void)
{
	xxk_print("try to output from userspace by accessing uart register directly\n");
	print("try to output from userspace by write syscall\n");
}

void jump_to_user_mode()
{
	unsigned long __u = (unsigned long)(user_program);
	unsigned long __sp = (unsigned long)(0x45400000);
	__asm__ __volatile__("msr ELR_EL1, %0\n\t"	\
			     "msr SP_EL0, %1\n\t"	\
			     "eret\n\t"			\
			     :
			     : "r"(__u), "r"(__sp)
			     : "memory");
	xxk_print("ERROR: Should not come here!\n");
}

