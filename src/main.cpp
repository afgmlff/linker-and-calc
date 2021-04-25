#include <iostream>
#include "../include/montador.hpp"
#include "../include/auxArquivo.hpp"
#include "../include/helper.hpp"

int main(int argc, char **argv) {
    try {
        if (argc == 2) {// ./montador input.asm

            std::cout << "Arquivo de entrada: " << argv[1] << endl;
            AuxArquivo auxArquivo(argv[1]);
            auxArquivo.extraiCode();

            Montador montador(auxArquivo.arquivoPronto);
            montador.primeiraPassagem();
            criaSaidaMontador(montador.segundaPassagem(), argv[1]);
            std::cout << "Arquivo de saída: " << trocaExtensao(argv[1], ".obj") << std::endl;
        }
        else if (argc == 3){
          std::cout << "Arquivos de entrada: " << argv[1] << " " << argv[2] << endl;
          AuxArquivo auxArquivo(argv[1]);
          auxArquivo.extraiCode();

          Montador montador(auxArquivo.arquivoPronto);
          montador.primeiraPassagem();
          criaSaidaMontador(montador.segundaPassagem(), argv[1]);
          std::cout << "Arquivo de saída: " << trocaExtensao(argv[1], ".obj") << std::endl;

          AuxArquivo auxArquivo2(argv[2]);
          auxArquivo2.extraiCode();

          Montador montador2(auxArquivo2.arquivoPronto);
          montador2.primeiraPassagem();
          criaSaidaMontador(montador2.segundaPassagem(), argv[2]);
          std::cout << "Arquivo de saída: " << trocaExtensao(argv[2], ".obj") << std::endl;

        }
        else if (argc == 4){
          std::cout << "Arquivos de entrada: " << argv[1] << " " << argv[2] << " " << argv[3] << endl;
          AuxArquivo auxArquivo(argv[1]);
          auxArquivo.extraiCode();

          Montador montador(auxArquivo.arquivoPronto);
          montador.primeiraPassagem();
          criaSaidaMontador(montador.segundaPassagem(), argv[1]);
          std::cout << "Arquivo de saída: " << trocaExtensao(argv[1], ".obj") << std::endl;

          AuxArquivo auxArquivo2(argv[2]);
          auxArquivo2.extraiCode();

          Montador montador2(auxArquivo2.arquivoPronto);
          montador2.primeiraPassagem();
          criaSaidaMontador(montador2.segundaPassagem(), argv[2]);
          std::cout << "Arquivo de saída: " << trocaExtensao(argv[2], ".obj") << std::endl;

          AuxArquivo auxArquivo3(argv[3]);
          auxArquivo3.extraiCode();

          Montador montador3(auxArquivo3.arquivoPronto);
          montador3.primeiraPassagem();
          criaSaidaMontador(montador3.segundaPassagem(), argv[3]);
          std::cout << "Arquivo de saída: " << trocaExtensao(argv[3], ".obj") << std::endl;
        }
        else {
            printf("Favor, informar arquivo para execucao do montador. Ex.: \"./montador caminho/entrada.asm\n");
            return 1;
        }
    } catch (PassagemException &e) {
        std::cout << e.stackErros() << std::endl;
    }
    return 0;
};
