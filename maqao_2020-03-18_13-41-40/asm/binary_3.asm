0xaab:::0::Insn: MOV	-0x14(%RBP),%EAX
0xaae:::0::Insn: CLTQ
0xab0:::0::Insn: LEA	(,%RAX,4),%RDX
0xab8:::0::Insn: MOV	-0x30(%RBP),%RAX
0xabc:::0::Insn: LEA	(%RDX,%RAX,1),%RBX
0xac0:::0::Insn: CALL	6f0 <rand@plt>
0xac5:::0::Insn: MOV	%EAX,%ECX
0xac7:::0::Insn: MOVSXD	%ECX,%RDX
0xaca:::0::Insn: MOV	%RDX,%RAX
0xacd:::0::Insn: SAL	$0x1e,%RAX
0xad1:::0::Insn: ADD	%RDX,%RAX
0xad4:::0::Insn: SHR	$0x20,%RAX
0xad8:::0::Insn: MOV	%EAX,%EDX
0xada:::0::Insn: SAR	$0x1d,%EDX
0xadd:::0::Insn: MOV	%ECX,%EAX
0xadf:::0::Insn: SAR	$0x1f,%EAX
0xae2:::0::Insn: SUB	%EAX,%EDX
0xae4:::0::Insn: MOV	%EDX,%EAX
0xae6:::0::Insn: PXOR	%XMM0,%XMM0
0xaea:::0::Insn: CVTSI2SS	%EAX,%XMM0
0xaee:::0::Insn: MOVSS	%XMM0,(%RBX)
0xaf2:::0::Insn: ADDL	$0x1,-0x14(%RBP)
0xaf6:::0::Insn: MOV	-0x14(%RBP),%EAX
0xaf9:::0::Insn: CLTQ
0xafb:::0::Insn: CMP	-0x28(%RBP),%RAX
0xaff:::0::Insn: JB	aab <init_array+0x1a>
