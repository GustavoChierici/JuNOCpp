#include "CustomString.hpp"

namespace JuNOCpp
{
    CustomString::CustomString(const char* s) :
    length(strlen(s))
    {
        setString(s);
    }

    CustomString::~CustomString()
    {
    }

    void CustomString::setString(const char* s)
    {
        this->str = new char[this->length + 1];
        strcpy(this->str, s);
    }

    const char* CustomString::getString() const
    {
        return this->str;
    }

    void CustomString::operator=(const char* s)
    {
        this->length = strlen(s);
        setString(s);
    }

    void CustomString::operator=(CustomString& s)
    {
        this->length = strlen(s.getString());
        setString(s.getString());
    }

    bool CustomString::operator==(CustomString& s)
    {
        return (!strcmp(this->getString(), s.getString()) ? true : false);
    }

    bool CustomString::operator==(const char* s)
    {
        bool isEqual = !strcmp(this->getString(), s);
        return isEqual;
    }

    bool CustomString::operator!=(CustomString& s)
    {
        return (strcmp(this->getString(), s.getString()) ? true : false);
    }

    bool CustomString::operator!=(const char* s)
    {
        return (!strcmp(this->getString(), s) ? true : false);
    }

    CustomString::operator const char *()
    {
        return this->getString();
    }
}
