#pragma once

#include "./BetterCondition.hpp"
#include "./BetterAction.hpp"
#include "../List.hpp"

namespace JuNOCpp
{
    class Action;
    class BetterRule: public Notifiable, public Notifier
    {
    public:
        BetterCondition* cond;
        BetterAction* action;
        
        int id;

    public:
        static int counter;
        static int approved;

    public:
        BetterRule();
        ~BetterRule();

        void execute();
        void update(const bool renotify = false);
    };
}

