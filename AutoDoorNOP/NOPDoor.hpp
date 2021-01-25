#pragma once

#include "JuNOC++.hpp"

class NOPDoor
{
public:
    NOP::Attribute<bool> at_is_open;
public:
    NOPDoor(bool value = false) : at_is_open{value} {}

    ~NOPDoor()
    {
    }
};