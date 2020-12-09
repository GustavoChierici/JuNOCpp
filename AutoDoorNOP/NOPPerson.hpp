#pragma once

#include "../JuNOCpp/JuNOC++.hpp"

class NOPPerson
{
public:
    NOP::Attribute<bool> at_pos_door_front;
    NOP::Attribute<double> at_velocity;

public:
    NOPPerson(bool value = false, double velocity = 0.0)
    {
        this->at_pos_door_front = value;
        this->at_velocity = velocity;
    }

    ~NOPPerson()
    {
    }
};