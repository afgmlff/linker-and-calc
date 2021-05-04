#include <iostream>
#include <fstream>
#include <sstream>
#include "../../include/ligador.hpp"

using namespace std;

Ligador::Ligador(string arquivoL) {
	arquivoLig = arquivoL;
}

Ligador::~Ligador() {}

void Ligador::ligar(){
  alinharCodigo();
  //extraiFatorC();

}

void Ligador::alinharCodigo(){
  ifstream file;
  file.open(arquivoLig);
  if(file.is_open()){
    cout << "Arquivo inicializado: " << arquivoLig << '\n';
  }
}

int Ligador::extraiFatorC(){

}
