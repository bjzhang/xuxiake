#include <xuxiake.h>
#include <lib.h>
#include <asm.h>
#include <asm/xuxiake.h>

#define EC_SHIFT	26
#define EC_MASK		0x3f
#define ISS_SHIFT	0
#define ISS_MASK	0x1ffffff

//0b01 0001
#define EC_SVC32	0x11
//0b01 0101
#define EC_SVC64	0x15
//0b10 0000
#define EL_IA_LOW	0x20
//0b10 0001
#define EL_IA_CUR	0x21
//0b10 0100
#define EL_DA_LOW	0x24
//0b10 0101
#define EL_DA_CUR	0x25

#ifdef CONFIG_USERSPACE
static void user_program(void);
#endif /* #ifdef CONFIG_USERSPACE */
#ifdef CONFIG_SYSCALL
extern void print(char *str);
#endif /* #ifdef CONFIG_SYSCALL */

static u64 get_currentel(void)
{
	u64 curentel = (u64)-1;

        __asm__ __volatile__("mrs %0, CurrentEL\n\t"\
                             : "=r" (curentel)
                             :
                             :);

	return curentel;
}

#ifdef CONFIG_USERSPACE
static void user_program(void)
{
	xxk_print("try to output from userspace by accessing uart register directly\n");
#ifdef CONFIG_SYSCALL
	print("try to output from userspace by write syscall\n");
#endif /* #ifdef CONFIG_SYSCALL */
}
#endif /* #ifdef CONFIG_USERSPACE`*/

s32 svc_handler(unsigned long esr, struct trap_regs *t)
{
	char *str = NULL;
	int is_handled = 0;

	xxk_debug("XXK: SVC from aarch64 EE\n");
	if (t->x8 == 64) {
		xxk_debug("XXK: write syscall\n");
		str = (char*)t->x1;
		xxk_print(str);
		is_handled = 1;
	} else {
		xxk_print("XXK: ERROR: could not handle this syscall: ");
		xxk_print_hex64(t->x8);
		xxk_print("\n");
	}
	return is_handled;
}


void trap_handler(unsigned long esr, struct trap_regs *t)
{
	unsigned long ec = (esr >> EC_SHIFT) & EC_MASK;
	unsigned long iss = (esr >> ISS_SHIFT) & ISS_MASK;
	s32 is_handled = 0;

	xxk_debug("XXK: enter svc esr: ");
	xxk_debug_hex64(esr);
	xxk_debug(", ec: ");
	xxk_debug_hex32(ec);
	xxk_debug(", iss: ");
	xxk_debug_hex32(iss);
	xxk_debug(", elr: ");
	xxk_debug_hex64(t->lr);
	xxk_debug("\n");
	switch(ec) {
	case EL_DA_LOW:
	case EL_DA_CUR:
#ifdef CONFIG_MMU
		is_handled = da_handler(esr, t);
#endif /* #ifdef CONFIG_MMU */
		break;
	case EL_IA_LOW:
	case EL_IA_CUR:
#ifdef CONFIG_MMU
		is_handled = ia_handler(esr, t);
#endif /* #ifdef CONFIG_MMU */
		break;
	case EC_SVC64:
		is_handled = svc_handler(esr, t);
		break;
	default:
		xxk_print("XXK: Do not regconize this exeption!\n");
		break;
	}

	if (is_handled) {
		xxk_debug("XXK: Exception return\n");
	} else {
		xxk_error("XXK: Could not handle this exception. stall...\n");
		while(1);
	}
}

void setup_exception_vector()
{
	unsigned long __v = (unsigned long)(_vectors);
	__asm__ __volatile__("msr VBAR_EL1, %0\n\t"	\
			     :
			     : "r"(__v)
			     : "memory");

	xxk_info("Current exception level: ");
	xxk_info_hex32(get_currentel() >> 2);
	xxk_info("\n");
}

#ifdef CONFIG_USERSPACE
void copy_user_program(void)
{
	memcpy((void*)USER_MEM_START, (void*)PHY_OFFSET, 2 * 1024 * 1024);
}

void jump_to_user_mode()
{
	unsigned long __u = (unsigned long)(user_program - PHY_OFFSET + USER_MEM_START);
	unsigned long __sp = (unsigned long)(USER_STACK_TOP);

	__asm__ __volatile__("msr ELR_EL1, %0\n\t"	\
			     "msr SP_EL0, %1\n\t"	\
			     "eret\n\t"			\
			     :
			     : "r"(__u), "r"(__sp)
			     : "memory");
	xxk_print("ERROR: Should not come here!\n");
}
#endif /* #ifdef CONFIG_USERSPACE */
