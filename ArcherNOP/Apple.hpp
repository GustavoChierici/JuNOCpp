#pragma once

#include "./JuNOCpp/FBE.hpp"

using namespace JuNOCpp;
using namespace Attributes;

class Apple: public FBE
{
public:
    Boolean* atAppleStatus;
    Char* atAppleColor;
public:
    Apple()
    {
        this->atAppleStatus = new Boolean();
        this->insertAttribute(this->atAppleStatus);
        this->atAppleColor = new Char('G');
        this->insertAttribute(this->atAppleColor);
    }
    ~Apple()
    {
        delete this->atAppleStatus;
        delete this->atAppleColor;
    }
};
