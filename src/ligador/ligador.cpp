#include <iostream>
#include <fstream>
#include <sstream>
#include "../../include/ligador.hpp"
#include "../../include/global.hpp"

using namespace std;

map<string, int> s_int_to_map(string const& s)
{
    map<string, int> m;

    string key, val;
    istringstream iss(s);

    while(getline(getline(iss, key, ',') >> ws, val))
        m[key] = stoi(val);

    return m;
}

Ligador::Ligador(string arquivoL) {
	arquivoLig = arquivoL;
}

Ligador::~Ligador() {}

void Ligador::ligar(){
  alinharCodigo();
  extraiFatorC();
//  aplicaFatorC();

}

std::string &lstrip(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}


void Ligador::alinharCodigo(){
  map<string, int> mapAux = {};

  ifstream file;
  ofstream outfile;
  string linha;
  string saida_ligador = "test_files_asm/saida_ligador.obj";
  int contL = 1;
  file.open(arquivoLig);
  outfile.open(saida_ligador);
  if(file.is_open()){
    cout << "Arquivo inicializado: " << arquivoLig << '\n';
  }
  while(getline(file, linha)){
    if(contL == 4){
      codigo_lig = codigo_lig + lstrip(linha.erase(0,2));

      }
    if(linha.find("D:") == 0){
      mapAux = s_int_to_map(linha.erase(0,3));
      for(auto elem : mapAux){
        mapGlobalDef[elem.first] = elem.second;
      }
    }
    contL++;
  }
  outfile << codigo_lig;
  file.close();
  outfile.close();
  fator[idArquivoLig] = extraiFatorC();
//  cout << fator[idArquivoLig -1]; //o fator de correção atual é o tamanho de espaço utilizado pelo módulo anterior



}

int Ligador::extraiFatorC(){
    ifstream fileAux;
    int fatorC = 0, contL = 1;
    string linha;
    fileAux.open(arquivoLig);
    while(getline(fileAux, linha)){
      if(contL == 2){
        fatorC = stoi(lstrip(linha.erase(0,2)));

        }
      contL++;
    }
    fileAux.close();
    return fatorC;
}
