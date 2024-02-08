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
	add	x13, x0, 126976
	adrp	x2, .LANCHOR0
	add	x2, x2, :lo12:.LANCHOR0
	mov	x10, x0
	mov	x11, x1
	add	x9, x0, 474
	add	x13, x13, 2624
	add	x12, x2, 7
.L7:
	sub	x0, x9, #452
	add	x1, x11, 16
	cmp	x11, x0
	mov	x16, x11
	cset	w0, cs
	cmp	x10, x1
	cset	w1, cs
	mov	x7, x11
	cmp	x11, x12
	add	x11, x11, 474
	orr	w0, w0, w1
	ccmp	x11, x2, 0, cc
	ccmp	w0, 0, 4, ls
	beq	.L2
	ldr	b17, [x2, 1]
	sub	x7, x9, #473
	ldr	b16, [x2, 2]
	sub	x6, x9, #472
	ldr	b7, [x2, 3]
	sub	x5, x9, #471
	ldr	b6, [x2, 4]
	sub	x3, x9, #470
	ldr	b5, [x2, 5]
	sub	x1, x9, #469
	ldr	b4, [x2, 6]
	sub	x0, x9, #468
	dup	v17.16b, v17.b[0]
	ld1r	{v18.16b}, [x2]
	dup	v16.16b, v16.b[0]
	mov	x4, 0
	dup	v7.16b, v7.b[0]
	dup	v6.16b, v6.b[0]
	dup	v5.16b, v5.b[0]
	dup	v4.16b, v4.b[0]
.L3:
	ldr	q0, [x7, x4]
	ldr	q3, [x10, x4]
	umull	v1.8h, v17.8b, v0.8b
	umull2	v0.8h, v17.16b, v0.16b
	ldr	q2, [x6, x4]
	umlal	v1.8h, v18.8b, v3.8b
	umlal2	v0.8h, v18.16b, v3.16b
	ldr	q3, [x5, x4]
	umlal	v1.8h, v16.8b, v2.8b
	umlal2	v0.8h, v16.16b, v2.16b
	ldr	q2, [x3, x4]
	umlal	v1.8h, v7.8b, v3.8b
	umlal2	v0.8h, v7.16b, v3.16b
	ldr	q3, [x1, x4]
	umlal	v1.8h, v6.8b, v2.8b
	umlal2	v0.8h, v6.16b, v2.16b
	ldr	q2, [x0, x4]
	umlal	v1.8h, v5.8b, v3.8b
	umlal2	v0.8h, v5.16b, v3.16b
	umlal	v1.8h, v4.8b, v2.8b
	umlal2	v0.8h, v4.16b, v2.16b
	ushr	v1.8h, v1.8h, 8
	ushr	v0.8h, v0.8h, 8
	xtn	v2.8b, v1.8h
	xtn2	v2.16b, v0.8h
	str	q2, [x16, x4]
	add	x4, x4, 16
	cmp	x4, 464
	bne	.L3
	mov	x0, x10
	.p2align 3,,7
.L5:
	ldrb	w6, [x0, 467]
	add	x0, x0, 1
	ldrb	w7, [x2]
	ldrb	w8, [x0, 463]
	ldrb	w3, [x2, 3]
	ldrb	w5, [x2, 1]
	ldrb	w1, [x0, 464]
	mul	w8, w8, w7
	ldrb	w15, [x0, 465]
	mul	w3, w3, w6
	ldrb	w14, [x0, 468]
	ldrb	w7, [x2, 2]
	ldrb	w6, [x2, 5]
	madd	w1, w1, w5, w8
	ldrb	w5, [x0, 467]
	ldrb	w8, [x2, 4]
	madd	w7, w7, w15, w3
	ldrb	w3, [x2, 6]
	mul	w6, w6, w14
	add	w1, w1, w7
	ldrb	w7, [x0, 469]
	madd	w5, w5, w8, w6
	add	w1, w1, w5
	madd	w1, w3, w7, w1
	lsr	w1, w1, 8
	strb	w1, [x16, x4]
	add	x4, x4, 1
	cmp	x4, 474
	bne	.L5
	add	x10, x10, 480
	add	x9, x9, 480
	cmp	x10, x13
	bne	.L7
.L15:
	ret
.L2:
	sub	x0, x9, #474
	.p2align 3,,7
.L6:
	ldrb	w4, [x0]
	add	x0, x0, 1
	ldrb	w3, [x0, 1]
	ldrb	w6, [x2]
	ldrb	w5, [x2, 2]
	ldrb	w1, [x0]
	ldrb	w8, [x2, 1]
	mul	w4, w4, w6
	ldrb	w15, [x2, 3]
	ldrb	w6, [x0, 2]
	mul	w3, w3, w5
	ldrb	w14, [x2, 4]
	ldrb	w5, [x0, 3]
	madd	w1, w1, w8, w4
	ldrb	w4, [x0, 4]
	ldrb	w8, [x2, 5]
	madd	w6, w6, w15, w3
	ldrb	w3, [x0, 5]
	cmp	x0, x9
	mul	w5, w5, w14
	add	w1, w1, w6
	ldrb	w6, [x2, 6]
	madd	w4, w4, w8, w5
	add	w1, w1, w4
	madd	w1, w3, w6, w1
	lsr	w1, w1, 8
	strb	w1, [x7], 1
	bne	.L6
	add	x10, x10, 480
	add	x9, x9, 480
	cmp	x10, x13
	bne	.L7
	b	.L15
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
	stp	x29, x30, [sp, -128]!
	.cfi_def_cfa_offset 128
	.cfi_offset 29, -128
	.cfi_offset 30, -120
	mov	x15, x0
	adrp	x0, .LANCHOR0
	add	x0, x0, :lo12:.LANCHOR0
	mov	x29, sp
	mov	x3, x15
	stp	x21, x22, [sp, 32]
	.cfi_offset 21, -96
	.cfi_offset 22, -88
	mov	x22, x1
	add	x9, x15, 474
	stp	x23, x24, [sp, 48]
	.cfi_offset 23, -80
	.cfi_offset 24, -72
	mov	x24, x1
	add	x1, x0, 7
	add	x8, x15, 948
	add	x7, x15, 1422
	add	x6, x15, 1896
	add	x5, x15, 2370
	add	x4, x15, 2844
	str	x1, [sp, 120]
	mov	x1, 1422
	mov	x21, 474
	mov	x23, 0
	stp	x19, x20, [sp, 16]
	stp	x25, x26, [sp, 64]
	.cfi_offset 19, -112
	.cfi_offset 20, -104
	.cfi_offset 25, -64
	.cfi_offset 26, -56
	mov	x26, 2370
	mov	x25, 1896
	stp	x27, x28, [sp, 80]
	.cfi_offset 27, -48
	.cfi_offset 28, -40
	mov	x27, 2844
	str	x1, [sp, 112]
	mov	x1, 948
	str	x1, [sp, 104]
.L21:
	add	x1, x24, 16
	add	x2, x3, 2860
	ldr	x10, [sp, 120]
	cmp	x3, x1
	mov	x13, x24
	cset	w1, cs
	cmp	x24, x2
	add	x24, x24, 474
	cset	w2, cs
	cmp	x13, x10
	orr	w1, w1, w2
	ccmp	x24, x0, 0, cc
	ccmp	w1, 0, 4, ls
	beq	.L22
	ldr	b17, [x0, 1]
	mov	x1, 0
	ldr	b16, [x0, 2]
	ldr	b7, [x0, 3]
	ldr	b6, [x0, 4]
	ldr	b5, [x0, 5]
	dup	v17.16b, v17.b[0]
	ldr	b4, [x0, 6]
	dup	v16.16b, v16.b[0]
	ld1r	{v18.16b}, [x0]
	dup	v7.16b, v7.b[0]
	dup	v6.16b, v6.b[0]
	dup	v5.16b, v5.b[0]
	dup	v4.16b, v4.b[0]
.L18:
	ldr	q0, [x9, x1]
	ldr	q3, [x3, x1]
	umull	v1.8h, v17.8b, v0.8b
	umull2	v0.8h, v17.16b, v0.16b
	ldr	q2, [x8, x1]
	umlal	v1.8h, v18.8b, v3.8b
	umlal2	v0.8h, v18.16b, v3.16b
	ldr	q3, [x7, x1]
	umlal	v1.8h, v16.8b, v2.8b
	umlal2	v0.8h, v16.16b, v2.16b
	ldr	q2, [x6, x1]
	umlal	v1.8h, v7.8b, v3.8b
	umlal2	v0.8h, v7.16b, v3.16b
	ldr	q3, [x5, x1]
	umlal	v1.8h, v6.8b, v2.8b
	umlal2	v0.8h, v6.16b, v2.16b
	ldr	q2, [x4, x1]
	umlal	v1.8h, v5.8b, v3.8b
	umlal2	v0.8h, v5.16b, v3.16b
	umlal	v1.8h, v4.8b, v2.8b
	umlal2	v0.8h, v4.16b, v2.16b
	ushr	v1.8h, v1.8h, 8
	ushr	v0.8h, v0.8h, 8
	xtn	v2.8b, v1.8h
	xtn2	v2.16b, v0.8h
	str	q2, [x13, x1]
	add	x1, x1, 16
	cmp	x1, 464
	bne	.L18
	.p2align 3,,7
.L20:
	ldrb	w16, [x9, x1]
	ldrb	w14, [x0, 1]
	ldrb	w10, [x8, x1]
	ldrb	w12, [x0, 2]
	ldrb	w2, [x3, x1]
	ldrb	w11, [x0]
	mul	w16, w16, w14
	ldrb	w17, [x5, x1]
	ldrb	w14, [x7, x1]
	mul	w10, w10, w12
	ldrb	w18, [x0, 3]
	ldrb	w12, [x0, 5]
	madd	w2, w2, w11, w16
	ldrb	w16, [x6, x1]
	ldrb	w11, [x0, 4]
	madd	w14, w14, w18, w10
	ldrb	w10, [x0, 6]
	mul	w12, w12, w17
	add	w2, w2, w14
	ldrb	w14, [x4, x1]
	madd	w11, w11, w16, w12
	add	w2, w2, w11
	madd	w2, w10, w14, w2
	lsr	w2, w2, 8
	strb	w2, [x13, x1]
	add	x1, x1, 1
	cmp	x1, 474
	bne	.L20
.L19:
	ldr	x2, [sp, 104]
	add	x23, x23, 474
	sub	x1, x23, #122880
	add	x3, x3, 474
	add	x2, x2, 474
	str	x2, [sp, 104]
	ldr	x2, [sp, 112]
	add	x21, x21, 474
	add	x25, x25, 474
	add	x26, x26, 474
	add	x2, x2, 474
	str	x2, [sp, 112]
	add	x27, x27, 474
	add	x9, x9, 474
	add	x8, x8, 474
	add	x7, x7, 474
	add	x6, x6, 474
	add	x5, x5, 474
	add	x4, x4, 474
	subs	x1, x1, #2256
	bne	.L21
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 128
	.cfi_remember_state
	.cfi_restore 30
	.cfi_restore 29
	.cfi_restore 27
	.cfi_restore 28
	.cfi_restore 25
	.cfi_restore 26
	.cfi_restore 23
	.cfi_restore 24
	.cfi_restore 21
	.cfi_restore 22
	.cfi_restore 19
	.cfi_restore 20
	.cfi_def_cfa_offset 0
	ret
.L22:
	.cfi_restore_state
	ldr	x1, [sp, 112]
	sub	x19, x21, x23
	sub	x18, x26, x23
	sub	x17, x25, x23
	sub	x28, x1, x23
	sub	x16, x27, x23
	ldr	x1, [sp, 104]
	add	x19, x15, x19
	add	x18, x15, x18
	add	x17, x15, x17
	sub	x20, x1, x23
	add	x16, x15, x16
	add	x28, x15, x28
	add	x20, x15, x20
	mov	x1, x23
	.p2align 3,,7
.L17:
	ldrb	w10, [x20, x1]
	ldrb	w2, [x0, 2]
	ldrb	w14, [x28, x1]
	ldrb	w13, [x15, x1]
	ldrb	w12, [x0]
	ldrb	w11, [x0, 3]
	mul	w10, w10, w2
	ldrb	w30, [x0, 1]
	ldrb	w2, [x19, x1]
	mul	w13, w13, w12
	ldrb	w12, [x17, x1]
	madd	w10, w14, w11, w10
	ldrb	w14, [x0, 4]
	ldrb	w11, [x18, x1]
	madd	w2, w2, w30, w13
	ldrb	w13, [x0, 5]
	mul	w12, w12, w14
	add	w10, w10, w2
	ldrb	w2, [x16, x1]
	madd	w11, w11, w13, w12
	ldrb	w12, [x0, 6]
	add	w10, w10, w11
	madd	w2, w2, w12, w10
	lsr	w2, w2, 8
	strb	w2, [x22, x1]
	add	x1, x1, 1
	cmp	x1, x21
	bne	.L17
	b	.L19
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
	stp	x29, x30, [sp, -64]!
	.cfi_def_cfa_offset 64
	.cfi_offset 29, -64
	.cfi_offset 30, -56
	mov	x29, sp
	stp	x19, x20, [sp, 16]
	.cfi_offset 19, -48
	.cfi_offset 20, -40
	mov	x19, x0
	mov	x20, x1
	mov	x0, 62444
	movk	x0, 0x1, lsl 16
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	.cfi_offset 21, -32
	.cfi_offset 22, -24
	.cfi_offset 23, -16
	bl	malloc
	adrp	x8, .LANCHOR0
	add	x2, x8, :lo12:.LANCHOR0
	add	x3, x19, 6
	mov	x5, x0
	ldrb	w9, [x8, #:lo12:.LANCHOR0]
	mov	w7, 0
	ldrb	w10, [x2, 1]
	ldrb	w11, [x2, 2]
	ldrb	w12, [x2, 3]
	dup	v16.16b, w9
	ldrb	w13, [x2, 4]
	dup	v7.16b, w10
	ldrb	w14, [x2, 5]
	dup	v6.16b, w11
	ldrb	w15, [x2, 6]
	dup	v5.16b, w12
	dup	v4.16b, w13
	dup	v3.16b, w14
	dup	v2.16b, w15
	.p2align 3,,7
.L33:
	sub	x18, x3, #6
	sub	x17, x3, #5
	sub	x16, x3, #4
	sub	x6, x3, #3
	sub	x4, x3, #2
	sub	x1, x3, #1
	mov	x2, 0
.L31:
	ldr	q0, [x18, x2]
	ldr	q18, [x17, x2]
	umull	v1.8h, v16.8b, v0.8b
	umull2	v0.8h, v16.16b, v0.16b
	ldr	q17, [x16, x2]
	umlal	v1.8h, v7.8b, v18.8b
	umlal2	v0.8h, v7.16b, v18.16b
	ldr	q18, [x6, x2]
	umlal	v1.8h, v6.8b, v17.8b
	umlal2	v0.8h, v6.16b, v17.16b
	ldr	q17, [x4, x2]
	umlal	v1.8h, v5.8b, v18.8b
	umlal2	v0.8h, v5.16b, v18.16b
	ldr	q18, [x1, x2]
	umlal	v1.8h, v4.8b, v17.8b
	umlal2	v0.8h, v4.16b, v17.16b
	ldr	q17, [x3, x2]
	umlal	v1.8h, v3.8b, v18.8b
	umlal2	v0.8h, v3.16b, v18.16b
	umlal	v1.8h, v2.8b, v17.8b
	umlal2	v0.8h, v2.16b, v17.16b
	ushr	v1.8h, v1.8h, 8
	ushr	v0.8h, v0.8h, 8
	xtn	v17.8b, v1.8h
	xtn2	v17.16b, v0.8h
	str	q17, [x5, x2]
	add	x2, x2, 16
	cmp	x2, 464
	bne	.L31
	ldrb	w22, [x3, 458]
	ldrb	w18, [x3, 459]
	ldrb	w17, [x3, 460]
	ldrb	w16, [x3, 461]
	ldrb	w1, [x3, 462]
	ldrb	w6, [x3, 463]
.L32:
	mul	w19, w6, w14
	mov	w23, w6
	ldrb	w6, [x3, x2]
	mul	w4, w18, w10
	mul	w21, w16, w12
	madd	w4, w17, w11, w4
	madd	w21, w1, w13, w21
	madd	w19, w6, w15, w19
	add	w4, w4, w21
	add	w4, w4, w19
	madd	w4, w22, w9, w4
	mov	w22, w18
	mov	w18, w17
	mov	w17, w16
	mov	w16, w1
	mov	w1, w23
	lsr	w4, w4, 8
	strb	w4, [x5, x2]
	add	x2, x2, 1
	cmp	x2, 474
	bne	.L32
	add	w7, w7, 480
	add	x3, x3, 480
	sub	w1, w7, #126976
	add	x5, x5, 474
	subs	w1, w1, #2624
	bne	.L33
	mov	x16, 59600
	movk	x16, 0x1, lsl 16
	add	x6, x8, :lo12:.LANCHOR0
	add	x21, x0, 948
	add	x30, x0, 1422
	add	x19, x0, 1896
	add	x18, x0, 2370
	add	x17, x0, 2844
	mov	x7, 0
	b	.L37
	.p2align 2,,3
.L34:
	add	x7, x7, 474
	add	x2, x2, 474
	cmp	x7, x16
	beq	.L36
	ldrb	w11, [x6, 2]
	ldrb	w12, [x6, 3]
	ldrb	w9, [x6]
	ldrb	w10, [x6, 1]
	ldrb	w13, [x6, 4]
	ldrb	w14, [x6, 5]
	ldrb	w15, [x6, 6]
.L37:
	sub	x8, x2, x7
	mov	x1, x7
	add	x8, x0, x8
.L35:
	ldrb	w22, [x0, x1]
	ldrb	w5, [x30, x1]
	ldrb	w4, [x8, x1]
	ldrb	w3, [x21, x1]
	ldrb	w23, [x18, x1]
	mul	w9, w22, w9
	ldrb	w22, [x19, x1]
	mul	w12, w5, w12
	madd	w4, w4, w10, w9
	ldrb	w5, [x17, x1]
	madd	w3, w3, w11, w12
	mul	w14, w23, w14
	madd	w13, w22, w13, w14
	add	w3, w4, w3
	add	w3, w3, w13
	madd	w3, w5, w15, w3
	lsr	w3, w3, 8
	strb	w3, [x20, x1]
	add	x1, x1, 1
	cmp	x1, x2
	beq	.L34
	ldrb	w9, [x6]
	ldrb	w10, [x6, 1]
	ldrb	w11, [x6, 2]
	ldrb	w12, [x6, 3]
	ldrb	w13, [x6, 4]
	ldrb	w14, [x6, 5]
	ldrb	w15, [x6, 6]
	b	.L35
	.p2align 2,,3
.L36:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	.cfi_restore 30
	.cfi_restore 29
	.cfi_restore 23
	.cfi_restore 21
	.cfi_restore 22
	.cfi_restore 19
	.cfi_restore 20
	.cfi_def_cfa_offset 0
	b	free
	.cfi_endproc
.LFE21:
	.size	Filter(unsigned char const*, unsigned char*), .-Filter(unsigned char const*, unsigned char*)
	.global	Coefficients
	.data
	.align	4
	.set	.LANCHOR0,. + 0
	.type	Coefficients, %object
	.size	Coefficients, 7
Coefficients:
	.ascii	"\002\017>b>\017\002"
	.ident	"GCC: (GNU) 9.2.0"
	.section	.note.GNU-stack,"",@progbits
