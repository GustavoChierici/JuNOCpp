#pragma once
#include "Attribute.hpp"

namespace JuNOCpp
{
    namespace Attributes
    {
        class Double: public Attribute
        {
        private:
            double currentStatus;
            double previousStatus;
        public:
            Double(double value = 0.0);
            ~Double();

            void setStatus(double status);

            //void notifyPremises();

            double getStatus();
        };
    }
}
