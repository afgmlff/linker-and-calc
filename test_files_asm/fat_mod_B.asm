MOD_B: BEGIN
FAT: EXTERN
	N: EXTERN
	PUBLIC MOD_B
SECTION DATA
	AUX: SPACE
SECTION TEXT
	STORE AUX
	MUL N
	STORE N
	LOAD AUX
	JMP FAT

END