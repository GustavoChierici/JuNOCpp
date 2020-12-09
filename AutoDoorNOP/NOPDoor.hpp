#pragma once

#include "../JuNOCpp/JuNOC++.hpp"

class NOPDoor
{
public:
    NOP::Attribute<bool> at_is_open;
public:
    NOPDoor(bool value = false)
    {
        this->at_is_open = value;
    }

    ~NOPDoor()
    {
    }
};