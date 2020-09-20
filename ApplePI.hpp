#pragma once
#include "./JuNOCpp/CustomString.hpp"

class ApplePI
{
public:
    bool status;
    CustomString color;
public:
    ApplePI()
    {
        status = false;
        color = "GREEN";
    }
    ~ApplePI(){}
};

