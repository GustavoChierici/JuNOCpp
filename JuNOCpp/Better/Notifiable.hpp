#pragma once

#include "../Definitions.hpp"
#include <iostream>

#ifdef USE_CUSTOM_SMART_PTRS
    #include "../Utils/SmartPtr.hpp"
    template <typename T>
    using enable_shared_from_this = JuNOCpp::Utils::enable_shared_from_this<T>;
#else
    #include <memory>
    template <typename T>
    using enable_shared_from_this = std::enable_shared_from_this<T>;
#endif // USE_CUSTOM_SMART_PTRS

namespace JuNOCpp
{
    /**
     * Classe abstrata Notifiable
     * 
     */
    class Notifiable: public enable_shared_from_this<Notifiable>
    {
    public:
        Notifiable() = default;
        ~Notifiable() = default;

        virtual void update(const bool renotify = false) = 0;
        virtual void update(const bool renotify, const bool status) = 0;
    };
}