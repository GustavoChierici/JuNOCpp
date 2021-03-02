#include "Desenhador.h"

#include <iostream>

Desenhador::Desenhador(unsigned int x, unsigned int y) : dimX{x}, dimY{y}, parede_vertical{'|'+ std::string(4*x+2, '_') + "|\n"},
linha_vazia{'|'+ std::string(4*x+2, ' ') + "|\n"}
{
}

Desenhador::~Desenhador()
{
}

void Desenhador::desenhar(int xBola, int yBola) const {
    std::cout << std::string(50, '\n') << parede_vertical;
    for (int i = -dimY; i <= (int)dimY; ++i) {
        if (i != yBola) std::cout << linha_vazia;
        else std::cout << '|' <<  std::string(2*(dimX + xBola), ' ') << "O " <<
        std::string(2*(dimX  - xBola), ' ') << "|\n";
    }

    std::cout << parede_vertical << std::flush;
}
