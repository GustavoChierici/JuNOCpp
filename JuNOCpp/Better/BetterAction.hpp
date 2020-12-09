#pragma once
#include "../List.hpp"
#include "./BetterInstigation.hpp"
#include "./NOPManager.hpp"
#include "Notifier.hpp"

namespace JuNOCpp
{
    class BetterRule;
    class BetterAction: public Notifier, public Notifiable
    {
    public:
        BetterRule* rule;

    public:
        BetterAction();
        ~BetterAction();
        
        void setBetterRule(BetterRule* b_rule);

        void update(const bool renotify = false);
    };
}