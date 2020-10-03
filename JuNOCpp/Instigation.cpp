#include "Instigation.hpp"

namespace JuNOCpp
{
    Instigation::Instigation(Method* mt)
    {
        this->mt = mt;
    }

    Instigation::Instigation(Attributes::Integer* attr, int value)
    {
        Method* aux = new Method(attr, value);
        this->mt = aux;
    }

    Instigation::Instigation(Attributes::Boolean* attr, bool value)
    {
        Method* aux = new Method(attr, value);
        this->mt = aux;
    }

    Instigation::Instigation(Attributes::Double* attr, double value)
    {
        Method* aux = new Method(attr, value);
        this->mt = aux;
    }

    Instigation::Instigation(Attributes::Char* attr, char value)
    {
        Method* aux = new Method(attr, value);
        this->mt = aux;
    }

    Instigation::Instigation(Attributes::String* attr, const char* value)
    {
        Method* aux = new Method(attr, value);
        this->mt = aux;
    }

    Instigation::~Instigation()
    {
    }

    void Instigation::call()
    {
        this->mt->execute();
    }
}