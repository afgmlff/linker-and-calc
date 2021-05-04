#include <iostream>
#include <fstream>
#include <sstream>
#include "../../include/ligador.hpp"
#include "../../include/global.hpp"

using namespace std;

Ligador::Ligador(string arquivoL) {
	arquivoLig = arquivoL;
}

void Ligador::populate_tuple(){
  ifstream file;
  string pAux, linha, linha2;
  char bit_id[99];
  int i = fator[idArquivoLig-1], teste[99], numero, tamanho, contL = 1;



  file.open(arquivoLig);
  while(getline(file, linha)){
    if(contL == 3){
      linha2 = (linha.erase(0,3));
    }
    if(linha.find("T:") == 0){
      linha = (linha.erase(0,3));
      break;
    }
    contL++;
  }
  istringstream iss(linha);
  while ( getline( iss, pAux, ' ' ) ) {
    teste[i] = atoi(pAux.c_str());
//    cout << teste[i] << endl;
    i++;
  }

  i = fator[idArquivoLig-1];
  tamanho = i + extraiFatorC();
//  cout << "i inicial: " << i << endl;
//  cout << "i final: " << tamanho << endl;

  int j = fator[idArquivoLig-1];

  for(char character : linha2){
    bit_id[j] = character;
//    cout << bit_id[j] << " ";
    j++;
  }


  while(i < tamanho){
    mapBitValue.push_back(make_tuple(bit_id[i], teste[i]));

//    cout << i << ": " <<get<0>(mapBitValue[i]) << " | " << get<1>(mapBitValue[i]) << endl;
    i++;
  }



}

map<string, int> s_int_to_map(string const& s)
{
    map<string, int> m;

    string key, val;
    istringstream iss(s);

    while(getline(getline(iss, key, ',') >> ws, val))
        m[key] = stoi(val);

    return m;
}



Ligador::~Ligador() {}

void Ligador::ligar(){
  alinharCodigo();
  extraiFatorC();
  if(idArquivoLig == idLastArq)
    corrigePendencia();

}

std::string &lstrip(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}


void Ligador::alinharCodigo(){
  map<string, int> mapAux = {};
  map<string, int> mapAux2 = {};

  ifstream file;
  ofstream outfile;
  string linha, auxS;
  string saida_ligador = "test_files_asm/saida_ligador.obj";
  int contL = 1;

  fator[idArquivoLig] = extraiFatorC();

//  cout << fator[idArquivoLig-1];
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
        mapGlobalDef[elem.first] = (elem.second + fator[idArquivoLig-1]);  //fator de correcao na tabela def global
      }
    }

    if(linha.find("U:") == 0){
      auxS = linha.erase(0,3);
      mapAux2 = s_int_to_map(auxS.erase(auxS.size() - 1));
      for(auto elem : mapAux2){
        mapUsoCorreto.emplace(elem.first, elem.second + fator[idArquivoLig-1]);
      }
    }

    contL++;
  }
  outfile << codigo_lig;
  file.close();
  outfile.close();

  populate_tuple();
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
//    cout << fatorC;
    return fatorC;
}

void Ligador::corrigePendencia(){
  int tamanho = fator[0] + fator[1] + fator[2] + fator[3];
  int i = 0, enderecoAux = 0;
  string aux;

  for(auto elemU : mapUsoCorreto){
    aux = elemU.first;
      for(auto elemD : mapGlobalDef){
        if(elemD.first == aux){
          cout << "achei!" <<endl;
        }
      }
  }

  while(i < tamanho){
    cout << i << ": " <<get<0>(mapBitValue[i]) << " | " << get<1>(mapBitValue[i]) << endl;
    i++;
  }

}
