#include "Double.hpp"

namespace JuNOCpp
{
    namespace Attributes
    {
        Double::Double(double value /* = "0.0" */)
        {
            this->currentStatus = value;
            this->previousStatus = value;
        }

        Double::~Double()
        {
        }

        void Double::setStatus(double status)
        {
            this->previousStatus = this->currentStatus;
            this->currentStatus = status;
            notifyPremises(this->currentStatus, this->previousStatus);
        }

        double Double::getStatus()
        {
            return this->currentStatus;
        }
    }
}