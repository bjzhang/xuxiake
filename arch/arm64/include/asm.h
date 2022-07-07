#ifndef ASM_H
#define ASM_H

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
} __packed;

#endif /* #ifndef __ASSEMBLY__ */
#endif /* #ifndef ASM_H */
