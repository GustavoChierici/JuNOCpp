#ifndef JUNOCPP_INSTIGATION_HPP
#define JUNOCPP_INSTIGATION_HPP

#include "Notifier.hpp"
#include "../Utils/NOPTraits/instigation_traits.hpp"
#include <functional>

namespace JuNOCpp
{
    namespace Core
    {
        class Instigation: public Notifiable
        {
        public:
            std::function<void()> method;
        public:
            Instigation(Utils::CustomString name = "UnnamedInstigation", std::function<void()> func = nullptr);
            ~Instigation();

            void setMt(std::function<void()>& func);

            void update(const bool renotify = false);
            void update(const bool renotify, const bool status);
        };
    } // namespace Core
}

#endif // !JUNOCPP_INSTIGATION_HPP