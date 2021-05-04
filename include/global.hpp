#include <string>
#include <map>
using namespace std;

extern int data_section_start;
extern int text_section_start;
extern int total_section_space;
extern string gb_bitmap;
extern map<string, int> mapUsoAux;
extern multimap<string, int> mapUso;
extern map<string, int> mapDefinicoes;
extern int fator[3];
extern int idArquivo;

//LIGADOR

extern string codigo_lig;
