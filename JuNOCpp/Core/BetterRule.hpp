#ifndef JUNOCPP_RULE_HPP
#define JUNOCPP_RULE_HPP

#include "./BetterCondition.hpp"
#include "./BetterAction.hpp"

namespace JuNOCpp
{
    class NOPManager;
    class BetterRule: public Notifiable, public Notifier
    {
    friend class NOPManager;
    private:
        BetterCondition* condition;
        BetterAction* action;
        
        int id;
        bool is_approved;

    public:
        static int counter;
        static int approved;

    public:
        BetterRule(Utils::CustomString name = "UnnamedRule");
        ~BetterRule();

        void update(const bool renotify = false);
        void update(const bool renotify, const bool status);
    };
}


#endif // !JUNOCPP_RULE_HPP
