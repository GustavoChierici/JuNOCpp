#pragma once
#include "../Table.hpp"
#include "../Premise.hpp"
#include "../CustomString.hpp"

namespace JuNOCpp
{
    namespace Attributes
    {
        class Attribute {
        protected:
            Table<Premise> premises;
            //std::unordered_map<int, Premise*> premises;

        public:
            Attribute();
            ~Attribute();

            void notifyPremises(int current, int previous);
            void notifyPremises(CustomString current, CustomString previous);
            void notifyPremises(double current, double previous);

            /*std::unordered_map<int, Premise*>**/Table<Premise>* getTable();
        };
    }
}
