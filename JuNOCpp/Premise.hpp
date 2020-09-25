#pragma once
#include <vector>
#include "CustomString.hpp"
#include "List.hpp"

namespace JuNOCpp
{
    class Condition;
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

    public:
        Premise();
        ~Premise();
        Premise(Attributes::Attribute* attr, const int value);

        void setAttribute(Attributes::Attribute* attr, int value);
        void setAttribute(Attributes::Attribute* attr, bool value);
        void setAttribute(Attributes::Attribute* attr, CustomString value);
        void setAttribute(Attributes::Attribute* attr, const char value);
        void setAttribute(Attributes::Attribute* attr, double value);

        void conditionalCheck(int value);
        void conditionalCheck(bool value);
        void conditionalCheck(CustomString value);
        void conditionalCheck(char value);
        void conditionalCheck(double value);

        void referenceCondition(Condition* pcond);

        void notifyConditions();
    };

}
