#include "Method.hpp"

namespace JuNOCpp
{
    Method::Method(void (*func)(Attributes::Attribute*, void*))
    {
        this->mt = func;
        this->fbe_reference = nullptr;
    }

    Method::Method(Attributes::Integer* attr, int value)
    {
        this->mt = [](Attributes::Attribute* attr, void* value)
        {
            static_cast<Attributes::Integer*>(attr)->setStatus(*(int*)value);
        };

        this->attr_reference = attr;
        this->value = &value;
        this->fbe_reference = nullptr;
    }

    Method::Method(Attributes::Boolean* attr, bool value)
    {
        this->mt = [](Attributes::Attribute* attr, void* value)
        {
            static_cast<Attributes::Boolean*>(attr)->setStatus(*(bool*)value);
        };

        this->attr_reference = attr;
        this->value = &value;
        this->fbe_reference = nullptr;
    }

    Method::Method(Attributes::Double* attr, double value)
    {
        this->mt = [](Attributes::Attribute* attr, void* value)
        {
            static_cast<Attributes::Double*>(attr)->setStatus(*(double*)value);
        };

        this->attr_reference = attr;
        this->value = &value;
        this->fbe_reference = nullptr;
    }

    Method::Method(Attributes::Char* attr, char value)
    {
        this->mt = [](Attributes::Attribute* attr, void* value)
        {
            static_cast<Attributes::Char*>(attr)->setStatus(*(char*)value);
        };

        this->attr_reference = attr;
        this->value = &value;
        this->fbe_reference = nullptr;
    }

    Method::Method(Attributes::String* attr, const char* value)
    {
        this->mt = [](Attributes::Attribute* attr, void* value)
        {
            static_cast<Attributes::String*>(attr)->setStatus((const char*)value);
        };

        this->attr_reference = attr;
        this->value = &value;
        this->fbe_reference = nullptr;
    }

    Method::~Method()
    {
    }

    void Method::execute()
    {
        this->mt(this->attr_reference, this->value);
    }
}