#pragma once
#include "../Table.hpp"
#include "../Premise.hpp"
#include "../CustomString.hpp"
#include "../List.hpp"

namespace JuNOCpp
{
    namespace Attributes
    {
        class Attribute {        
        protected:
            Table<Premise> premises;
            List<Premise> especial_premises;

        public:
            Attribute();
            ~Attribute();

            void notifyPremises(int current, int previous);
            void notifyPremises(CustomString current, CustomString previous);
            void notifyPremises(double current, double previous);

            Table<Premise>* getTable();
            List<Premise>* getList();
        };
    }
}
