[FORMAT "WCOFF"]
[INSTRSET "i486p"]
[OPTIMIZE 1]
[OPTION 1]
[BITS 32]
	EXTERN	_io_hlt
	EXTERN	_io_load_eflags
	EXTERN	_io_cli
	EXTERN	_io_out8
	EXTERN	_io_store_eflags
[FILE "bootpack.c"]
[SECTION .text]
	GLOBAL	_HariMain
_HariMain:
	PUSH	EBP
	MOV	EBP,ESP
	CALL	_init_palette
	MOVSX	EAX,WORD [4086]
	PUSH	EAX
	MOVSX	EAX,WORD [4084]
	PUSH	EAX
	PUSH	DWORD [4088]
	CALL	_init_screen
	ADD	ESP,12
L2:
	CALL	_io_hlt
	JMP	L2
[SECTION .data]
_table_rgb.0:
	DB	0
	DB	0
	DB	0
	DB	-1
	DB	0
	DB	0
	DB	0
	DB	-1
	DB	0
	DB	-1
	DB	-1
	DB	0
	DB	0
	DB	0
	DB	-1
	DB	-1
	DB	0
	DB	-1
	DB	0
	DB	-1
	DB	-1
	DB	-1
	DB	-1
	DB	-1
	DB	-58
	DB	-58
	DB	-58
	DB	-124
	DB	0
	DB	0
	DB	0
	DB	-124
	DB	0
	DB	-124
	DB	-124
	DB	0
	DB	0
	DB	0
	DB	-124
	DB	-124
	DB	0
	DB	-124
	DB	0
	DB	-124
	DB	-124
	DB	-124
	DB	-124
	DB	-124
[SECTION .text]
	GLOBAL	_init_palette
_init_palette:
	PUSH	EBP
	MOV	EBP,ESP
	PUSH	_table_rgb.0
	PUSH	15
	PUSH	0
	CALL	_set_palette
	LEAVE
	RET
	GLOBAL	_init_screen
_init_screen:
	PUSH	EBP
	MOV	EBP,ESP
	PUSH	EDI
	PUSH	ESI
	PUSH	EBX
	SUB	ESP,20
	MOVSX	EBX,WORD [12+EBP]
	MOVSX	EAX,WORD [16+EBP]
	MOV	DWORD [-16+EBP],EAX
	LEA	EDI,DWORD [-1+EBX]
	SUB	EAX,29
	LEA	ESI,DWORD [-4+EBX]
	PUSH	EAX
	PUSH	EDI
	PUSH	0
	PUSH	0
	PUSH	14
	PUSH	EBX
	PUSH	DWORD [8+EBP]
	CALL	_boxfill8
	MOV	EAX,DWORD [-16+EBP]
	SUB	EAX,28
	PUSH	EAX
	PUSH	EDI
	PUSH	EAX
	PUSH	0
	PUSH	8
	PUSH	EBX
	PUSH	DWORD [8+EBP]
	CALL	_boxfill8
	MOV	EAX,DWORD [-16+EBP]
	ADD	ESP,56
	SUB	EAX,27
	PUSH	EAX
	PUSH	EDI
	PUSH	EAX
	PUSH	0
	PUSH	7
	PUSH	EBX
	PUSH	DWORD [8+EBP]
	CALL	_boxfill8
	MOV	EAX,DWORD [-16+EBP]
	DEC	EAX
	PUSH	EAX
	MOV	EAX,DWORD [-16+EBP]
	PUSH	EDI
	SUB	EAX,26
	PUSH	EAX
	LEA	EDI,DWORD [-47+EBX]
	PUSH	0
	PUSH	8
	PUSH	EBX
	PUSH	DWORD [8+EBP]
	CALL	_boxfill8
	MOV	EAX,DWORD [-16+EBP]
	ADD	ESP,56
	SUB	EAX,24
	MOV	DWORD [-20+EBP],EAX
	PUSH	EAX
	PUSH	59
	PUSH	EAX
	PUSH	3
	PUSH	7
	PUSH	EBX
	PUSH	DWORD [8+EBP]
	CALL	_boxfill8
	MOV	EAX,DWORD [-16+EBP]
	SUB	EAX,4
	PUSH	EAX
	MOV	DWORD [-24+EBP],EAX
	PUSH	2
	PUSH	DWORD [-20+EBP]
	PUSH	2
	PUSH	7
	PUSH	EBX
	PUSH	DWORD [8+EBP]
	CALL	_boxfill8
	ADD	ESP,56
	PUSH	DWORD [-24+EBP]
	PUSH	59
	PUSH	DWORD [-24+EBP]
	PUSH	3
	PUSH	15
	PUSH	EBX
	PUSH	DWORD [8+EBP]
	CALL	_boxfill8
	MOV	EAX,DWORD [-16+EBP]
	SUB	EAX,5
	PUSH	EAX
	MOV	EAX,DWORD [-16+EBP]
	PUSH	59
	SUB	EAX,23
	PUSH	EAX
	MOV	DWORD [-28+EBP],EAX
	PUSH	59
	PUSH	15
	PUSH	EBX
	PUSH	DWORD [8+EBP]
	CALL	_boxfill8
	MOV	EAX,DWORD [-16+EBP]
	ADD	ESP,56
	SUB	EAX,3
	MOV	DWORD [-32+EBP],EAX
	PUSH	EAX
	PUSH	59
	PUSH	EAX
	PUSH	2
	PUSH	0
	PUSH	EBX
	PUSH	DWORD [8+EBP]
	CALL	_boxfill8
	PUSH	DWORD [-32+EBP]
	PUSH	60
	PUSH	DWORD [-20+EBP]
	PUSH	60
	PUSH	0
	PUSH	EBX
	PUSH	DWORD [8+EBP]
	CALL	_boxfill8
	ADD	ESP,56
	PUSH	DWORD [-20+EBP]
	PUSH	ESI
	PUSH	DWORD [-20+EBP]
	PUSH	EDI
	PUSH	15
	PUSH	EBX
	PUSH	DWORD [8+EBP]
	CALL	_boxfill8
	PUSH	DWORD [-24+EBP]
	PUSH	EDI
	PUSH	DWORD [-28+EBP]
	PUSH	EDI
	PUSH	15
	PUSH	EBX
	PUSH	DWORD [8+EBP]
	CALL	_boxfill8
	ADD	ESP,56
	PUSH	DWORD [-32+EBP]
	PUSH	ESI
	PUSH	DWORD [-32+EBP]
	PUSH	EDI
	PUSH	7
	PUSH	EBX
	PUSH	DWORD [8+EBP]
	CALL	_boxfill8
	LEA	EAX,DWORD [-3+EBX]
	PUSH	DWORD [-32+EBP]
	PUSH	EAX
	PUSH	DWORD [-20+EBP]
	PUSH	EAX
	PUSH	7
	PUSH	EBX
	PUSH	DWORD [8+EBP]
	CALL	_boxfill8
	LEA	ESP,DWORD [-12+EBP]
	POP	EBX
	POP	ESI
	POP	EDI
	POP	EBP
	RET
	GLOBAL	_set_palette
_set_palette:
	PUSH	EBP
	MOV	EBP,ESP
	PUSH	EDI
	PUSH	ESI
	PUSH	EBX
	PUSH	ECX
	MOV	EBX,DWORD [8+EBP]
	MOV	EDI,DWORD [12+EBP]
	MOV	ESI,DWORD [16+EBP]
	CALL	_io_load_eflags
	MOV	DWORD [-16+EBP],EAX
	CALL	_io_cli
	PUSH	EBX
	PUSH	968
	CALL	_io_out8
	CMP	EBX,EDI
	POP	EAX
	POP	EDX
	JLE	L12
L14:
	MOV	EAX,DWORD [-16+EBP]
	MOV	DWORD [8+EBP],EAX
	LEA	ESP,DWORD [-12+EBP]
	POP	EBX
	POP	ESI
	POP	EDI
	POP	EBP
	JMP	_io_store_eflags
L12:
	MOV	AL,BYTE [ESI]
	INC	EBX
	SHR	AL,2
	MOVZX	EAX,AL
	PUSH	EAX
	PUSH	969
	CALL	_io_out8
	MOV	AL,BYTE [1+ESI]
	SHR	AL,2
	MOVZX	EAX,AL
	PUSH	EAX
	PUSH	969
	CALL	_io_out8
	MOV	AL,BYTE [2+ESI]
	SHR	AL,2
	ADD	ESI,3
	MOVZX	EAX,AL
	PUSH	EAX
	PUSH	969
	CALL	_io_out8
	ADD	ESP,24
	CMP	EBX,EDI
	JLE	L12
	JMP	L14
	GLOBAL	_boxfill8
_boxfill8:
	PUSH	EBP
	MOV	EBP,ESP
	PUSH	EDI
	PUSH	ESI
	PUSH	EBX
	PUSH	EDI
	PUSH	EDI
	MOV	AL,BYTE [16+EBP]
	MOV	ECX,DWORD [24+EBP]
	MOV	EDI,DWORD [28+EBP]
	MOV	BYTE [-13+EBP],AL
	CMP	ECX,DWORD [32+EBP]
	JG	L27
	MOV	EBX,DWORD [12+EBP]
	IMUL	EBX,ECX
L25:
	MOV	EDX,DWORD [20+EBP]
	CMP	EDX,EDI
	JG	L29
	MOV	EAX,DWORD [8+EBP]
	ADD	EAX,EBX
	LEA	EAX,DWORD [EAX+EDX*1]
	MOV	DWORD [-20+EBP],EAX
L24:
	MOV	ESI,DWORD [-20+EBP]
	MOV	AL,BYTE [-13+EBP]
	INC	EDX
	MOV	BYTE [ESI],AL
	INC	ESI
	MOV	DWORD [-20+EBP],ESI
	CMP	EDX,EDI
	JLE	L24
L29:
	INC	ECX
	ADD	EBX,DWORD [12+EBP]
	CMP	ECX,DWORD [32+EBP]
	JLE	L25
L27:
	POP	EBX
	POP	ESI
	POP	EBX
	POP	ESI
	POP	EDI
	POP	EBP
	RET
