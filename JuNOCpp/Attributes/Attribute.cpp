#include "Attribute.hpp"
using namespace JuNOCpp;
using namespace Attributes;

Attribute::Attribute()
{
}

Attribute::~Attribute()
{
}

void Attribute::notifyPremises(int current, int previous)
{
    Premise* aux = premises[previous];
    if(aux)
        aux->conditionalCheck(current);
    aux = premises[current];
    if(aux)
        aux->conditionalCheck(current);
}

void Attribute::notifyPremises(CustomString current, CustomString previous)
{
    Premise* aux = premises[previous];
    if(aux)
        aux->conditionalCheck(current);
    aux = premises[current];
    if(aux)
        aux->conditionalCheck(current);
}

void Attribute::notifyPremises(double current, double previous)
{
    Premise* aux = premises[previous];
    if(aux)
        aux->conditionalCheck(current);
    aux = premises[current];
    if(aux)
        aux->conditionalCheck(current);
}


/*std::unordered_map<int, Premise*>**/Table<Premise>* Attribute::getTable()
{
    return &premises;
}
