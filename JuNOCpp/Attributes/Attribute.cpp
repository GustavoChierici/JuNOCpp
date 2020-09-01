#include "Attribute.hpp"
using namespace JuNOCpp;
using namespace Attributes;

Attribute::Attribute()
{
    this->currentStatus = nullptr;
    this->previousStatus = nullptr;
}

Attribute::~Attribute()
{
    this->currentStatus = nullptr;
    this->previousStatus = nullptr;
}

void Attribute::notifyPremises()
{
    Premise* aux = premises[*(int*)this->previousStatus];
    if(aux)
        aux->conditionalCheck();
    aux = premises[*(int*)this->currentStatus];
    if(aux)
        aux->conditionalCheck();
}

Table<Premise>* Attribute::getTable()
{
    return &premises;
}
