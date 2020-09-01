#pragma once
#include "../Table.hpp"
#include "../Premise.hpp"

namespace JuNOCpp
{
    namespace Attributes
    {
        class Attribute {
        protected:
            Table<Premise> premises;
            void* currentStatus;
            void* previousStatus;

        public:
            Attribute();
            ~Attribute();

            void notifyPremises();

            Table<Premise>* getTable();
        };
    }
}
