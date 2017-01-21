	.file	"teste.ll"
	.text
	.globl	main
	.align	16, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rax
.Ltmp1:
	.cfi_def_cfa_offset 16
	movl	$.LformatString, %edi
	movl	$16, %esi
	xorl	%eax, %eax
	callq	printf
	movl	$1, %eax
	popq	%rdx
	ret
.Ltmp2:
	.size	main, .Ltmp2-main
	.cfi_endproc

	.type	.LformatString,@object  # @formatString
	.section	.rodata,"a",@progbits
.LformatString:
	.ascii	"%d"
	.size	.LformatString, 2


	.section	".note.GNU-stack","",@progbits
