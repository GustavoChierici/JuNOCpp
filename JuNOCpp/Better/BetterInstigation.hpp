#pragma once 
// #include "./BetterMethod.hpp"
#include "Notifier.hpp"
#include <functional>
#include <tuple>

namespace JuNOCpp
{
    class BetterInstigation: public Notifiable
    {
    public:
        //BetterMethod* method;
        std::function<void()> method;
    public:
        BetterInstigation();
        ~BetterInstigation();

        void setMt(std::function<void()>& func);

        void update(const bool renotify = false);
    };
}