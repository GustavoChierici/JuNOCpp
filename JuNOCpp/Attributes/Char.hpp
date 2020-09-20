#pragma once
#include "Attribute.hpp"

namespace JuNOCpp
{
    namespace Attributes
    {
        class Char: public Attribute
        {
        private:
            char currentStatus;
            char previousStatus;
        public:
            Char(char value = '_');
            ~Char();

            void setStatus(char status);

            //void notifyPremises();

            char getStatus();
        };
    }
}