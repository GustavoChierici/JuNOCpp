#pragma once

#include "JuNOCpp/JuNOC++.hpp"

class NOPDoor: public FBE
{
public:
    Boolean* at_is_open;
public:
    NOPDoor(bool value = false)
    {
        this->at_is_open = new Boolean(value);
    }

    ~NOPDoor()
    {
        delete this->at_is_open;
    }
};