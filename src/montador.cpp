#ifndef MONTADOR
#define MONTADOR

#include "../include/montador.hpp"
#include "../include/global.hpp"

using namespace std;

Montador::Montador(FileHandler *fileHandler) {
    this->arquivo = fileHandler;
}

int Montador::sizeInstDiretiva(const string &instrucao) {
    if (instrucao == "COPY") {
        return 3;
    } else if (instrucao == "STOP" or instrucao == "SPACE" or instrucao == "CONST") {
        return 1;
    } else if (instrucao == "SECTION" or instrucao == "BEGIN" or instrucao == "END" or instrucao == "PUBLIC" or instrucao == "EXTERN") {
        return 0;
    } else {
        return 2;
    }
};

void Montador::validaOPlinha(const Linha &linha) {
    bool isValida;
    if (linha.operacao == "COPY") {
        isValida = !linha.op1.empty() and !linha.op2.empty();
    }
    else if (linha.operacao == "STOP" or linha.operacao == "SPACE" or linha.operacao == "BEGIN" or linha.operacao == "END" or linha.operacao == "EXTERN") {
        isValida = linha.op1.empty() and linha.op2.empty();
    }
    else {
        isValida = !linha.op1.empty() and linha.op2.empty();
        if (linha.operacao == "CONST") {

            if (!isInteger(linha.op1)) {
                throw EnumExcecao(EnumExcecao::OPERANDO_INVALIDO);
            }
            isValida = isValida and isInteger(linha.op1);
        }
        else if (linha.operacao == "SECTION") {
            if (linha.op1 != "DATA" and linha.op1 != "TEXT") {
                throw EnumExcecao(EnumExcecao::OPERANDO_INVALIDO);
            }
            isValida = isValida and (linha.op1 == "DATA" or linha.op1 == "TEXT");
        }
    }
    if (!isValida) {
        throw EnumExcecao(EnumExcecao::QTD_OP_ERRADA);
    }
}

void Montador::primeiraPassagem(bool toBeLinked) {
    string linha;
    int contadorPosicao = 0, contadorLinha = 0, auxCount = 0, flagTxtS = 0, flagDataS = 0, flagDirLink = 0, contPostText, contPostData, flagBegin = 0, existeDirLink = 0;
    contPostText = text_section_start;
    contPostData = data_section_start;

//    cout << "(montador)text section start: " << text_section_start << '\n' << "(montador)data section start: "<< data_section_start << '\n';

    while (!arquivo->hasEnd()) {
        try {
            arquivo->getLine(&linha);

            if(flagDataS == 0 && flagTxtS == 1){
              contPostText += 1;
            }
            if(flagDataS == 1){
              contPostData += 1;
            }

            if (linha.empty()) continue;
            Linha l = splitLinha(linha);
//            cout << linha << '\n';

//            cout << linha << "  | flag diretivalink: " << flagDirLink << "\n";
//            cout << "    |  l.operacao: " << l.operacao << "   ";


            if ((l.operacao == "BEGIN" or l.operacao == "END") and !toBeLinked){
                throw EnumExcecao(EnumExcecao::BEGIN_END_NOT_NEEDED);
            }

            if(l.op1 == "DATA" or l.operacao == "CONST" or l.operacao == "SPACE")
              flagDataS = 1;

            if(l.op1 == "TEXT" or (mapInstrucao.end() != mapInstrucao.find(l.operacao)))
              flagTxtS = 1;

            if((mapDiretivaLink.end() != mapDiretivaLink.find(l.operacao))){
              flagDirLink = 1;
              existeDirLink = 1;
              mapPresencaDir[l.operacao] = contadorPosicao;
            }
            if(!(mapDiretivaLink.end() != mapDiretivaLink.find(l.operacao)))
              flagDirLink = 0;




// alocando bitmap  ----> VERIFICAR O QUE FAZER COM "SPACE" E CHECAR OPERANDOS
            if (l.operacao != "SECTION" and l.operacao != "BEGIN" and l.operacao != "END" and l.operacao != "PUBLIC" and l.operacao != "EXTERN" and !l.operacao.empty()){
                if(flagDataS == 0 && flagTxtS == 1)
                  bitmap = bitmap + "0";

                else if(flagDataS == 1){
                  bitmap = "0" + bitmap;
                }
            }

            if (l.operacao != "CONST" and l.operacao != "SECTION" and l.operacao != "SPACE" and  l.operacao != "BEGIN" and l.operacao != "END" and l.operacao != "PUBLIC" and l.operacao != "EXTERN" and !l.op1.empty()){
                bitmap = bitmap + "1";
                if (!l.op2.empty()){
                  bitmap = bitmap + "1";
                }
            }


            if (!l.rotulo.empty()) { //checa se há rotulo
                if (mapSimbolos.end() != mapSimbolos.find(l.rotulo)) {//busca na tabela se há repetido. caso afirmativo -> erro rotulo rep

                    throw EnumExcecao(EnumExcecao::DECLARACAO_ROT_REP);
                }
                else {//caso negativo -> insere rotulo

                    mapSimbolos[l.rotulo] = contadorPosicao;
                }
            }

            if (mapInstrucao.end() != mapInstrucao.find(l.operacao)) {//procura se é instrucao existente
                contadorPosicao += sizeInstDiretiva(l.operacao);
            }
            else {

                if (mapDiretiva.end() != mapDiretiva.find(l.operacao)) { //procura se é diretiva existente
                    contadorPosicao += sizeInstDiretiva(l.operacao);
                }
                else {
                    throw EnumExcecao(EnumExcecao::DIRETIVA_INST_INVALID); //caso nao seja -> erro operacao
                }
            }

            //map mapUso
            if(l.operacao == "PUBLIC"){
                mapDefinicoes[l.op1] = contadorPosicao;
            }

            if(l.operacao == "EXTERN"){
                mapUsoAux[l.rotulo] = contadorPosicao;
            }

            if(mapUsoAux.end() != mapUsoAux.find(l.op1)){
              mapUso.emplace(l.op1, contadorPosicao-1);
            }

            if(!l.op2.empty() and mapUsoAux.end() != mapUsoAux.find(l.op2)){
              mapUso.emplace(l.op2, contadorPosicao-1);
            }

        } catch (EnumExcecao &e) {
            if(flagDataS == 0){
              errors.pushErro(e.error, linha, contPostText);
              continue;
            }
            else{
              errors.pushErro(e.error, linha, contPostData);
              continue;
            }
        }
    }
//    cout << flagDirLink;
    try{
      if(toBeLinked and ((mapPresencaDir.end() == mapPresencaDir.find("BEGIN")) or (mapPresencaDir.end() == mapPresencaDir.find("END")))) {
        throw EnumExcecao(EnumExcecao::BEGIN_END_AUSENTE);
      }
    } catch (EnumExcecao &e) {
        errors.pushErro(e.error, linha, contPostText);
    }

    for(auto e1 : mapDefinicoes){
      for(auto e2 : mapSimbolos){
        if(e1.first == e2.first)
          mapDefinicoes[e1.first] = e2.second;
      }
    }

    for(auto elem : mapUso)
    {
       std::cout << elem.first << " " << elem.second << " " << "\n";
    }

    arquivo->resetFile();
}

string Montador::segundaPassagem(bool toBeLinked) {
    string linha;
    string code;
    int contadorPosicao = 0, contadorLinha = 0, auxCount = 0, flagTxtS, flagDirLink = 0, flagDataS = 0, contPostText, contPostData;
    contPostText = text_section_start;
    contPostData = data_section_start;

    while (!arquivo->hasEnd()) {
        try {
            arquivo->getLine(&linha);

            if(flagDataS == 0 && flagTxtS == 1){
              contPostText += 1;
            }

            if(flagDataS == 1){
              contPostData += 1;
            }

            if (linha.empty()) continue;
            Linha l = splitLinha(linha, false);

//            cout << l.operacao << '\n';

            if(l.op1 == "DATA" or (mapDiretiva.end() != mapDiretiva.find(l.operacao)))
              flagDataS = 1;

            if(l.op1 == "TEXT" or (mapInstrucao.end() != mapInstrucao.find(l.operacao)))
              flagTxtS = 1;

            if((mapDiretivaLink.end() != mapDiretivaLink.find(l.operacao)))
              flagDirLink = 1;

            if (l.operacao != "CONST" and l.operacao != "SECTION") { //removendo possibilidade de ser diretiva
                if ((mapSimbolos.end() == mapSimbolos.find(l.op1) and !l.op1.empty()) or (
                        mapSimbolos.end() == mapSimbolos.find(l.op2) and !l.op2.empty())) {
                    throw EnumExcecao(EnumExcecao::DECLARACAO_ROT_AUSENTE);
                }
            }

            if (mapInstrucao.end() != mapInstrucao.find(l.operacao)) {//localiza instrucao
                contadorPosicao += sizeInstDiretiva(l.operacao);
                validaOPlinha(l);

                //codigo de saida
                code += to_string(mapInstrucao[l.operacao]) + ' ';
                if (!l.op1.empty()) {
                    code += to_string(mapSimbolos[l.op1]) + ' ';
                }
                if (!l.op2.empty()) {
                    code += to_string(mapSimbolos[l.op2]) + ' ';
                }
            }
            else {
                if (mapDiretiva.end() != mapDiretiva.find(l.operacao)) {//localiza diretiva
                    validaOPlinha(l);

                    //codigo de saida p/ diretiva
                    if (l.operacao == "CONST") {
                        code += l.op1 + ' ';
                    }
                    else if (l.operacao == "SPACE") {
                        code += "0 ";
                    }
                } else {
                    throw EnumExcecao(EnumExcecao::DIRETIVA_INST_INVALID);
                }
            }
        } catch (EnumExcecao &e) {
            if(flagDataS == 0){
              errors.pushErro(e.error, linha, contPostText);
              continue;
            }
            else{
              errors.pushErro(e.error, linha, contPostData);
              continue;
            }
        }
    }

    if (errors.emptyStack()) {
        throw PassagemException("Montagem", errors.collectErros());
    }
    gb_bitmap = bitmap;

/*
    for(auto elem : mapSimbolos){
        std::cout << elem.first << " " << elem.second << " " << "\n";
    }
*/

    return code;
}

#endif
