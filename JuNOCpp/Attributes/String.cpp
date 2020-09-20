#include "String.hpp"

namespace JuNOCpp
{
    namespace Attributes
    {
        String::String(CustomString value /* = "_" */)
        {
            this->currentStatus = value;
            this->previousStatus = value;
        }

        String::~String()
        {
        }

        void String::setStatus(CustomString status)
        {
            this->previousStatus = this->currentStatus;
            this->currentStatus = status;
            notifyPremises(this->currentStatus, this->previousStatus);
        }

        CustomString String::getStatus()
        {
            return this->currentStatus;
        }
    }
}