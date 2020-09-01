#pragma once
#include "Attribute.hpp"

namespace JuNOCpp
{
    namespace Attributes
    {
        class Integer: public Attribute
        {
        public:
            Integer(int value = 0);
            ~Integer();

            void setStatus(int status);

            int getState();
        };
    }
}
