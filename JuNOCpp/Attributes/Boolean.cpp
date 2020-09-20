#include "Boolean.hpp"

namespace JuNOCpp
{
    namespace Attributes
    {
        Boolean::Boolean(bool value /* = false */)
        {
            this->currentStatus = value;
            this->previousStatus = value;
        }

        Boolean::~Boolean()
        {
        }

        void Boolean::setStatus(bool status)
        {
            this->previousStatus = this->currentStatus;
            this->currentStatus = status;
            notifyPremises(this->currentStatus, this->previousStatus);
        }

        bool Boolean::getStatus()
        {
            return this->currentStatus;
        }

        // void Boolean::notifyPremises()
        // {
        //     Premise* aux = premises[*(int*)this->previousStatus];
        //     if(aux)
        //         aux->conditionalCheck(this->getStatus());
        //     aux = premises[*(int*)this->currentStatus];
        //     if(aux)
        //         aux->conditionalCheck(this->getStatus());
        // }
    }
}