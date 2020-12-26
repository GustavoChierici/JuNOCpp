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
    BetterRule::BetterRule() :
        condition{nullptr},
        action{nullptr},
        id{BetterRule::counter++},
        is_approved{false},
        name{"UnnamedRule"}
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

        this->notify();
        BetterRule::approved++;
    }
}