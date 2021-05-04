#include <string>
#include <map>
#include <vector>
#include <tuple>
using namespace std;

extern int data_section_start;
extern int text_section_start;
extern int total_section_space;
extern string gb_bitmap;
extern map<string, int> mapUsoAux;
extern multimap<string, int> mapUso;
extern map<string, int> mapDefinicoes;
extern int fator[4];
extern int idArquivo;

//LIGADOR

extern string codigo_lig;
extern int idArquivoLig;
extern map<string, int> mapGlobalDef;
extern multimap<string, int> mapUsoCorreto;
extern vector<tuple<char, int>> mapBitValue;
extern int idLastArq;
