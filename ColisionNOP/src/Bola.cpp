#include "Bola.h"

Bola::Bola(int x /*= 0*/, int y /*= 0*/, int v_x /*= 1*/, int v_y /*= 1*/) :
    at_pos_x{x}, at_pos_y{y}, vx{v_x}, vy{v_y}, at_mover{false}
{
}

Bola::~Bola()
{
}

NOP::Attribute<int>* Bola::getX() {
    return &at_pos_x;
}

NOP::Attribute<int>* Bola::getY() {
    return &at_pos_y;
}

NOP::Attribute<bool>* Bola::getAtMover() {
    return &at_mover;
}


void Bola::mtMover() {
    at_pos_x = at_pos_x.getCurrentStatus() + vx;
    at_pos_y = at_pos_y.getCurrentStatus() + vy;
}

void Bola::mtInverterVX() {
    vx *= -1;
}

void Bola::mtInverterVY() {
    vy *= -1;
}
