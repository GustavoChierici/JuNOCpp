#pragma once

#include "./Condition.hpp"
#include "./Attributes/Integer.hpp"

namespace JuNOCpp
{
    class Rule
    {
    private:
        Condition* cond;
        Attributes::Integer* attr;
        int exec_value;

    public:
        Rule(const int exec_value = 0, Condition* pcond = nullptr);

        ~Rule();

        void addPremise(Attributes::Integer* pattr, const int value);

        void addPremise(Premise* pprm);

        void addCondition(Condition* cond);

        void referenceAttr(Attributes::Integer* attr);

        void execute();

    };

}

