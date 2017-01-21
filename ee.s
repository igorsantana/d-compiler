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
	movl	$1, 4(%rsp)
	jmp	.LBB0_1
	.align	16, 0x90
.LBB0_2:                                # %_loop_1
                                        #   in Loop: Header=BB0_1 Depth=1
	movl	4(%rsp), %esi
	incl	%esi
	movl	%esi, 4(%rsp)
	movl	$STR_0, %edi
	xorl	%eax, %eax
	callq	printf
.LBB0_1:                                # %_loop_0
                                        # =>This Inner Loop Header: Depth=1
	cmpl	$2, 4(%rsp)
	jbe	.LBB0_2
# BB#3:                                 # %_loop_2
	xorl	%eax, %eax
	popq	%rcx
	retq
.Lfunc_end0:
	.size	main, .Lfunc_end0-main
	.cfi_endproc

	.type	STR_0,@object           # @STR_0
	.section	.rodata,"a",@progbits
STR_0:
	.ascii	"%i"
	.size	STR_0, 2


	.section	".note.GNU-stack","",@progbits
