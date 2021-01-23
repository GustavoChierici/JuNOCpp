#ifndef JUNOCPP_ACTION_HPP
#define JUNOCPP_ACTION_HPP

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
        Utils::forward_list<BetterCondition*> dependant_rules;

    public:
        BetterAction(Utils::CustomString name = "UnnamedAction");
        ~BetterAction();
        
        void setBetterRule(BetterRule* b_rule);

        void update(const bool renotify = false);
        void update(const bool renotify, const bool status) {}
        void notify(const bool renotify = false);
        void disapproveDependantRules();
    };
}
#endif // !JUNOCPP_ACTION_HPP