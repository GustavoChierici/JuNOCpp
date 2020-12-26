#pragma once

#include <iostream>
#include <memory>

namespace JuNOCpp
{
    /**
     * Classe abstrata Notifiable
     * 
     */
    class Notifiable: public std::enable_shared_from_this<Notifiable>
    {
    public:
        Notifiable() = default;
        ~Notifiable() = default;

        virtual void update(const bool renotify = false) = 0;
        virtual void update(const bool renotify, const bool status) = 0;
    };
}