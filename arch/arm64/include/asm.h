#ifndef ASM_H
#define ASM_H

#define PHY_OFFSET		(0x40000000)
#define PHY_SIZE		(0x06000000)
#define DEV_PL011_OFFSET	(0x09000000)
#define DEV_PL011_SIZE		(0x00001000)

#define SYS_STACK_TOP		(0x45200000)
#define USER_MEM_START		(0x80000000)
#define USER_DATA_START		(0xC0000000)
#define USER_STACK_SIZE		(0x00010000)
#define USER_STACK_TOP		(USER_DATA_START + USER_STACK_SIZE)

//8G
#define MEMORY_MAX		(0x200000000UL)

#ifndef __ASSEMBLY__
/* reference opensbi/include/sbi/sbi_trap.h */
/** Representation of register state at time of trap/interrupt */
struct trap_regs {
	unsigned long x0;
	unsigned long x1;
	unsigned long x2;
	unsigned long x3;
	unsigned long x4;
	unsigned long x5;
	unsigned long x6;
	unsigned long x7;
	unsigned long x8;
	unsigned long x9;
	unsigned long fp;
	unsigned long lr;
} __attribute__((__packed__));

/* Copy from include/linux/arm-smccc.h */
/**
 * struct arm_smccc_res - Result from SMC/HVC call
 * @a0-a3 result values from registers 0 to 3
 */
struct arm_smccc_res {
	unsigned long a0;
	unsigned long a1;
	unsigned long a2;
	unsigned long a3;
};

/* replace struct arm_smccc_quirk to void to simplicity */
asmlinkage void __arm_smccc_smc(unsigned long a0, unsigned long a1,
                        unsigned long a2, unsigned long a3, unsigned long a4,
                        unsigned long a5, unsigned long a6, unsigned long a7,
                        struct arm_smccc_res *res, void *quirk);

#define arm_smccc_smc(...) __arm_smccc_smc(__VA_ARGS__, NULL)

#endif /* #ifndef __ASSEMBLY__ */
#endif /* #ifndef ASM_H */
