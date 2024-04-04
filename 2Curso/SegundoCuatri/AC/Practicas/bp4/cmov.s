	.file	"cmov.c"
# GNU C17 (GCC) version 12.1.0 (x86_64-pc-linux-gnu)
#	compiled by GNU C version 12.1.0, GMP version 6.2.1, MPFR version 4.1.0-p13, MPC version 1.2.1, isl version isl-0.24-GMP

# GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
# options passed: -mtune=generic -march=x86-64
	.text
	.section	.rodata
.LC0:
	.string	"c: %i\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$16, %rsp	#,
# cmov.c:4: 	volatile int a=0;
	movl	$0, -12(%rbp)	#, a
# cmov.c:5: 	volatile int b=1;
	movl	$1, -8(%rbp)	#, b
# cmov.c:8: 	c = (a==b)?3:7;
	movl	-12(%rbp), %edx	# a, a.1_1
	movl	-8(%rbp), %eax	# b, b.2_2
# cmov.c:8: 	c = (a==b)?3:7;
	cmpl	%eax, %edx	# b.2_2, a.1_1
	jne	.L2	#,
# cmov.c:8: 	c = (a==b)?3:7;
	movl	$3, %eax	#, iftmp.0_3
	jmp	.L3	#
.L2:
# cmov.c:8: 	c = (a==b)?3:7;
	movl	$7, %eax	#, iftmp.0_3
.L3:
# cmov.c:8: 	c = (a==b)?3:7;
	movl	%eax, -4(%rbp)	# iftmp.0_3, c
# cmov.c:10: 	printf("c: %i\n", c);
	movl	-4(%rbp), %eax	# c, tmp87
	movl	%eax, %esi	# tmp87,
	leaq	.LC0(%rip), %rax	#, tmp88
	movq	%rax, %rdi	# tmp88,
	movl	$0, %eax	#,
	call	printf@PLT	#
# cmov.c:11: 	return(0);
	movl	$0, %eax	#, _11
# cmov.c:12: }
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (GNU) 12.1.0"
	.section	.note.GNU-stack,"",@progbits
