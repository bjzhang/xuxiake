
#include "xuxiake.h"

.equ	USTACK,		0x80400000
.equ	SSCRATCH,	0x80300000

	.global		_start
	.global		_trap_handler
	.section	".start", "ax"
_start:
	csrw	sie, 0
	csrw	sip, 0
	li	sp,  SSCRATCH
	call	cpu_entry

_trap_handler:
	csrrw	tp, CSR_SSCRATCH, tp
	add	tp, tp, -8
	sd	t0, 0(tp)
	add	t0, sp, 0
	add	sp, tp, -TRAP_REGS_SIZE
	sd	zero, 0(sp)
	sd	ra,   1*8(sp)
	sd	t0,   2*8(sp)
	sd	gp,   3*8(sp)
	sd	a0,  10*8(sp)
	sd	a1,  11*8(sp)
	sd	a2,  12*8(sp)
	sd	a3,  13*8(sp)
	sd	a4,  14*8(sp)
	sd	a5,  15*8(sp)
	sd	a6,  16*8(sp)
	sd	a7,  17*8(sp)
	add	a0,  sp, 0
	call trap_handler
	ld	zero, 0(sp)
	ld	ra,   1*8(sp)
	ld	gp,   3*8(sp)
	ld	a0,  10*8(sp)
	ld	a1,  11*8(sp)
	ld	a2,  12*8(sp)
	ld	a3,  13*8(sp)
	ld	a4,  14*8(sp)
	ld	a5,  15*8(sp)
	ld	a6,  16*8(sp)
	ld	a7,  17*8(sp)
	ld	t0,   0(tp)
	ld	sp,   2*8(sp)
	sret
