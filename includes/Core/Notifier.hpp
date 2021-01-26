#ifndef JUNOCPP_NOTIFIER_HPP
#define JUNOCPP_NOTIFIER_HPP

#include ".config.hpp"
#include "forward_list.hpp"
#include "Notifiable.hpp"
#include "NOPLogger.hpp"
#include <iostream>
#include "common_traits.hpp"

#ifdef USE_CUSTOM_SMART_PTRS
    #include "smart_ptr.hpp"
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
    namespace Core
    {
        class Notifier
        {
        protected:
            NOPCollection<shared_ptr<Notifiable>> notifiables;

        public:
            Notifier() = default;
            Notifier(NOPCollection<shared_ptr<Notifiable>> notfs): notifiables{notfs} {}
            virtual ~Notifier() = default;
            
            void insert(shared_ptr<Notifiable>& notifiable);
            void remove(shared_ptr<Notifiable>& notifiable);
            void insert(shared_ptr<Notifiable>&& notifiable);
            void remove(shared_ptr<Notifiable>&& notifiable);

            virtual void notify(const bool renotify = false);
            virtual void notify(const bool renotify, const bool status);
        };
    } // namespace Core
}

#endif // !JUNOCPP_NOTIFIER_HPP