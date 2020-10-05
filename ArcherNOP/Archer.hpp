#pragma once

#include "./JuNOCpp/FBE.hpp"

using namespace JuNOCpp;
using namespace Attributes;

class Archer: public FBE
{
public:
    Boolean* atArcherStatus;
public:
    Archer()
    {
        this->atArcherStatus = new Boolean();
        this->insertAttribute(this->atArcherStatus);
    }
    ~Archer()
    {
        delete this->atArcherStatus;
    }
};
