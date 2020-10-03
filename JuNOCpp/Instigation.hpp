#pragma once
#include "Method.hpp"
#include "Attributes/Integer.hpp"
#include "Attributes/Boolean.hpp"
#include "Attributes/Double.hpp"
#include "Attributes/Char.hpp"
#include "Attributes/String.hpp"

namespace JuNOCpp
{
    class Instigation
    {
    private:
        Method* mt;

    public:
        Instigation(Method* mt = nullptr);
        Instigation(Attributes::Integer* attr, int value);
        Instigation(Attributes::Boolean* attr, bool value);
        Instigation(Attributes::Double* attr, double value);
        Instigation(Attributes::Char* attr, char value);
        Instigation(Attributes::String* attr, const char* value);
        ~Instigation();

        void call();
    };
}