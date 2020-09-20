#include "Integer.hpp"
using namespace JuNOCpp;
using namespace Attributes;

Integer::Integer(int value)
{
    this->currentStatus = value;
    this->previousStatus = value;
}

Integer::~Integer()
{
}

void Integer::setStatus(int status)
{
    this->previousStatus = this->currentStatus;
    this->currentStatus = status;
    notifyPremises(this->currentStatus, this->previousStatus);
}

int Integer::getStatus()
{
    return this->currentStatus;
}

// void Integer::notifyPremises()
// {
//     Premise* aux = premises[this->previousStatus];
//     if(aux)
//         aux->conditionalCheck(this->getStatus());
//     aux = premises[this->currentStatus];
//     if(aux)
//         aux->conditionalCheck(this->getStatus());
// }
