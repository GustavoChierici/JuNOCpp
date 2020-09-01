#pragma once

#include "./JuNOCpp/FBE.hpp"

using namespace JuNOCpp;
using namespace Attributes;

class Archer: public FBE
{
public:
    Integer* atArcherStatus;
public:
    Archer()
    {
        this->atArcherStatus = new Integer(0);
        this->insertAttribute(this->atArcherStatus);
    }
    ~Archer()
    {
        delete this->atArcherStatus;
    }
};
