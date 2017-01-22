	.text
	.file	"ee.ll"
	.globl	main
	.align	16, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# BB#0:
	pushq	%rax
.Ltmp0:
	.cfi_def_cfa_offset 16
	movl	$10, 4(%rsp)
	movl	$1, (%rsp)
	jmp	.LBB0_1
	.align	16, 0x90
.LBB0_2:                                # %_loop_1
                                        #   in Loop: Header=BB0_1 Depth=1
	movl	(%rsp), %eax
	imull	4(%rsp), %eax
	movl	%eax, (%rsp)
	decl	4(%rsp)
.LBB0_1:                                # %_loop_0
                                        # =>This Inner Loop Header: Depth=1
	cmpl	$2, 4(%rsp)
	jae	.LBB0_2
# BB#3:                                 # %_loop_2
	movl	(%rsp), %esi
	movl	$STR_0, %edi
	xorl	%eax, %eax
	callq	printf
	xorl	%eax, %eax
	popq	%rcx
	retq
.Lfunc_end0:
	.size	main, .Lfunc_end0-main
	.cfi_endproc

	.type	STR_0,@object           # @STR_0
	.section	.rodata,"a",@progbits
	.align	16
STR_0:
	.ascii	"Resultado do farorial de 10: %i \n"
	.size	STR_0, 33


	.section	".note.GNU-stack","",@progbits
