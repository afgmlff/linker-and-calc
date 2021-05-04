#include "../include/global.hpp"

int data_section_start = 0;
int text_section_start = 0;
string gb_bitmap = "";
map<string, int> mapUsoAux = {};
multimap <string, int> mapUso = {};
map<string, int> mapDefinicoes = {};
int fator[4] = {0, 0, 0, 0};
int idArquivo = 1;

//Ligador
string codigo_lig = "";
int idArquivoLig = 0;
map<string, int> mapGlobalDef = {};
