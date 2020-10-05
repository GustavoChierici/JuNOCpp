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