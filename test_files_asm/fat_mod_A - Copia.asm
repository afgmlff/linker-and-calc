MOD_A: BEGIN
SECTION DATA
        MOD_B: EXTERN
	PUBLIC FAT
	PUBLIC N
	N: SPACE
	ONE: CONST 1
SECTION TEXT
	INPUT N
	LOAD N
	FAT: SUB ONE
	JMPZ FIM
	JMP MOD_B
	FIM: OUTPUT N
	STOP

END