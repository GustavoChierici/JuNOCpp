#pragma once

#include "./BetterCondition.hpp"
#include "./BetterAction.hpp"
#include "../List.hpp"

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
        CustomString name;

    public:
        static int counter;
        static int approved;

    public:
        BetterRule();
        ~BetterRule();

        void update(const bool renotify = false);
        void update(const bool renotify, const bool status) {}
    };
}

