
.equ	STACK,		0x80400000

	.global		_start
	.section	".start", "ax"
_start:
	csrw	sie, 0
	csrw	sip, 0
	li	sp,  STACK
	call	cpu_entry
