#pragma once

#include "Premise.hpp"
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

    public:
        Condition();
        ~Condition();

        void addPremise(Premise* prm);

        void conditionalCheck(bool status);
        void referenceRule(Rule* rule);

    };

}
