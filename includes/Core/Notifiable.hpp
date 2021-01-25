#ifndef JUNOCPP_NOTIFIABLE_HPP
#define JUNOCPP_NOTIFIABLE_HPP

#include "../.config.hpp"
#include <iostream>
#include "../Utils/CustomString.hpp"

#ifdef USE_CUSTOM_SMART_PTRS
    #include "../Utils/smart_ptr.hpp"
    template <typename T>
    using enable_shared_from_this = JuNOCpp::Utils::enable_shared_from_this<T>;
#else
    #include <memory>
    template <typename T>
    using enable_shared_from_this = std::enable_shared_from_this<T>;
#endif // USE_CUSTOM_SMART_PTRS

namespace JuNOCpp
{
    namespace Core
    {
        /**
         * @brief Classe abstrata Notifiable
         * 
         */
        class Notifiable: public enable_shared_from_this<Notifiable>
        {
            friend class Notifier;
        protected:
            Utils::CustomString name;
        public:
            Notifiable(Utils::CustomString name = "Unnamed"): name(name) { }
            virtual ~Notifiable() = default;

            virtual void update(const bool renotify = false) = 0;
            virtual void update(const bool renotify, const bool status) = 0;

            Utils::CustomString getName() const { return name; }
            void setName(const Utils::CustomString& name) { this->name = name; }
        };
    } // namespace Core
}

#endif // !JUNOCPP_NOTIFIABLE_HPP