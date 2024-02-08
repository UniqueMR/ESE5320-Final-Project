	.arch armv8-a+crypto+crc
	.file	"Filter.cpp"
	.text
	.global	Coefficients
	.data
	.align	3
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
	.text
	.align	2
	.global	Filter_horizontal(unsigned char const*, unsigned char*)
	.type	Filter_horizontal(unsigned char const*, unsigned char*), %function
Filter_horizontal(unsigned char const*, unsigned char*):
.LFB14:
	.cfi_startproc
	sub	sp, sp, #32
	.cfi_def_cfa_offset 32
	str	x0, [sp, 8]
	str	x1, [sp]
	str	wzr, [sp, 28]
.L7:
	ldr	w0, [sp, 28]
	cmp	w0, 269
	bgt	.L8
	str	wzr, [sp, 24]
.L6:
	ldr	w0, [sp, 24]
	cmp	w0, 473
	bgt	.L3
	str	wzr, [sp, 20]
	str	wzr, [sp, 16]
.L5:
	ldr	w0, [sp, 16]
	cmp	w0, 6
	bgt	.L4
	adrp	x0, Coefficients
	add	x0, x0, :lo12:Coefficients
	ldrsw	x1, [sp, 16]
	ldr	w0, [x0, x1, lsl 2]
	ldr	w2, [sp, 28]
	mov	w1, 480
	mul	w2, w2, w1
	ldr	w1, [sp, 24]
	add	w2, w2, w1
	ldr	w1, [sp, 16]
	add	w1, w2, w1
	sxtw	x1, w1
	ldr	x2, [sp, 8]
	add	x1, x2, x1
	ldrb	w1, [x1]
	mul	w0, w0, w1
	ldr	w1, [sp, 20]
	add	w0, w1, w0
	str	w0, [sp, 20]
	ldr	w0, [sp, 16]
	add	w0, w0, 1
	str	w0, [sp, 16]
	b	.L5
.L4:
	ldr	w0, [sp, 20]
	lsr	w2, w0, 8
	ldr	w1, [sp, 28]
	mov	w0, 474
	mul	w1, w1, w0
	ldr	w0, [sp, 24]
	add	w0, w1, w0
	sxtw	x0, w0
	ldr	x1, [sp]
	add	x0, x1, x0
	and	w1, w2, 255
	strb	w1, [x0]
	ldr	w0, [sp, 24]
	add	w0, w0, 1
	str	w0, [sp, 24]
	b	.L6
.L3:
	ldr	w0, [sp, 28]
	add	w0, w0, 1
	str	w0, [sp, 28]
	b	.L7
.L8:
	nop
	add	sp, sp, 32
	.cfi_def_cfa_offset 0
	ret
	.cfi_endproc
.LFE14:
	.size	Filter_horizontal(unsigned char const*, unsigned char*), .-Filter_horizontal(unsigned char const*, unsigned char*)
	.align	2
	.global	Filter_vertical(unsigned char const*, unsigned char*)
	.type	Filter_vertical(unsigned char const*, unsigned char*), %function
Filter_vertical(unsigned char const*, unsigned char*):
.LFB15:
	.cfi_startproc
	sub	sp, sp, #32
	.cfi_def_cfa_offset 32
	str	x0, [sp, 8]
	str	x1, [sp]
	str	wzr, [sp, 28]
.L15:
	ldr	w0, [sp, 28]
	cmp	w0, 263
	bgt	.L16
	str	wzr, [sp, 24]
.L14:
	ldr	w0, [sp, 24]
	cmp	w0, 473
	bgt	.L11
	str	wzr, [sp, 20]
	str	wzr, [sp, 16]
.L13:
	ldr	w0, [sp, 16]
	cmp	w0, 6
	bgt	.L12
	adrp	x0, Coefficients
	add	x0, x0, :lo12:Coefficients
	ldrsw	x1, [sp, 16]
	ldr	w0, [x0, x1, lsl 2]
	ldr	w2, [sp, 28]
	ldr	w1, [sp, 16]
	add	w2, w2, w1
	mov	w1, 474
	mul	w2, w2, w1
	ldr	w1, [sp, 24]
	add	w1, w2, w1
	sxtw	x1, w1
	ldr	x2, [sp, 8]
	add	x1, x2, x1
	ldrb	w1, [x1]
	mul	w0, w0, w1
	ldr	w1, [sp, 20]
	add	w0, w1, w0
	str	w0, [sp, 20]
	ldr	w0, [sp, 16]
	add	w0, w0, 1
	str	w0, [sp, 16]
	b	.L13
.L12:
	ldr	w0, [sp, 20]
	lsr	w2, w0, 8
	ldr	w1, [sp, 28]
	mov	w0, 474
	mul	w1, w1, w0
	ldr	w0, [sp, 24]
	add	w0, w1, w0
	sxtw	x0, w0
	ldr	x1, [sp]
	add	x0, x1, x0
	and	w1, w2, 255
	strb	w1, [x0]
	ldr	w0, [sp, 24]
	add	w0, w0, 1
	str	w0, [sp, 24]
	b	.L14
.L11:
	ldr	w0, [sp, 28]
	add	w0, w0, 1
	str	w0, [sp, 28]
	b	.L15
.L16:
	nop
	add	sp, sp, 32
	.cfi_def_cfa_offset 0
	ret
	.cfi_endproc
.LFE15:
	.size	Filter_vertical(unsigned char const*, unsigned char*), .-Filter_vertical(unsigned char const*, unsigned char*)
	.align	2
	.global	Filter(unsigned char const*, unsigned char*)
	.type	Filter(unsigned char const*, unsigned char*), %function
Filter(unsigned char const*, unsigned char*):
.LFB16:
	.cfi_startproc
	stp	x29, x30, [sp, -48]!
	.cfi_def_cfa_offset 48
	.cfi_offset 29, -48
	.cfi_offset 30, -40
	mov	x29, sp
	str	x0, [sp, 24]
	str	x1, [sp, 16]
	mov	x0, 62444
	movk	x0, 0x1, lsl 16
	bl	malloc
	str	x0, [sp, 40]
	ldr	x1, [sp, 40]
	ldr	x0, [sp, 24]
	bl	Filter_horizontal(unsigned char const*, unsigned char*)
	ldr	x1, [sp, 16]
	ldr	x0, [sp, 40]
	bl	Filter_vertical(unsigned char const*, unsigned char*)
	ldr	x0, [sp, 40]
	bl	free
	nop
	ldp	x29, x30, [sp], 48
	.cfi_restore 30
	.cfi_restore 29
	.cfi_def_cfa_offset 0
	ret
	.cfi_endproc
.LFE16:
	.size	Filter(unsigned char const*, unsigned char*), .-Filter(unsigned char const*, unsigned char*)
	.ident	"GCC: (GNU) 9.2.0"
	.section	.note.GNU-stack,"",@progbits
