#include "./BetterRule.hpp"
#include "./NOPManager.hpp"
#include <iostream>

namespace JuNOCpp
{
    int BetterRule::counter = 0;
    int BetterRule::approved = 0;

    /**************************************** 
    * Construtores/Destrutores
    ****************************************/
    BetterRule::BetterRule(Utils::CustomString name) :
        Notifiable(name),
        condition{nullptr},
        action{nullptr},
        id{BetterRule::counter++},
        is_approved{false}
    {
    }

    BetterRule::~BetterRule()
    {
    }
    
    /***************************************
    *  Executar BetterRule aprovada
    ****************************************/
    void BetterRule::update(const bool renotify)
    {
        // std::cout << "RULE " << this->id << " (" << this << ")" <<std::endl;

        #ifdef SHOW_NOP_LOGGER
            Utils::NOPLogger::Get().writeRuleApproved(name, this);

            Utils::NOPLogger::Get().incrementIdentation();
        #endif // SHOW_NOP_LOGGER

        this->notify();
        BetterRule::approved++;

        #ifdef SHOW_NOP_LOGGER
            Utils::NOPLogger::Get().decrementIdentation();
        #endif // SHOW_NOP_LOGGER
    }

    void BetterRule::update(const bool renotify, const bool status)
    {
        #ifdef SHOW_NOP_LOGGER
            Utils::NOPLogger::Get().writeRuleApproved(name, this);

            Utils::NOPLogger::Get().incrementIdentation();
        #endif // SHOW_NOP_LOGGER

        this->notify();
        BetterRule::approved++;

        #ifdef SHOW_NOP_LOGGER
            Utils::NOPLogger::Get().decrementIdentation();
        #endif // SHOW_NOP_LOGGER
    }
}