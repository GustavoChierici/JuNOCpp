#pragma once
#include <functional>

namespace JuNOCpp
{
    class BetterMethod
    {
    public:
        std::function<void()> mt;
    
    public:
        BetterMethod();
        ~BetterMethod();

        void setMt(std::function<void()> func)
        {
            this->mt = func;
        }

        void execute()
        {
            this->mt();
        }
    };
}