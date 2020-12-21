#pragma once
#include "../List.hpp"
#include "./BetterInstigation.hpp"
#include "./NOPManager.hpp"
#include "Notifier.hpp"
#include "BetterCondition.hpp"

namespace JuNOCpp
{
    class BetterRule;
    class BetterAction: public Notifier, public Notifiable
    {
    public:
        BetterRule* rule;
        List<BetterCondition*> dependant_rules;

    public:
        BetterAction();
        ~BetterAction();
        
        void setBetterRule(BetterRule* b_rule);

        void update(const bool renotify = false);
        void update(const bool renotify, const bool status) {}
        void notify(const bool renotify = false);
        void disapproveDependantRules();
    };
}