#ifndef LIGADOR_H
#define LIGADOR_H

#include <map>
#include <string>

#include "helper.hpp"
#include "fileHelper.hpp"

class Ligador{
private:
    string arquivoLig;

public:
    Ligador(string arquivoL);
    ~Ligador();

  	void ligar();
    void alinharCodigo();
    int extraiFatorC();

};


#endif
