#ifndef AUX_ARQUIVO_H
#define AUX_ARQUIVO_H

#include <string>
#include <map>
#include "fileHelper.hpp"
#include "error.hpp"
#include "helper.hpp"

using namespace std;

class AuxArquivo {
public:
    AssembleErr errors;

//    int data_section_start = 0;
//    int text_section_start = 0;

    map<string, string> mapComponente = {};
    PFile *arquivo;

    FileHandler *arquivoPronto;


    explicit AuxArquivo(const string &nomeArquivo);

    void extraiCode();

    map<string, int> mapInstrucao = {
            {"ADD", 1},
            {"SUB", 2},
            {"MUL", 3},
            {"DIV", 4},
            {"JMP", 5},
            {"JMPN", 6},
            {"JMPP", 7},
            {"JMPZ", 8},
            {"COPY", 9},
            {"LOAD", 10},
            {"STORE", 11},
            {"INPUT", 12},
            {"OUTPUT", 13},
            {"STOP", 14}
    };

    map<string, int> mapDiretiva = {
            {"SECTION", 0},
            {"SPACE",   1},
            {"CONST",   1},
            {"BEGIN",   0},
            {"END",     0},
            {"PUBLIC",  0},
            {"EXTERN",  0},
    };
    
};

#endif
