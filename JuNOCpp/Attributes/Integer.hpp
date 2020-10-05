#pragma once
#include "Attribute.hpp"

namespace JuNOCpp
{
    namespace Attributes
    {
        class Integer: public Attribute
        {
        private:
            int currentStatus;
            int previousStatus;
        public:
            Integer(int value = 0);
            ~Integer();

            void setStatus(int status);

            int getStatus();
        };
    }
}
