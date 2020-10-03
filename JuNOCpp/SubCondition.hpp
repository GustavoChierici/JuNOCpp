#pragma once

#include "Premise.hpp"
#include "CustomString.hpp"
#include <iostream>
#include "Condition.hpp"

namespace JuNOCpp
{
    class SubCondition: public Condition
    {
    private:
        Condition* condition;
        bool current_status;
        bool previous_status;

    public:
        SubCondition(CustomString mode = "CONJUNCTION");
        ~SubCondition();

        void addPremise(Premise* prm);

        void conditionalCheck(bool status);
        void referenceCondition(Condition* cond);
    };
}
