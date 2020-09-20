#pragma once
#include <string.h>

namespace JuNOCpp
{
    class CustomString
    {
    private:
        int lenght;
        char* str;
    public:
        CustomString(const char* s = "");
        ~CustomString();

        const char* getString() const;

        void operator=(const char* s);
        void operator=(CustomString& s);

        bool operator==(CustomString& s);
        bool operator==(const char* s);

        bool operator!=(CustomString& s);
        bool operator!=(const char* s);

        operator const char* ();
    
    private:
        void setString(const char* s);
    };
}