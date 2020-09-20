#include "Char.hpp"

namespace JuNOCpp
{
    namespace Attributes
    {
        Char::Char(char value /* = '_' */)
        {
            this->currentStatus = value;
            this->previousStatus = value;
        }

        Char::~Char()
        {
        }

        void Char::setStatus(char status)
        {
            this->previousStatus = this->currentStatus;
            this->currentStatus = status;
            notifyPremises(this->currentStatus, this->previousStatus);
        }

        char Char::getStatus()
        {
            return this->currentStatus;
        }
    }
}