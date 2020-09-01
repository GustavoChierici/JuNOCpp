#pragma once
#include <vector>

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
        bool status;
        bool previous_status;
        std::vector<Condition*> conditions;

    public:
        Premise();
        ~Premise();
        Premise(Attributes::Attribute* attr, const int value);

        void setAttribute(Attributes::Attribute* attr, const int value);
        void setAttribute(Attributes::Attribute* attr, const bool value);

        void conditionalCheck();

        void referenceCondition(Condition* pcond);

        void notifyConditions();
    };

}
