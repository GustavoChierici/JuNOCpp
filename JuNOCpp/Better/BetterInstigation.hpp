#pragma once
#include "Notifier.hpp"
#include <functional>

namespace JuNOCpp
{
    class BetterInstigation: public Notifiable
    {
    public:
        std::function<void()> method;
    public:
        BetterInstigation(CustomString name = "UnnamedInstigation");
        ~BetterInstigation();

        void setMt(std::function<void()>& func);

        void update(const bool renotify = false);
        void update(const bool renotify, const bool status);
    };
}