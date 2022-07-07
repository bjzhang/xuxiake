
#include "xuxiake.h"

.equ	USTACK,		0x45400000
.equ	SSCRATCH,	0x45300000

	.global		_start
	.global		_trap_handler
	.section	".start", "ax"
_start:
	csrw	sie, 0
	csrw	sip, 0
	li	sp,  SSCRATCH
	call	cpu_entry

_trap_handler:
	# Swap tp and sscratch
	csrrw	tp, CSR_SSCRATCH, tp
	add	tp, tp, -8
	sd	t0, 0(tp)
	//t0 is the sp in user mode.
	add	t0, sp, 0
	add	sp, tp, -TRAP_REGS_SIZE
	sd	ra,     0(sp)
	sd	t0,   1*8(sp)
	sd	gp,   2*8(sp)
	sd	a0,   9*8(sp)
	sd	a1,  10*8(sp)
	sd	a2,  11*8(sp)
	sd	a3,  12*8(sp)
	sd	a4,  13*8(sp)
	sd	a5,  14*8(sp)
	sd	a6,  15*8(sp)
	sd	a7,  16*8(sp)
	add	a0,  sp, 0
	call trap_handler
	ld	ra,     0(sp)
	ld	gp,   2*8(sp)
	ld	a0,   9*8(sp)
	ld	a1,  10*8(sp)
	ld	a2,  11*8(sp)
	ld	a3,  12*8(sp)
	ld	a4,  13*8(sp)
	ld	a5,  14*8(sp)
	ld	a6,  15*8(sp)
	ld	a7,  16*8(sp)
	//restore tp
	add	tp, sp, TRAP_REGS_SIZE
	//restore sp. For now, sp of smode is useless
	ld	sp,   1*8(sp)
	//restore t0
	ld	t0,   0(tp)
	//tp should as same as sscratch in the beginning of _trap_handler
	add	tp, tp, 8
	csrrw	tp, CSR_SSCRATCH, tp
	sret
