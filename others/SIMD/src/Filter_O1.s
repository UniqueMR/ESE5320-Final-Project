	.arch armv8-a+crypto+crc
	.file	"Filter.cpp"
	.text
	.align	2
	.p2align 4,,15
	.global	Filter_horizontal(unsigned char const*, unsigned char*)
	.type	Filter_horizontal(unsigned char const*, unsigned char*), %function
Filter_horizontal(unsigned char const*, unsigned char*):
.LFB19:
	.cfi_startproc
	mov	w9, 1620
	adrp	x5, .LANCHOR0
	add	x5, x5, :lo12:.LANCHOR0
	mov	x8, x0
	add	x7, x1, 474
	neg	w10, w1
	sub	w9, w9, w1
.L4:
	sub	x6, x7, #474
	mov	x4, x8
	.p2align 3,,7
.L3:
	mov	x0, 0
	mov	w1, 0
	.p2align 3,,7
.L2:
	ldrb	w3, [x4, x0]
	ldr	w2, [x5, x0, lsl 2]
	add	x0, x0, 1
	cmp	x0, 7
	madd	w1, w3, w2, w1
	bne	.L2
	lsr	w1, w1, 8
	strb	w1, [x6], 1
	add	x4, x4, 1
	cmp	x7, x6
	bne	.L3
	add	w10, w10, 6
	add	x7, x7, 474
	cmp	w10, w9
	add	x8, x8, 480
	bne	.L4
	ret
	.cfi_endproc
.LFE19:
	.size	Filter_horizontal(unsigned char const*, unsigned char*), .-Filter_horizontal(unsigned char const*, unsigned char*)
	.align	2
	.p2align 4,,15
	.global	Filter_vertical(unsigned char const*, unsigned char*)
	.type	Filter_vertical(unsigned char const*, unsigned char*), %function
Filter_vertical(unsigned char const*, unsigned char*):
.LFB20:
	.cfi_startproc
	adrp	x5, .LANCHOR0
	add	x5, x5, :lo12:.LANCHOR0
	mov	x8, x0
	mov	x7, x1
	mov	w9, 0
.L12:
	mov	x6, 0
	.p2align 3,,7
.L11:
	add	x1, x8, x6
	mov	x0, 0
	mov	w2, 0
	.p2align 3,,7
.L10:
	ldrb	w4, [x1]
	add	x1, x1, 474
	ldr	w3, [x5, x0, lsl 2]
	add	x0, x0, 1
	cmp	x0, 7
	madd	w2, w4, w3, w2
	bne	.L10
	lsr	w2, w2, 8
	strb	w2, [x7, x6]
	add	x6, x6, 1
	cmp	x6, 474
	bne	.L11
	add	w9, w9, 1
	add	x7, x7, 474
	cmp	w9, 264
	add	x8, x8, 474
	bne	.L12
	ret
	.cfi_endproc
.LFE20:
	.size	Filter_vertical(unsigned char const*, unsigned char*), .-Filter_vertical(unsigned char const*, unsigned char*)
	.align	2
	.p2align 4,,15
	.global	Filter(unsigned char const*, unsigned char*)
	.type	Filter(unsigned char const*, unsigned char*), %function
Filter(unsigned char const*, unsigned char*):
.LFB21:
	.cfi_startproc
	stp	x29, x30, [sp, -32]!
	.cfi_def_cfa_offset 32
	.cfi_offset 29, -32
	.cfi_offset 30, -24
	mov	x29, sp
	stp	x19, x20, [sp, 16]
	.cfi_offset 19, -16
	.cfi_offset 20, -8
	mov	x19, x1
	mov	x20, x0
	mov	x0, 62444
	movk	x0, 0x1, lsl 16
	bl	malloc
	mov	x11, x0
	mov	x1, x11
	mov	x0, x20
	bl	Filter_horizontal(unsigned char const*, unsigned char*)
	mov	x0, x11
	mov	x1, x19
	bl	Filter_vertical(unsigned char const*, unsigned char*)
	ldp	x19, x20, [sp, 16]
	mov	x0, x11
	ldp	x29, x30, [sp], 32
	.cfi_restore 30
	.cfi_restore 29
	.cfi_restore 19
	.cfi_restore 20
	.cfi_def_cfa_offset 0
	b	free
	.cfi_endproc
.LFE21:
	.size	Filter(unsigned char const*, unsigned char*), .-Filter(unsigned char const*, unsigned char*)
	.global	Coefficients
	.data
	.align	3
	.set	.LANCHOR0,. + 0
	.type	Coefficients, %object
	.size	Coefficients, 28
Coefficients:
	.word	2
	.word	15
	.word	62
	.word	98
	.word	62
	.word	15
	.word	2
	.ident	"GCC: (GNU) 9.2.0"
	.section	.note.GNU-stack,"",@progbits
