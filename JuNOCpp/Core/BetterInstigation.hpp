#ifndef JUNOCPP_INSTIGATION_HPP
#define JUNOCPP_INSTIGATION_HPP

#include "Notifier.hpp"
#include "../Utils/NOPTraits/instigation_traits.hpp"
#include <functional>

namespace JuNOCpp
{
    class BetterInstigation: public Notifiable
    {
    public:
        std::function<void()> method;
    public:
        BetterInstigation(Utils::CustomString name = "UnnamedInstigation", std::function<void()> func = nullptr);
        ~BetterInstigation();

        void setMt(std::function<void()>& func);

        void update(const bool renotify = false);
        void update(const bool renotify, const bool status);
    };
}

#endif // !JUNOCPP_INSTIGATION_HPP