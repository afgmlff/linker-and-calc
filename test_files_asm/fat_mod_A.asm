MOD_A: BEGIN
MOD_B: EXTERN
MOD_C: extern
	PUBLIC FAT
	PUBLIC N
	public FIM
SECTION DATA
	N: SPACE
	ONE: CONST 1
SECTION TEXT
	INPUT N
	LOAD N
	FAT: SUB ONE
	JMPZ MOD_C
	JMP MOD_B
	FIM: OUTPUT N
	STOP

END
