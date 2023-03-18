
#include <xuxiake.h>
#include <asm.h>

.equ	STACK,		SYS_STACK_TOP

	.global		_start
	.global		_vectors
	.global		_trap_handler
	.section	".start", "ax"
_start:
	mov x3, STACK
	mrs x4, CurrentEL
	mov sp, x3
	mov fp, sp
	bl cpu_entry

_trap_handler:
	stp fp, lr, [sp, #-16]!
	stp x8, x9, [sp, #-16]!
	stp x6, x7, [sp, #-16]!
	stp x4, x5, [sp, #-16]!
	stp x2, x3, [sp, #-16]!
	stp x0, x1, [sp, #-16]!
	mrs x0, ESR_EL1
	mov x1, sp
	bl trap_handler
	ldp x0, x1, [sp], 16
	ldp x2, x3, [sp], 16
	ldp x4, x5, [sp], 16
	ldp x6, x7, [sp], 16
	ldp x8, x9, [sp], 16
	ldp fp, lr, [sp], 16
	#restore pstate
	eret

.align	11
_vectors:
	b _trap_handler
.align	7
	b _trap_handler
.align	7
	b _trap_handler
.align	7
	b _trap_handler
.align	7
	b _trap_handler
.align	7
	b _trap_handler
.align	7
	b _trap_handler
.align	7
	b _trap_handler
.align	7
	b _trap_handler
.align	7
	b _trap_handler
.align	7
	b _trap_handler
.align	7
	b _trap_handler
.align	7
	b _trap_handler
.align	7
	b _trap_handler
.align	7
	b _trap_handler
.align	7
	b _trap_handler

.equ	ARM_SMCCC_RES_X0_OFFS,		16 /* offsetof(struct arm_smccc_res, a0) */
.equ	ARM_SMCCC_RES_X2_OFFS,		16 /* offsetof(struct arm_smccc_res, a2) */
.equ	ARM_SMCCC_QUIRK_ID_OFFS,	0 /* offsetof(struct arm_smccc_quirk, id) */
.equ	ARM_SMCCC_QUIRK_STATE_OFFS,	8 /* offsetof(struct arm_smccc_quirk, state) */
.equ	ARM_SMCCC_1_2_REGS_X0_OFFS,	0 /* offsetof(struct arm_smccc_1_2_regs, a0) */
.equ	ARM_SMCCC_1_2_REGS_X2_OFFS,	16 /* offsetof(struct arm_smccc_1_2_regs, a2) */
.equ	ARM_SMCCC_1_2_REGS_X4_OFFS,	32 /* offsetof(struct arm_smccc_1_2_regs, a4) */
.equ	ARM_SMCCC_1_2_REGS_X6_OFFS,	48 /* offsetof(struct arm_smccc_1_2_regs, a6) */
.equ	ARM_SMCCC_1_2_REGS_X8_OFFS,	64 /* offsetof(struct arm_smccc_1_2_regs, a8) */
.equ	ARM_SMCCC_1_2_REGS_X10_OFFS,	80 /* offsetof(struct arm_smccc_1_2_regs, a10) */
.equ	ARM_SMCCC_1_2_REGS_X12_OFFS,	96 /* offsetof(struct arm_smccc_1_2_regs, a12) */
.equ	ARM_SMCCC_1_2_REGS_X14_OFFS,	112 /* offsetof(struct arm_smccc_1_2_regs, a14) */
.equ	ARM_SMCCC_1_2_REGS_X16_OFFS,	128 /* offsetof(struct arm_smccc_1_2_regs, a16) */
.equ	ARM_SMCCC_QUIRK_NONE,		0
.equ	ARM_SMCCC_QUIRK_QCOM_A6,	1 /* Save/restore register a6 */

        .macro SMCCC instr
        stp     x29, x30, [sp, #-16]!
        mov     x29, sp
/**
 * alternative_if ARM64_SVE
 *         bl      __arm_smccc_sve_check
 * alternative_else_nop_endif
 */
        \instr  #0
        ldr     x4, [sp, #16]
        stp     x0, x1, [x4, #ARM_SMCCC_RES_X0_OFFS]
        stp     x2, x3, [x4, #ARM_SMCCC_RES_X2_OFFS]
        ldr     x4, [sp, #24]
        cbz     x4, 1f /* no quirk structure */
        ldr     x9, [x4, #ARM_SMCCC_QUIRK_ID_OFFS]
        cmp     x9, #ARM_SMCCC_QUIRK_QCOM_A6
        b.ne    1f
        str     x6, [x4, ARM_SMCCC_QUIRK_STATE_OFFS]
1:      ldp     x29, x30, [sp], #16
        ret
        .endm

/* Original defined at arch/arm64/kernel/smccc-call.S */
/*
 * void arm_smccc_smc(unsigned long a0, unsigned long a1, unsigned long a2,
 *                unsigned long a3, unsigned long a4, unsigned long a5,
 *                unsigned long a6, unsigned long a7, struct arm_smccc_res *res,
 *                struct arm_smccc_quirk *quirk)
 */
.global		__arm_smccc_smc
__arm_smccc_smc:
        SMCCC   smc
        /*SMCCC   hvc*/

