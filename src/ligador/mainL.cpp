#include <iostream>
#include "../../include/ligador.hpp"
#include "../../include/global.hpp"

int main(int argc, char **argv) {
  if (argc < 3){
		cout << "Quantidade de parametros invalida. Forneça os nomes dos arquivos a serem ligados.";
		return 1;
	}

  if (argc == 3){
	   Ligador ligador(argv[1]);
	   ligador.ligar();

     Ligador ligador2(argv[2]);
     ligador2.ligar();
  }

	return 0;

}
