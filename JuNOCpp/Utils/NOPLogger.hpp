#ifndef JUNOCPP_NOP_LOGGER_HPP
#define JUNOCPP_NOP_LOGGER_HPP

#include <string>
#include <iostream>
#include "../Core/Notifiable.hpp"

namespace JuNOCpp
{
    namespace Utils
    {
        class NOPLogger // Singleton
        {
        public:
            NOPLogger(const NOPLogger&) = delete;

            static NOPLogger& Get() 
            { 
                static NOPLogger instance;
                return instance; 
            }

            static void writeNotification(CustomString name, Notifiable* address)
            {
                std::cout << identation << "(=>) " << name << " (" << address << ")" << std::endl;
            }

            static void writeNotification(CustomString name, Notifiable* address, bool status)
            {
                std::cout << identation << "(=>) " << name << " (" << address << ")"
                        << " with status: " << (status ? "true" : "false") << std::endl;
            }

            template <typename T>
            static void writeAssignment(CustomString name, Notifiable* address, T value, bool renotify)
            {
                std::cout << identation << "(=) "<< name << " (" << address << ") <- " << value << " (renotify: " 
                        << (renotify ? "true)" : "false)") << std::endl; 
            }

            static void writeNotifying(CustomString name, Notifiable* address, bool renotify)
            {
                std::cout << identation << (renotify ? "(R) " : "(N) ") << name << " (" << address << ") notifying:" << std::endl;
            }

            static void writeNotifying(CustomString name, Notifiable* address, bool value, bool renotify)
            {
                std::cout << identation << (renotify ? "(R) " : "(N) ") << name << " (" << address << ") is now " <<
                    (value ? "true. Notifying:" : "false. Notifying:") << std::endl;
            }

            static void writeIncrementCondition(CustomString name, Notifiable* address, const int approved, const int quantity)
            {
                std::cout << identation << "(+) " << name << " (" << address << ") " << approved << "/" << quantity << std::endl; 
            }

            static void writeDecrementCondition(CustomString name, Notifiable* address, const int approved, const int quantity)
            {
                std::cout << identation << "(-) " << name << " (" << address << ") " << approved << "/" << quantity << std::endl; 
            }

            static void writeActivatingImpertinents(CustomString name, Notifiable* address)
            {
                std::cout << identation << "(on) " << name << " (" << address << ") activating impertinents" << std::endl;
            }

            static void writeDeactivatingImpertinents(CustomString name, Notifiable* address)
            {
                std::cout << identation << "(off) " << name << " (" << address << ") deactivating impertinents" << std::endl;
            }

            static void writeImpertinentActivated(CustomString name, Notifiable* address)
            {
                 std::cout << identation << "(*on) " << name << " (" << address << ") activated" << std::endl;
            }

            static void writeImpertinentDeactivated(CustomString name, Notifiable* address)
            {
                 std::cout << identation << "(*off) " << name << " (" << address << ") deactivated" << std::endl;
            }  

            static void writeRuleApproved(CustomString name, Notifiable* address)
            {
                std::cout << identation << "(*R) " << name << " (" << address << ") approved! Executing:" << std::endl;
            }

            static void writeActionExecuting(CustomString name, Notifiable* address)
            {
                std::cout << identation << "(*A) " << name << " (" << address << ") called. Notifying/calling:" << std::endl;
            }

            static void writeInstigationExecuting(CustomString name, Notifiable* address)
            {
                std::cout << identation << "(*I) " << name << " (" << address << ") called. Executing:" << std::endl;
            }

            static void incrementIdentation(CustomString ident = "   ") { identation += ident; }
            static void decrementIdentation() 
            {
                identation.pop_back();
                identation.pop_back();
                identation.pop_back();
            }

        private:
            NOPLogger() {}
            ~NOPLogger() {}

        public:
            static std::string identation;
        };
    } // namespace Utils
} // namespace JuNOCpp


#endif // !JUNOCPP_NOP_LOGGER_HPP