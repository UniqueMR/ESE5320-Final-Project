	.arch armv8-a+crypto+crc
	.file	"Scale.cpp"
	.text
	.align	2
	.p2align 4,,15
	.global	Scale(unsigned char const*, unsigned char*)
	.type	Scale(unsigned char const*, unsigned char*), %function
Scale(unsigned char const*, unsigned char*):
.LFB12:
	.cfi_startproc
	mov	x4, x0
	mov	x5, x1
	mov	w6, 0
	mov	w7, 480
.L3:
	asr	w3, w6, 1
	mov	x0, 0
	mul	w3, w3, w7
	.p2align 3,,7
.L2:
	add	w1, w3, w0, asr 1
	ldrb	w2, [x4, x0]
	add	x0, x0, 2
	cmp	x0, 960
	strb	w2, [x5, w1, sxtw]
	bne	.L2
	add	w6, w6, 2
	add	x4, x4, 1920
	cmp	w6, 540
	bne	.L3
	ret
	.cfi_endproc
.LFE12:
	.size	Scale(unsigned char const*, unsigned char*), .-Scale(unsigned char const*, unsigned char*)
	.ident	"GCC: (GNU) 9.2.0"
	.section	.note.GNU-stack,"",@progbits
