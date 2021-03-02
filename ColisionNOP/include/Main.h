#ifndef MAIN_H_
#define MAIN_H_

#include "Bola.h"
#include "Desenhador.h"

class Main
{

private:
    Bola* bola;
    NOP::Rule rlOne;
    NOP::Rule rlTwo;
    NOP::Rule rlThree;
    unsigned int dimSalaX;
    unsigned int dimSalaY;
    Desenhador desenhador;

public:
    Main(unsigned int x, unsigned int y);
    virtual ~Main();

private:
    void initStartApplicationComponents();
    void initFactBase();
    void initRules();
    void initSharedEntities();
    void codeApplication();
};

#endif
