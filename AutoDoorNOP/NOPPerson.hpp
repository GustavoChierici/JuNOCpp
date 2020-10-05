#pragma once

#include "JuNOCpp/JuNOC++.hpp"

class NOPPerson: public FBE
{
public:
    Boolean* at_pos_door_front;
    Double* at_velocity;

public:
    NOPPerson(bool value = false, double velocity = 0.0)
    {
        this->at_pos_door_front = new Boolean(value);
        this->at_velocity = new Double(velocity);
    }

    ~NOPPerson()
    {
        delete this->at_pos_door_front;
        delete this->at_velocity;
    }
};