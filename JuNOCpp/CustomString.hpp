#pragma once
#include <string.h>
#include <string>

namespace JuNOCpp
{
    class CustomString
    {
    private:
        size_t length;
        char* str;
    public:
        CustomString(const char* s = "");
        CustomString(const CustomString& s);
        CustomString(const std::string& s);
        ~CustomString();

        const char* getString() const;
        char* get_str() { return str; }

        void operator=(const char* s);
        void operator=(const CustomString& s);
        void operator=(const std::string& s);


        bool operator==(const char* s) const;
        bool operator==(const CustomString& s) const;
        bool operator==(const std::string& s) const;

        bool operator!=(const char* s) const;
        bool operator!=(const CustomString& s) const;
        bool operator!=(const std::string& s) const;

        operator const char* ();
    
    private:
        void setString(const char* s);
    };
}