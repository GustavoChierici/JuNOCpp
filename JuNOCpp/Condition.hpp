#pragma once

#include "Premise.hpp"
#include "CustomString.hpp"
#include "List.hpp"
#include <iostream>

namespace JuNOCpp
{
    class Rule;
    class SubCondition;
    class Condition
    {
    protected:
        int quantity;
        int approved_premises_and_subconds;
        Rule* rule;
        CustomString mode;
        List<SubCondition> subconditions;
        SubCondition* current_subcondition;

    public:
        Condition(CustomString mode = "CONJUNCTION");
        ~Condition();

        void addPremise(Premise* prm);

        void addSubCondition(CustomString mode = "CONJUNCTION");
        void addSubCondition(SubCondition* subcond);
        void addPremiseToSubCondition(Premise* prm);

        virtual void conditionalCheck(bool status);
        void referenceRule(Rule* rule);

    };

}
