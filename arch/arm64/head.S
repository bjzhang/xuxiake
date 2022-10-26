
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

