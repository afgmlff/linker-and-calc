#include <iostream>
#include "../../include/ligador.hpp"
#include "../../include/global.hpp"

int main(int argc, char **argv) {
  if (argc < 3){
		cout << "Quantidade de parametros invalida. Forneça os nomes dos arquivos a serem ligados.";
		return 1;
	}

  if (argc == 3){
     idLastArq = 2;
     idArquivoLig = 1;
	   Ligador ligador(argv[1]);
	   ligador.ligar();

     idArquivoLig = 2;
     Ligador ligador2(argv[2]);
     ligador2.ligar();
/*
     for(auto elem : mapGlobalDef)
     {
        std::cout << elem.first << " " << elem.second << " " << "\n";
     }
*/
  }

  if (argc == 4){
     idLastArq = 3;
     idArquivoLig = 1;
	   Ligador ligador(argv[1]);
	   ligador.ligar();

     idArquivoLig = 2;
     Ligador ligador2(argv[2]);
     ligador2.ligar();

     idArquivoLig = 3;
     Ligador ligador3(argv[3]);
     ligador3.ligar();

     for(auto elem : mapUsoCorreto)
     {
        std::cout << elem.first << " " << elem.second << " " << "\n";
     }

  }

	return 0;

}
