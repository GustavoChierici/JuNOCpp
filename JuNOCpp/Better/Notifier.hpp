#ifndef NOTIFIER_HPP
#define NOTIFIER_HPP

#include "../Definitions.hpp"
#include "../List.hpp"
#include "Notifiable.hpp"
#include <iostream>

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
    public:
        List<shared_ptr<Notifiable>> notifiables;

    public:
        Notifier() = default;
        ~Notifier() = default;
        
        void insert(shared_ptr<Notifiable>& notifiable);
        void remove(shared_ptr<Notifiable>& notifiable);
        void insert(shared_ptr<Notifiable>&& notifiable);
        void remove(shared_ptr<Notifiable>&& notifiable);

        virtual void notify(const bool renotify = false);
        virtual void notify(const bool renotify, const bool status);
    };
}

#endif // !NOTIFIER_HPP