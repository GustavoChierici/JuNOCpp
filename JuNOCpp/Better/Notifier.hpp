#ifndef NOTIFIER_HPP
#define NOTIFIER_HPP

#include "../.config.hpp"
#include "../Utils/forward_list.hpp"
#include "Notifiable.hpp"
#include "../Utils/NOPLogger.hpp"
#include <iostream>
#include "../Utils/NOPTraits/common_traits.hpp"

#ifdef USE_CUSTOM_SMART_PTRS
    #include "../Utils/SmartPtr.hpp"
    template <typename T>
    using shared_ptr = JuNOCpp::Utils::shared_ptr<T>;
    template <typename T>
    using weak_ptr = JuNOCpp::Utils::weak_ptr<T>;
#else
    #include <memory>
    template <typename T>
    using shared_ptr = std::shared_ptr<T>;
    template <typename T>
    using weak_ptr = std::weak_ptr<T>;
#endif // USE_CUSTOM_SMART_PTRS


namespace JuNOCpp
{
    class Notifier
    {
    protected:
        Utils::forward_list<shared_ptr<Notifiable>> notifiables;

    public:
        Notifier() = default;
        Notifier(Utils::forward_list<shared_ptr<Notifiable>> notfs): notifiables{notfs} {}
        virtual ~Notifier() = default;
        
        void insert(shared_ptr<Notifiable>& notifiable);
        void remove(shared_ptr<Notifiable>& notifiable);
        void insert(shared_ptr<Notifiable>&& notifiable);
        void remove(shared_ptr<Notifiable>&& notifiable);

        virtual void notify(const bool renotify = false);
        virtual void notify(const bool renotify, const bool status);
    };
}

#endif // !NOTIFIER_HPP