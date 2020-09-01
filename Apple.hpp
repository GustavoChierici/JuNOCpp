#pragma once

#include "./JuNOCpp/FBE.hpp"

using namespace JuNOCpp;
using namespace Attributes;

class Apple: public FBE
{
public:
    Integer* atAppleStatus;
    Integer* atAppleColor; //0 - Green; 1 - Red
public:
    Apple()
    {
        this->atAppleStatus = new Integer(0);
        this->insertAttribute(this->atAppleStatus);
        this->atAppleColor = new Integer(0);
        this->insertAttribute(this->atAppleColor);
    }
    ~Apple()
    {
        delete this->atAppleStatus;
        delete this->atAppleColor;
    }
};
