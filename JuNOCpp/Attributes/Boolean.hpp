#pragma once
#include "Attribute.hpp"

namespace JuNOCpp
{
    namespace Attributes
    {
        class Boolean: public Attribute
        {
        private:
            bool currentStatus;
            bool previousStatus;
        public:
            Boolean(bool value = false);
            ~Boolean();

            void setStatus(bool status);

            bool getStatus();

            //void notifyPremises();
        };
    }
}
