#ifndef BOLA_H
#define BOLA_H

#include "JuNOC++.hpp"

class Bola
{
    public:
        Bola(int x = 0, int y = 0, int v_x = 1, int v_y = 1);
        ~Bola();
        NOP::Attribute<int>* getX();
        NOP::Attribute<int>* getY();
        NOP::Attribute<bool>* getAtMover();
    private:

        NOP::Attribute<int> at_pos_x;
        NOP::Attribute<int> at_pos_y;
        NOP::Attribute<bool> at_mover;
        int vx;
        int vy;
    public:
        void mtMover();
        void mtInverterVX();
        void mtInverterVY();

};

#endif // BOLA_H
