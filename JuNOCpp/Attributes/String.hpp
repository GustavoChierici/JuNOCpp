#pragma once

#include "Attribute.hpp"

namespace JuNOCpp
{
    namespace Attributes
    {
        class String: public Attribute
        {
        private:
            CustomString currentStatus;
            CustomString previousStatus;
        public:
            String(CustomString value = "_");
            ~String();

            void setStatus(CustomString status);

            //void notifyPremises();

            CustomString getStatus();
        };
    }  
}
