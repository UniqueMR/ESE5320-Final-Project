	.arch armv8-a+crypto+crc
	.file	"Example.cpp"
	.text
	.align	2
	.p2align 4,,15
	.global	add3_NEON(unsigned char*)
	.type	add3_NEON(unsigned char*), %function
add3_NEON(unsigned char*):
.LFB5824:
	.cfi_startproc
	movi	v1.16b, 0x3
	add	x1, x0, 1024
	.p2align 3,,7
.L2:
	ldr	q0, [x0]
	add	v0.16b, v0.16b, v1.16b
	str	q0, [x0], 16
	cmp	x0, x1
	bne	.L2
	ret
	.cfi_endproc
.LFE5824:
	.size	add3_NEON(unsigned char*), .-add3_NEON(unsigned char*)
	.align	2
	.p2align 4,,15
	.global	add3_c(unsigned int*)
	.type	add3_c(unsigned int*), %function
add3_c(unsigned int*):
.LFB5825:
	.cfi_startproc
	movi	v1.4s, 0x3
	add	x1, x0, 4096
	.p2align 3,,7
.L6:
	ldr	q0, [x0]
	add	v0.4s, v0.4s, v1.4s
	str	q0, [x0], 16
	cmp	x1, x0
	bne	.L6
	ret
	.cfi_endproc
.LFE5825:
	.size	add3_c(unsigned int*), .-add3_c(unsigned int*)
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align	3
.LC0:
	.string	"%s:\n"
	.align	3
.LC1:
	.string	"%02d\n"
	.text
	.align	2
	.p2align 4,,15
	.global	print_NEON(unsigned char*, char*)
	.type	print_NEON(unsigned char*, char*), %function
print_NEON(unsigned char*, char*):
.LFB5826:
	.cfi_startproc
	stp	x29, x30, [sp, -48]!
	.cfi_def_cfa_offset 48
	.cfi_offset 29, -48
	.cfi_offset 30, -40
	mov	x29, sp
	stp	x19, x20, [sp, 16]
	.cfi_offset 19, -32
	.cfi_offset 20, -24
	mov	x19, x0
	adrp	x20, .LC1
	add	x20, x20, :lo12:.LC1
	str	x21, [sp, 32]
	.cfi_offset 21, -16
	add	x21, x19, 1024
	adrp	x0, .LC0
	add	x0, x0, :lo12:.LC0
	bl	printf
	.p2align 3,,7
.L9:
	ldrb	w1, [x19], 1
	mov	x0, x20
	bl	printf
	cmp	x19, x21
	bne	.L9
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	.cfi_restore 30
	.cfi_restore 29
	.cfi_restore 21
	.cfi_restore 19
	.cfi_restore 20
	.cfi_def_cfa_offset 0
	ret
	.cfi_endproc
.LFE5826:
	.size	print_NEON(unsigned char*, char*), .-print_NEON(unsigned char*, char*)
	.align	2
	.p2align 4,,15
	.global	print_C(unsigned int*, char*)
	.type	print_C(unsigned int*, char*), %function
print_C(unsigned int*, char*):
.LFB5827:
	.cfi_startproc
	stp	x29, x30, [sp, -48]!
	.cfi_def_cfa_offset 48
	.cfi_offset 29, -48
	.cfi_offset 30, -40
	mov	x29, sp
	stp	x19, x20, [sp, 16]
	.cfi_offset 19, -32
	.cfi_offset 20, -24
	mov	x19, x0
	adrp	x20, .LC1
	add	x20, x20, :lo12:.LC1
	str	x21, [sp, 32]
	.cfi_offset 21, -16
	add	x21, x19, 4096
	adrp	x0, .LC0
	add	x0, x0, :lo12:.LC0
	bl	printf
	.p2align 3,,7
.L13:
	ldr	w1, [x19], 4
	mov	x0, x20
	bl	printf
	cmp	x19, x21
	bne	.L13
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	.cfi_restore 30
	.cfi_restore 29
	.cfi_restore 21
	.cfi_restore 19
	.cfi_restore 20
	.cfi_def_cfa_offset 0
	ret
	.cfi_endproc
.LFE5827:
	.size	print_C(unsigned int*, char*), .-print_C(unsigned int*, char*)
	.align	2
	.p2align 4,,15
	.global	compare_results(unsigned int*, unsigned char*)
	.type	compare_results(unsigned int*, unsigned char*), %function
compare_results(unsigned int*, unsigned char*):
.LFB5828:
	.cfi_startproc
	mov	x2, 0
	b	.L18
	.p2align 2,,3
.L22:
	cmp	x2, 1024
	beq	.L21
.L18:
	ldrb	w3, [x1, x2]
	ldr	w4, [x0, x2, lsl 2]
	add	x2, x2, 1
	cmp	w3, w4, uxtb
	beq	.L22
	mov	w0, 0
	ret
	.p2align 2,,3
.L21:
	mov	w0, 1
	ret
	.cfi_endproc
.LFE5828:
	.size	compare_results(unsigned int*, unsigned char*), .-compare_results(unsigned int*, unsigned char*)
	.section	.rodata.str1.8
	.align	3
.LC2:
	.string	"equal"
	.align	3
.LC3:
	.string	"NOT equal"
	.align	3
.LC4:
	.string	"NEON add3 takes %fns \n"
	.align	3
.LC5:
	.string	"C add3 takes %fns \n"
	.align	3
.LC6:
	.string	"Results are "
	.section	.text.startup,"ax",@progbits
	.align	2
	.p2align 4,,15
	.global	main
	.type	main, %function
main:
.LFB5829:
	.cfi_startproc
	movi	v20.4s, 0x10
	mov	x12, 5200
	movi	v4.4s, 0x7f
	sub	sp, sp, x12
	.cfi_def_cfa_offset 5200
	movi	v19.4s, 0x4
	movi	v18.4s, 0x8
	movi	v17.4s, 0xc
	stp	x29, x30, [sp]
	.cfi_offset 29, -5200
	.cfi_offset 30, -5192
	mov	x29, sp
	adrp	x0, .LC7
	ldr	q5, [x0, #:lo12:.LC7]
	stp	x19, x20, [sp, 16]
	.cfi_offset 19, -5184
	.cfi_offset 20, -5176
	add	x20, sp, 80
	stp	x21, x22, [sp, 32]
	.cfi_offset 21, -5168
	.cfi_offset 22, -5160
	add	x21, sp, 1104
	mov	x1, x20
	add	x2, x20, 1024
	mov	x19, x21
	mov	x0, x21
	.p2align 3,,7
.L24:
	mov	v0.16b, v5.16b
	add	v5.4s, v5.4s, v20.4s
	add	v3.4s, v0.4s, v19.4s
	add	v2.4s, v0.4s, v18.4s
	add	v1.4s, v0.4s, v17.4s
	and	v0.16b, v0.16b, v4.16b
	and	v3.16b, v3.16b, v4.16b
	and	v2.16b, v2.16b, v4.16b
	and	v1.16b, v1.16b, v4.16b
	xtn	v16.4h, v0.4s
	xtn2	v16.8h, v3.4s
	xtn	v7.4h, v2.4s
	xtn2	v7.8h, v1.4s
	xtn	v6.8b, v16.8h
	xtn2	v6.16b, v7.8h
	str	q6, [x1], 16
	cmp	x1, x2
	stp	q0, q3, [x0]
	stp	q2, q1, [x0, 32]
	add	x0, x0, 64
	bne	.L24
	bl	std::chrono::_V2::system_clock::now()
	mov	x22, x0
	movi	v1.16b, 0x3
	mov	x1, x20
	add	x2, x20, 1024
	str	x0, [sp, 64]
	.p2align 3,,7
.L25:
	ldr	q0, [x1]
	add	v0.16b, v0.16b, v1.16b
	str	q0, [x1], 16
	cmp	x1, x2
	bne	.L25
	bl	std::chrono::_V2::system_clock::now()
	sub	x1, x0, x22
	movi	d1, #0
	adrp	x2, .LC4
	scvtf	d0, x1
	str	x0, [sp, 72]
	add	x0, x2, :lo12:.LC4
	fadd	d0, d0, d1
	bl	printf
	bl	std::chrono::_V2::system_clock::now()
	mov	x22, x0
	movi	v1.4s, 0x3
	add	x1, x21, 4096
	str	x0, [sp, 64]
	.p2align 3,,7
.L26:
	ldr	q0, [x19]
	add	v0.4s, v0.4s, v1.4s
	str	q0, [x19], 16
	cmp	x19, x1
	bne	.L26
	bl	std::chrono::_V2::system_clock::now()
	sub	x1, x0, x22
	movi	d1, #0
	adrp	x2, .LC5
	scvtf	d0, x1
	str	x0, [sp, 72]
	add	x0, x2, :lo12:.LC5
	fadd	d0, d0, d1
	bl	printf
	mov	x0, 1
	b	.L29
	.p2align 2,,3
.L37:
	cmp	x0, 1025
	beq	.L36
.L29:
	add	x2, x21, x0, lsl 2
	add	x1, x20, x0
	add	x0, x0, 1
	ldrb	w2, [x2, -4]
	ldrb	w1, [x1, -1]
	cmp	w1, w2
	beq	.L37
	adrp	x19, :got:std::cout
	adrp	x1, .LC6
	mov	x2, 12
	add	x1, x1, :lo12:.LC6
	ldr	x0, [x19, #:got_lo12:std::cout]
	bl	std::basic_ostream<char, std::char_traits<char> >& std::__ostream_insert<char, std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&, char const*, long)
	adrp	x1, .LC3
	add	x1, x1, :lo12:.LC3
.L30:
	ldr	x0, [x19, #:got_lo12:std::cout]
	bl	std::basic_ostream<char, std::char_traits<char> >& std::operator<< <std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&, char const*)
	bl	std::basic_ostream<char, std::char_traits<char> >& std::endl<char, std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&)
	mov	w0, 0
	mov	x12, 5200
	ldp	x29, x30, [sp]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	add	sp, sp, x12
	.cfi_remember_state
	.cfi_restore 29
	.cfi_restore 30
	.cfi_restore 21
	.cfi_restore 22
	.cfi_restore 19
	.cfi_restore 20
	.cfi_def_cfa_offset 0
	ret
.L36:
	.cfi_restore_state
	adrp	x19, :got:std::cout
	adrp	x1, .LC6
	mov	x2, 12
	add	x1, x1, :lo12:.LC6
	ldr	x0, [x19, #:got_lo12:std::cout]
	bl	std::basic_ostream<char, std::char_traits<char> >& std::__ostream_insert<char, std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&, char const*, long)
	adrp	x1, .LC2
	add	x1, x1, :lo12:.LC2
	b	.L30
	.cfi_endproc
.LFE5829:
	.size	main, .-main
	.align	2
	.p2align 4,,15
	.type	_GLOBAL__sub_I__Z9add3_NEONPh, %function
_GLOBAL__sub_I__Z9add3_NEONPh:
.LFB6346:
	.cfi_startproc
	stp	x29, x30, [sp, -32]!
	.cfi_def_cfa_offset 32
	.cfi_offset 29, -32
	.cfi_offset 30, -24
	mov	x29, sp
	str	x19, [sp, 16]
	.cfi_offset 19, -16
	adrp	x19, .LANCHOR0
	add	x19, x19, :lo12:.LANCHOR0
	mov	x0, x19
	bl	std::ios_base::Init::Init()
	mov	x1, x19
	adrp	x0, :got:std::ios_base::Init::~Init()
	ldr	x19, [sp, 16]
	adrp	x2, __dso_handle
	add	x2, x2, :lo12:__dso_handle
	ldp	x29, x30, [sp], 32
	.cfi_restore 30
	.cfi_restore 29
	.cfi_restore 19
	.cfi_def_cfa_offset 0
	ldr	x0, [x0, #:got_lo12:std::ios_base::Init::~Init()]
	b	__cxa_atexit
	.cfi_endproc
.LFE6346:
	.size	_GLOBAL__sub_I__Z9add3_NEONPh, .-_GLOBAL__sub_I__Z9add3_NEONPh
	.section	.init_array,"aw"
	.align	3
	.xword	_GLOBAL__sub_I__Z9add3_NEONPh
	.section	.rodata.cst16,"aM",@progbits,16
	.align	4
.LC7:
	.word	0
	.word	1
	.word	2
	.word	3
	.bss
	.align	3
	.set	.LANCHOR0,. + 0
	.type	std::__ioinit, %object
	.size	std::__ioinit, 1
std::__ioinit:
	.zero	1
	.hidden	__dso_handle
	.ident	"GCC: (GNU) 9.2.0"
	.section	.note.GNU-stack,"",@progbits
