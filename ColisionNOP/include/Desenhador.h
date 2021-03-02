#ifndef DESENHADOR_H
#define DESENHADOR_H

#include <string>

class Desenhador
{
    public:
        Desenhador(unsigned int x, unsigned int y);
        ~Desenhador();

        void desenhar(int xBola, int yBola) const;

    private:
        unsigned int dimX;
        unsigned int dimY;
        std::string parede_vertical;
        std::string linha_vazia;
};

#endif // DESENHADOR_H
