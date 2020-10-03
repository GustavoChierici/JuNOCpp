#pragma once

#include "Rule.hpp"
#include "List.hpp"
#include "Instigation.hpp"
#include "Method.hpp"
#include "Attributes/Attribute.hpp"
#include "Attributes/Integer.hpp"
#include "Attributes/Boolean.hpp"
#include "Attributes/Double.hpp"
#include "Attributes/Char.hpp"
#include "Attributes/String.hpp"

namespace JuNOCpp
{
    class Action
    {
    private:
        Rule* rule;
        List<Instigation> instigations;
    public:
        Action(Rule* rl = nullptr);
        ~Action();

        void addInstigation(Instigation* inst);
        void addInstigation(Method* mt);
        void addInstigation(Attributes::Integer* attr, int value);
        void addInstigation(Attributes::Boolean* attr, bool value);
        void addInstigation(Attributes::Double* attr, double value);
        void addInstigation(Attributes::Char* attr, char value);
        void addInstigation(Attributes::String* attr, const char* value);
        

        void setRule(Rule* rl);

        void callInstigations();
    };
}