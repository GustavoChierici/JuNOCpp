#pragma once

#include "Premise.hpp"
#include "CustomString.hpp"
#include <iostream>

namespace JuNOCpp
{
    class Rule;
    class Condition
    {
    private:
        int quantity;
        int true_premises;
        Rule* rule;
        CustomString mode;

    public:
        Condition(CustomString mode = "CONJUNCTION");
        ~Condition();

        void addPremise(Premise* prm);

        void conditionalCheck(bool status);
        void referenceRule(Rule* rule);

    };

}
