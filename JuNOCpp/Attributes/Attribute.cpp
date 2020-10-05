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

    List<Premise>::Element<Premise>* aux2 = this->especial_premises.getFirst();
    while(aux2 != nullptr)
    {
            aux2->getInfo()->conditionalCheck(current);
            aux2 = aux2->getNext();
    }
}

void Attribute::notifyPremises(CustomString current, CustomString previous)
{
    Premise* aux = premises[previous];
    if(aux)
        aux->conditionalCheck(current);
    aux = premises[current];
    if(aux)
        aux->conditionalCheck(current);

    List<Premise>::Element<Premise>* aux2 = this->especial_premises.getFirst();
    while(aux2 != nullptr)
    {
            aux2->getInfo()->conditionalCheck(current);
            aux2 = aux2->getNext();
    }
}

void Attribute::notifyPremises(double current, double previous)
{
    Premise* aux = premises[previous];
    if(aux)
        aux->conditionalCheck(current);
    aux = premises[current];
    if(aux)
        aux->conditionalCheck(current);
    
    List<Premise>::Element<Premise>* aux2 = this->especial_premises.getFirst();
    while(aux2 != nullptr)
    {
            aux2->getInfo()->conditionalCheck(current);
            aux2 = aux2->getNext();
    }
}

Table<Premise>* Attribute::getTable()
{
    return &premises;
}

List<Premise>* Attribute::getList()
{
    return &this->especial_premises;
}
