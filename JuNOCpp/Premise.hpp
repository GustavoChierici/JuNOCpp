#pragma once
#include <vector>
#include "CustomString.hpp"
#include "List.hpp"
#include <functional>

namespace JuNOCpp
{
    class Condition;
    class SubCondition;
    namespace Attributes
    {
        class Attribute;
    }
    class Premise{
    private:
        Attributes::Attribute* attr_reference;
        int value;
        CustomString str_value;
        char char_value;
        double double_value;
        bool status;
        bool previous_status;
        List<Condition> conditions;
        List<SubCondition> subconditions;
        int mode; // 0 - NOT_EQUAL ou !=; 1 - EQUAL ou ==; 2 - GREATER_THAN ou >; 3 - GREATER_OR_EQUAL_THAN ou >=; 4 - LESS THAN ou <; 5 - LESS_OR_EQUAL_THAN ou <=;  
        bool (*comp_int)(int, int);
        bool (*comp_double)(double, double);
        bool (*comp_str)(CustomString, CustomString);

    public:
        Premise(CustomString mode = "EQUAL");
        ~Premise();
        Premise(Attributes::Attribute* attr, const int value, CustomString mode = "EQUAL");

        void setAttribute(Attributes::Attribute* attr, int value);
        void setAttribute(Attributes::Attribute* attr, bool value);
        void setAttribute(Attributes::Attribute* attr, CustomString value);
        void setAttribute(Attributes::Attribute* attr, const char value);
        void setAttribute(Attributes::Attribute* attr, const double value);

        void conditionalCheck(int value);
        void conditionalCheck(bool value);
        void conditionalCheck(CustomString value);
        void conditionalCheck(char value);
        void conditionalCheck(double value);

        void referenceCondition(Condition* pcond);

        void referenceSubCondition(SubCondition* subcond);

        void notifyConditions();
    };

}
