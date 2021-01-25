#pragma once

#include "../JuNOCpp/includes/JuNOC++.hpp"

class Apple
{
public:
    NOP::Attribute<bool> atAppleStatus;
    NOP::Attribute<char> atAppleColor;
public:
    Apple() : atAppleColor{'G'} {}
    ~Apple()
    {
    }
};
