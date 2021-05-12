# Trabalho Prático 2
Nome: Aécio Fernandes Galiza Magalhães

Matrícula: 15/0115121

Disciplina: Software Básico

# Como executar o programa
Para a execução do programa, é necessário ambiente Ubuntu (foi desenvolvido no 16.04), g++ (foi desenvolvido na versão 5.4) e GNU Make 4.1 (para construir o projeto).

Como executar:

1) Extrair o arquivo entregue pelo Moodle;
2) Na raiz do arquivo (entrar na pasta "150115121_trab1_sb"), digite o comando 'make' para construir o projeto (montador + simulador + ligador);
3) Ainda na raiz, para MONTAR um, dois ou três arquivos exemplos basta utilizar

    $ ./montador <caminho/arquivo1> <caminho/arquivo2> <caminho/arquivo3>

    #ex.: ./montador test_files_asm/ex1.asm (1) OU ./montador test_files_asm/fat_mod_A_2.asm test_files_asm/fat_mod_B_2.asm (2) OU ./montador test_files_asm/fat_mod_A.asm test_files_asm/fat_mod_B.asm test_files_asm/fat_mod_C.asm (3)

4) Assim, são gerados os arquivos .OBJ na mesma pasta do arquivo de entrada (por exemplo, ex1.obj dentro da pasta "test_files_asm"), caso NÃO hajam erros na montagem (Apenas erros de diretivas BEGIN/END).

5) No caso de 2 ou 3 arquivos montados, é necessário ligá-los em seguida, utilizando o comando:

    $ ./ligador <caminho/arquivo1.obj> <caminho/arquivo2.obj> <caminho/arquivo3.obj>

    #ex.: ./montador test_files_asm/fat_mod_A.obj test_files_asm/fat_mod_B.obj test_files_asm/fat_mod_C.obj

6) Após ligados, é gerado um arquivo de saída do ligador cujo nome é igual ao nome do ÚLTIMO arquivo inserido no módulo do ligador, com a extensão ".obj.obj (para evitar que subescreva o .obj gerado pelo montador anteriormente)
Por exemplo, a serem ligados os módulos "fat_mod_A.obj + fat_mod_B.obj + fat_mod_C.obj", será resultado o arquivo "fat_mod_C.obj.obj" dentro da PASTA "test_files_asm". Esse arquivo pode ser utilizado no simulador, utilizando:

    $ ./simulador test_files_asm/fat_mod_C.obj.obj

7) Para casos de apenas 1 arquivo montado (como no primeiro trabalho), o arquivo de saída do próprio montador pode ser utilizado no simulador, da mesma forma:

    $ ./simulador <caminho/arquivo1.obj>

    #ex.: ./simulador test_files_asm/ex1.obj (atente-se a extensão .OBJ)

8) Assim, o simulador mostrará na tela o valor de PC e ACC após cada instrução, bem como o valor de OUTPUT para instruções do tipo OUTPUT.
7) Também é gerado um arquivo de saida .OUT na mesma pasta do arquivo de entrada (por exemplo, fat_mod_C.obj.out, dentro da pasta "test_files_asm"), com os OUTPUTS do programa, separados por um "ENTER".

# Formato do arquivo objeto
O arquivo objeto é composto por 4 partes: cabeçalho (H), código objeto (T), tabela de uso (U) e tabela de definições (D). Por exemplo:

H: nome do arquivo (sem extensão)

H: tamanho

H: mapa de bits

T: código objeto em linha única

U: primeiro elemento da tabela de uso

...

U: ultimo elemento da tabela de uso

D: primeiro elemento da tabela de definições

...

D: último elemento da tabela de definições (fim do arquivo objeto)


