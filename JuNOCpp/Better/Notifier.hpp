#ifndef NOTIFIER_HPP
#define NOTIFIER_HPP

#include "../List.hpp"
#include "Notifiable.hpp"
#include <iostream>
#include <memory>
#include <vector>

namespace JuNOCpp
{
    class Notifier
    {
    public:
        List<std::shared_ptr<Notifiable>> notifiables;
        std::vector<std::shared_ptr<Notifiable>> notfs;
    
    public:
        Notifier() = default;
        ~Notifier() = default;
        
        void insert(std::shared_ptr<Notifiable>&& notifiable);
        void remove(std::shared_ptr<Notifiable>&& notifiable);

        virtual void notify(const bool renotify = false);
        virtual void notify(const bool renotify, const bool status);
    };
}

#endif // !NOTIFIER_HPP