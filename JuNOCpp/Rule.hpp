#pragma once

#include "./Condition.hpp"
#include "./Attributes/Integer.hpp"
#include "./Attributes/Boolean.hpp"
#include "./Attributes/String.hpp"
#include "./Attributes/Char.hpp"
#include "./Attributes/Double.hpp"
#include "Instigation.hpp"
#include "Method.hpp"


namespace JuNOCpp
{
    class Action;
    class Rule
    {
    private:
        Condition* cond;
        Action* action;
        Attributes::Attribute* attr;
        void* exec_value;

        void (*exec)(Attributes::Attribute*, void*, Action*);

        int mode;

    public:
        static int counter;

        const static int COMPLETE = 0;
        const static int INCOMPLETE = 1;
        const static int DERIVED = 2;

    public:
        Rule(CustomString mode = "CONJUNCTION", int rl_mode = Rule::COMPLETE);

        ~Rule();

        void addPremise(Attributes::Integer* pattr, const int value, CustomString mode = "EQUAL");
        void addPremise(Attributes::Boolean* pattr, const bool , CustomString mode = "EQUAL");
        void addPremise(Attributes::String* pattr, CustomString value, CustomString mode = "EQUAL");
        void addPremise(Attributes::Char* pattr, const char value, CustomString mode = "EQUAL");
        void addPremise(Attributes::Double* pattr, const double value, CustomString mode = "EQUAL");
        void addPremise(Premise* pprm);

        void addSubcondition(CustomString mode = "CONJUNCTION");
        void addSubcondition(SubCondition* subcond);
        void addPremiseToSubCondition(Attributes::Integer* pattr, const int value, CustomString mode = "EQUAL");
        void addPremiseToSubCondition(Attributes::Boolean* pattr, const bool value, CustomString mode = "EQUAL");
        void addPremiseToSubCondition(Attributes::String* pattr, CustomString value, CustomString mode = "EQUAL");
        void addPremiseToSubCondition(Attributes::Char* pattr, const char value, CustomString mode = "EQUAL");
        void addPremiseToSubCondition(Attributes::Double* pattr, const double value, CustomString mode = "EQUAL");
        void addPremiseToSubCondition(Premise* pprm);

        void referenceAttr(Attributes::Integer* attr, int exec_value);
        void referenceAttr(Attributes::Boolean* attr, bool exec_value);
        void referenceAttr(Attributes::String* attr, CustomString exec_value);
        void referenceAttr(Attributes::Char* attr, char exec_value);
        void referenceAttr(Attributes::Double* attr, double exec_value);

        void addInstigation(Instigation* inst);
        void addInstigation(Method* mt);
        void addInstigation(Attributes::Integer* attr, int value);

        void execute();

    };
}

