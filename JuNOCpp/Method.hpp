#pragma once
#include "FBE.hpp"
#include "Attributes/Attribute.hpp"
#include "Attributes/Integer.hpp"
#include "Attributes/Boolean.hpp"
#include "Attributes/Double.hpp"
#include "Attributes/Char.hpp"
#include "Attributes/String.hpp"

namespace JuNOCpp
{
    class Method
    {
    public:
        void (*mt)(Attributes::Attribute*, void*);
        FBE* fbe_reference;
        Attributes::Attribute* attr_reference;
        void* value;

    public:
        Method(void (*func)(Attributes::Attribute*, void*) = nullptr);
        Method(Attributes::Integer* attr, int value);
        Method(Attributes::Boolean* attr, bool value);
        Method(Attributes::Double* attr, double value);
        Method(Attributes::Char* attr, char value);
        Method(Attributes::String* attr, const char* value);
        ~Method();

        void execute();
    };
}