#ifndef ASM_H
#define ASM_H

#define CSR_SSCRATCH	0x140
#define CSR_STAP	0x180
#define TRAP_REGS_SIZE	(35*8)

/* SBI Extension IDs */
#define SBI_EXT_0_1_CONSOLE_PUTCHAR             0x1

#ifndef __ASSEMBLY__
int sbi_ecall(int ext, unsigned long arg0);

/* reference opensbi/include/sbi/sbi_trap.h */
/** Representation of register state at time of trap/interrupt */
struct trap_regs {
	/** ra register state */	//0
	unsigned long ra;
	/** sp register state */	//1
	unsigned long sp;
	/** gp register state */	//2
	unsigned long gp;
	/** tp register state */	//3
	unsigned long tp;
	/** t0 register state */	//4
	unsigned long t0;
	/** t1 register state */	//5
	unsigned long t1;
	/** t2 register state */	//6
	unsigned long t2;
	/** s0 register state */	//7
	unsigned long s0;
	/** s1 register state */	//8
	unsigned long s1;
	/** a0 register state */	//9
	unsigned long a0;
	/** a1 register state */	//10
	unsigned long a1;
	/** a2 register state */	//11
	unsigned long a2;
	/** a3 register state */	//12
	unsigned long a3;
	/** a4 register state */	//13
	unsigned long a4;
	/** a5 register state */	//14
	unsigned long a5;
	/** a6 register state */	//15
	unsigned long a6;
	/** a7 register state */	//16
	unsigned long a7;
	/** s2 register state */	//17
	unsigned long s2;
	/** s3 register state */	//18
	unsigned long s3;
	/** s4 register state */	//19
	unsigned long s4;
	/** s5 register state */	//20
	unsigned long s5;
	/** s6 register state */	//21
	unsigned long s6;
	/** s7 register state */	//22
	unsigned long s7;
	/** s8 register state */	//23
	unsigned long s8;
	/** s9 register state */	//24
	unsigned long s9;
	/** s10 register state */	//25
	unsigned long s10;
	/** s11 register state */	//26
	unsigned long s11;
	/** t3 register state */	//27
	unsigned long t3;
	/** t4 register state */	//28
	unsigned long t4;
	/** t5 register state */	//29
	unsigned long t5;
	/** t6 register state */	//30
	unsigned long t6;
	/** mepc register state */	//31
	unsigned long mepc;
	/** mstatus register state */	//32
	unsigned long mstatus;
	/** mstatusH register state (only for 32-bit) */	//33
	unsigned long mstatusH;
} __packed;

#endif /* #ifndef __ASSEMBLY__ */
#endif /* #ifndef ASM_H */
