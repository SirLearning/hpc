	.file	"debugcode.cpp"
	.intel_syntax noprefix
	.text
	.p2align 4
	.globl	_Z6vecaddPdS_S_m
	.type	_Z6vecaddPdS_S_m, @function
_Z6vecaddPdS_S_m:
.LFB1763:
	.cfi_startproc
	test	rcx, rcx
	je	.L2
	cmp	rcx, 1
	je	.L6
	mov	r8, rcx
	xor	eax, eax
	shr	r8
	sal	r8, 4
	.p2align 4,,10
	.p2align 3
.L4:
	movupd	xmm0, XMMWORD PTR [rdi+rax]
	movupd	xmm1, XMMWORD PTR [rsi+rax]
	addpd	xmm0, xmm1
	movups	XMMWORD PTR [rdx+rax], xmm0
	add	rax, 16
	cmp	r8, rax
	jne	.L4
	mov	rax, rcx
	and	rax, -2
	and	ecx, 1
	je	.L2
.L3:
	movsd	xmm0, QWORD PTR [rsi+rax*8]
	addsd	xmm0, QWORD PTR [rdi+rax*8]
	movsd	QWORD PTR [rdx+rax*8], xmm0
.L2:
	xor	eax, eax
	ret
.L6:
	xor	eax, eax
	jmp	.L3
	.cfi_endproc
.LFE1763:
	.size	_Z6vecaddPdS_S_m, .-_Z6vecaddPdS_S_m
	.p2align 4
	.globl	_Z14SimpleMultiplyPKdS0_Pdmmm
	.type	_Z14SimpleMultiplyPKdS0_Pdmmm, @function
_Z14SimpleMultiplyPKdS0_Pdmmm:
.LFB1764:
	.cfi_startproc
	push	r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	push	r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	push	r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	push	r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	push	rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	push	rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	mov	QWORD PTR [rsp-8], rsi
	test	rcx, rcx
	je	.L12
	test	r9, r9
	je	.L12
	mov	rbx, rdi
	mov	rax, rcx
	mov	r12, rdx
	mov	r10, r8
	mov	DWORD PTR [rsp-20], eax
	xor	r15d, r15d
	xor	r14d, r14d
	xor	r13d, r13d
	lea	rdi, [0+r9*8]
	lea	rsi, [0+r8*8]
	pxor	xmm2, xmm2
	mov	QWORD PTR [rsp-16], rdi
	lea	rcx, [rbx+rsi]
	.p2align 4,,10
	.p2align 3
.L14:
	mov	r8, QWORD PTR [rsp-8]
	lea	rbp, [rbx+r15*8]
	lea	r11, [r12+r14*8]
	xor	edi, edi
	.p2align 4,,10
	.p2align 3
.L18:
	mov	rdx, r8
	mov	rax, rbp
	movapd	xmm1, xmm2
	test	r10, r10
	je	.L17
	.p2align 4,,10
	.p2align 3
.L15:
	movsd	xmm0, QWORD PTR [rax]
	mulsd	xmm0, QWORD PTR [rdx]
	add	rax, 8
	add	rdx, rsi
	addsd	xmm1, xmm0
	cmp	rax, rcx
	jne	.L15
.L17:
	movsd	QWORD PTR [r11+rdi*8], xmm1
	add	rdi, 1
	add	r8, 8
	cmp	r9, rdi
	jne	.L18
	add	r13d, 1
	add	r14, r10
	add	r15, r9
	add	rcx, QWORD PTR [rsp-16]
	cmp	r13d, DWORD PTR [rsp-20]
	jne	.L14
.L12:
	pop	rbx
	.cfi_def_cfa_offset 48
	pop	rbp
	.cfi_def_cfa_offset 40
	pop	r12
	.cfi_def_cfa_offset 32
	pop	r13
	.cfi_def_cfa_offset 24
	pop	r14
	.cfi_def_cfa_offset 16
	pop	r15
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE1764:
	.size	_Z14SimpleMultiplyPKdS0_Pdmmm, .-_Z14SimpleMultiplyPKdS0_Pdmmm
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC1:
	.string	"Timing = %ldus\n"
.LC2:
	.string	"aaa = %d\n"
	.section	.text.startup,"ax",@progbits
	.p2align 4
	.globl	main
	.type	main, @function
main:
.LFB1765:
	.cfi_startproc
	push	rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	xor	esi, esi
	sub	rsp, 101392
	.cfi_def_cfa_offset 101408
	lea	rdi, [rsp+68624]
	call	gettimeofday
	xor	eax, eax
	imul	rbx, QWORD PTR [rsp+68624], 1000000
	add	rbx, QWORD PTR [rsp+68632]
	.p2align 4,,10
	.p2align 3
.L31:
	movapd	xmm1, XMMWORD PTR [rsp+1040+rax]
	movapd	xmm0, XMMWORD PTR [rsp+16+rax]
	addpd	xmm0, xmm1
	movaps	XMMWORD PTR [rsp], xmm1
	movaps	XMMWORD PTR [rsp+2064+rax], xmm0
	add	rax, 16
	cmp	rax, 1024
	jne	.L31
	lea	rdi, [rsp+68624]
	xor	esi, esi
	call	gettimeofday
	mov	edi, OFFSET FLAT:.LC1
	xor	eax, eax
	imul	rsi, QWORD PTR [rsp+68624], 1000000
	add	rsi, QWORD PTR [rsp+68632]
	sub	rsi, rbx
	call	printf
	mov	r9d, 64
	mov	ecx, 64
	lea	rdx, [rsp+68624]
	lea	rsi, [rsp+35856]
	lea	rdi, [rsp+3088]
	mov	r8d, 64
	call	_Z14SimpleMultiplyPKdS0_Pdmmm
	xor	esi, esi
	mov	edi, OFFSET FLAT:.LC2
	xor	eax, eax
	call	printf
	add	rsp, 101392
	.cfi_def_cfa_offset 16
	xor	eax, eax
	pop	rbx
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE1765:
	.size	main, .-main
	.p2align 4
	.type	_GLOBAL__sub_I__Z6vecaddPdS_S_m, @function
_GLOBAL__sub_I__Z6vecaddPdS_S_m:
.LFB2247:
	.cfi_startproc
	sub	rsp, 8
	.cfi_def_cfa_offset 16
	mov	edi, OFFSET FLAT:_ZStL8__ioinit
	call	_ZNSt8ios_base4InitC1Ev
	mov	edx, OFFSET FLAT:__dso_handle
	mov	esi, OFFSET FLAT:_ZStL8__ioinit
	mov	edi, OFFSET FLAT:_ZNSt8ios_base4InitD1Ev
	add	rsp, 8
	.cfi_def_cfa_offset 8
	jmp	__cxa_atexit
	.cfi_endproc
.LFE2247:
	.size	_GLOBAL__sub_I__Z6vecaddPdS_S_m, .-_GLOBAL__sub_I__Z6vecaddPdS_S_m
	.section	.init_array,"aw"
	.align 8
	.quad	_GLOBAL__sub_I__Z6vecaddPdS_S_m
	.local	_ZStL8__ioinit
	.comm	_ZStL8__ioinit,1,1
	.hidden	__dso_handle
	.ident	"GCC: (GNU) 11.2.0"
	.section	.note.GNU-stack,"",@progbits
