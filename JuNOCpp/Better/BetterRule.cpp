#include "BetterRule.hpp"
#include <iostream>

namespace JuNOCpp
{
    int BetterRule::counter = 0;
    int BetterRule::approved = 0;

    /**************************************** 
    * Construtores/Destrutores
    ****************************************/
    // BetterRule::BetterRule(CustomString mode /* = "CONJUNCTION" */, int rl_mode /* = BetterRule::COMPLETE */)
    // {
    //     this->cond = new Condition(mode);
    //     this->cond->referenceBetterRule(this);

    //     this->mode = rl_mode;

    //     switch(rl_mode)
    //     {
    //         case BetterRule::COMPLETE:
    //             this->action = new Action(this);
    //             this->attr = nullptr;
    //             this->exec_value = nullptr;
    //             this->exec = [](Attributes::Attribute* attr = nullptr, void* value = nullptr, Action* act = nullptr)
    //                         {
    //                             act->callInstigations();
    //                         };
    //             break;
    //         case BetterRule::INCOMPLETE:
    //             this->action = nullptr;
    //             this->exec = nullptr;
    //             this->attr = nullptr;
    //             this->exec_value = nullptr;
    //             break;
    //         case BetterRule::CUSTOM:
    //             this->action = nullptr;
    //             this->exec = nullptr;
    //             this->exec_value = nullptr;
    //             this->attr = nullptr;
    //             break;
    //     }
    // }

    BetterRule::BetterRule()
    {
        this->condition = nullptr;
        this->action = nullptr;
        this->id = BetterRule::counter;
        this->approved = false;
        this->name = "UnnamedRule";
        BetterRule::counter++;
    }

    BetterRule::~BetterRule()
    {
    }
    
    /***************************************
    *  Executar BetterRule aprovada
    ****************************************/
    void BetterRule::update(const bool renotify) //Método que a BetterRule execute após ter sido aprovada
    {
        // std::cout << "RULE " << this->id << " (" << this << ")" <<std::endl;

        this->notify();
        BetterRule::approved++;
    }
}