#include "Rule.hpp"
#include "NOPManager.hpp"
#include <iostream>

namespace JuNOCpp
{
    namespace Core
    {
        int Rule::counter = 0;
        int Rule::approved = 0;

        /**
         * @brief Construtor
         * 
         * @param name 
         */
        Rule::Rule(Utils::CustomString name) :
            Notifiable(name),
            condition{nullptr},
            action{nullptr},
            id{Rule::counter++},
            is_approved{false}
        {
        }

        /**
         * @brief Destrutor
         * 
         */
        Rule::~Rule()
        {
            condition = nullptr;
            action = nullptr;
        }
        
        /**
         * @brief Executa a Rule aprovada
         * 
         * @param renotify 
         */
        void Rule::update(const bool renotify)
        {
            // std::cout << "RULE " << this->id << " (" << this << ")" <<std::endl;

            #ifdef SHOW_NOP_LOGGER
                Utils::NOPLogger::Get().writeRuleApproved(name, this);

                Utils::NOPLogger::Get().incrementIdentation();
            #endif // SHOW_NOP_LOGGER

            this->notify();
            Rule::approved++;

            #ifdef SHOW_NOP_LOGGER
                Utils::NOPLogger::Get().decrementIdentation();
            #endif // SHOW_NOP_LOGGER
        }

        /**
         * @brief Executa a Rule aprovada
         * 
         * @param renotify 
         * @param status 
         */
        void Rule::update(const bool renotify, const bool status)
        {
            #ifdef SHOW_NOP_LOGGER
                Utils::NOPLogger::Get().writeRuleApproved(name, this);

                Utils::NOPLogger::Get().incrementIdentation();
            #endif // SHOW_NOP_LOGGER

            this->notify();
            Rule::approved++;

            #ifdef SHOW_NOP_LOGGER
                Utils::NOPLogger::Get().decrementIdentation();
            #endif // SHOW_NOP_LOGGER
        }   
    } // namespace Core
}