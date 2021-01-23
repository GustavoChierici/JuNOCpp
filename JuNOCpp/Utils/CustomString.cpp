#include "./CustomString.hpp"

namespace JuNOCpp
{
    namespace Utils
    {
        CustomString::CustomString(const char *s) : length{strlen(s)}, str{nullptr}
        {
            setString(s);
        }

        CustomString::CustomString(const CustomString &s) : length{s.length}, str{nullptr}
        {
            setString(s.getString());
        }

        CustomString::CustomString(const std::string &s) : length{s.length()}, str{nullptr}
        {
            setString(s.c_str());
        }

        CustomString::~CustomString()
        {
            if (str) delete[] str;
        }

        void CustomString::setString(const char *s)
        {
            if (str)
                delete[] str;

            // this->str = (char*)malloc((strlen(s)) * sizeof(char));
            this->str = new char[(strlen(s)) + 1];
            strcpy(this->str, s);
        }

        const char *CustomString::getString() const
        {
            return this->str;
        }

        void CustomString::operator=(const char *s)
        {
            this->length = strlen(s);
            setString(s);
        }

        void CustomString::operator=(const CustomString &s)
        {
            this->length = strlen(s.getString());
            setString(s.getString());
        }

        void CustomString::operator=(const std::string &s)
        {
            this->length = s.length();
            setString(s.c_str());
        }

        bool CustomString::operator==(const char *s) const
        {
            return !strcmp(this->getString(), s);
        }

        bool CustomString::operator==(const CustomString &s) const
        {
            return (!strcmp(this->getString(), s.getString()) ? true : false);
        }

        bool CustomString::operator==(const std::string &s) const
        {
            return (!strcmp(this->getString(), s.c_str()) ? true : false);
        }

        bool CustomString::operator!=(const char *s) const
        {
            return (strcmp(this->getString(), s) ? true : false);
        }

        bool CustomString::operator!=(const CustomString &s) const
        {
            return (strcmp(this->getString(), s.getString()) ? true : false);
        }

        bool CustomString::operator!=(const std::string &s) const
        {
            return (strcmp(this->getString(), s.c_str()) ? true : false);
        }

        CustomString::operator const char *()
        {
            return this->getString();
        }
    } // namespace Utils
} // namespace JuNOCpp
