#pragma once

#include "./Condition.hpp"
#include "./Attributes/Integer.hpp"
#include "./Attributes/Boolean.hpp"
#include "./Attributes/String.hpp"
#include "./Attributes/Char.hpp"
#include "./Attributes/Double.hpp"


namespace JuNOCpp
{
    class Rule
    {
    private:
        Condition* cond;
        Attributes::Attribute* attr;
        int attr_type; // 0 - Integer; 1 - Boolean; 2 - String; 3 - Char; 4 - Double
        int exec_value_int;
        bool exec_value_bool;
        CustomString exec_value_str;
        char exec_value_char;
        double exec_value_double;

    public:
        Rule(CustomString mode = "CONJUNCTION");

        ~Rule();

        void addPremise(Attributes::Integer* pattr, const int value);
        void addPremise(Attributes::Boolean* pattr, const bool value);
        void addPremise(Attributes::String* pattr, CustomString value);
        void addPremise(Attributes::Char* pattr, const char value);
        void addPremise(Attributes::Double* pattr, const double value);
        void addPremise(Premise* pprm);

        void referenceAttr(Attributes::Integer* attr, const int exec_value);
        void referenceAttr(Attributes::Boolean* attr, const bool exec_value);
        void referenceAttr(Attributes::String* attr, CustomString exec_value);
        void referenceAttr(Attributes::Char* attr, const char exec_value);
        void referenceAttr(Attributes::Double* attr, const double exec_value);

        void execute();

    };

}

