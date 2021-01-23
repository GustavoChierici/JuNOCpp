/**
 * @file attribute_traits.hpp
 * @author Gustavo Brunholi Chierici (gustavobchierici@gmail.com)
 * @brief Algumas funções e metafunctions úteis para a manipulação de Attributes,
 * especialmente para a criação de tuplas de operação entre Attributes
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef JUNOCPP_ATTRIBUTE_TRAITS_HPP
#define JUNOCPP_ATTRIBUTE_TRAITS_HPP

#include <type_traits>
#include "../../.config.hpp"

#ifdef USE_CUSTOM_SMART_PTRS
    #include "../smart_ptr.hpp"
#else
    #include <memory>
#endif // USE_CUSTOM_SMART_PTRS

namespace JuNOCpp
{
    template<class TYPE>
    class Attribute;

    namespace Utils
    {
        namespace NOPTraits
        {
            
            template<typename AttrType, typename Type>
            struct is_attribute_of: std::false_type {};

            template<typename Type>
            struct is_attribute_of<Attribute<Type>, Type>: std::true_type {};

            template<typename Type>
            struct is_attribute_of<Attribute<Type>*, Type>: std::true_type {};

            template<typename AttrType, typename Type>
            inline constexpr bool is_attribute_of_v = is_attribute_of<AttrType, Type>::value;
            
            auto at_add_at = [](auto ... args) { return (... + args->getCurrentStatus()); };
            using at_add_at_t = decltype(at_add_at);

            /** Attribute opertions (used in tuples) **/
            /** + operator **/

            template<typename T>
            auto at_add_val = [](Attribute<T>* attr, auto ... values) { return attr->getCurrentStatus() + (... + values); };
            template<typename T>
            using at_add_val_t = decltype(at_add_val<T>);

            auto val_add_at = [](auto value, auto ... attrs) { return value + (... + attrs->getCurrentStatus()); };
            using val_add_at_t = decltype(val_add_at);

            auto val_add_val = [](auto... args) { return (... + args); };
            using val_add_val_t = decltype(val_add_val);

            /** - operator **/

            auto at_sub_at = [](auto ... args) { return (... - args->getCurrentStatus()); };
            using at_sub_at_t = decltype(at_sub_at);

            template<typename T>
            auto at_sub_val = [](Attribute<T>* attr, auto ... values) { return attr->getCurrentStatus() - (... - values); };
            template<typename T>
            using at_sub_val_t = decltype(at_sub_val<T>);

            auto val_sub_at = [](auto value, auto ... attrs) { return value - (... - attrs->getCurrentStatus()); };
            using val_sub_at_t = decltype(val_sub_at);

            auto val_sub_val = [](auto... args) { return (... - args); };
            using val_sub_val_t = decltype(val_sub_val);

            /** * operator **/

            auto at_mult_at = [](auto ... args) { return (... * args->getCurrentStatus()); };
            using at_mult_at_t = decltype(at_mult_at);

            template<typename T>
            auto at_mult_val = [](Attribute<T>* attr, auto ... values) { return attr->getCurrentStatus() * (... * values); };
            template<typename T>
            using at_mult_val_t = decltype(at_mult_val<T>);

            auto val_mult_at = [](auto value, auto ... attrs) { return value * (... * attrs->getCurrentStatus()); };
            using val_mult_at_t = decltype(val_mult_at);

            auto val_mult_val = [](auto... args) { return (... * args); };
            using val_mult_val_t = decltype(val_mult_val);

            /** / operator **/

            auto at_div_at = [](auto ... args) { return (... / args->getCurrentStatus()); };
            using at_div_at_t = decltype(at_div_at);

            template<typename T>
            auto at_div_val = [](Attribute<T>* attr, auto ... values) { return attr->getCurrentStatus() / (... / values); };
            template<typename T>
            using at_div_val_t = decltype(at_div_val<T>);

            auto val_div_at = [](auto value, auto ... attrs) { return value / (... / attrs->getCurrentStatus()); };
            using val_div_at_t = decltype(val_div_at);

            auto val_div_val = [](auto... args) { return (... / args); };
            using val_div_val_t = decltype(val_div_val);

            #ifdef USE_CUSTOM_SMART_PTRS
                template <typename T>
                using shared_ptr = JuNOCpp::Utils::shared_ptr<T>;
                template <typename T>
                using weak_ptr = JuNOCpp::Utils::weak_ptr<T>;
            #else
                template <typename T>
                using shared_ptr = std::shared_ptr<T>;
                template <typename T>
                using weak_ptr = std::weak_ptr<T>;
            #endif // USE_CUSTOM_SMART_PTRS

            template <typename T, typename PrT>
            void insertPremise(T t, shared_ptr<PrT> premise)
            {
            }

            template <typename T, typename PrT>
            void insertPremise(Attribute<T>* attr, shared_ptr<PrT> premise)
            {
                attr->insert(premise);
            }

            template <typename ...Ts, typename PrT>
            void insertPremise(std::tuple<Ts...> tuple, shared_ptr<PrT> premise)
            {
                std::apply([premise](auto... args){ (insertPremise(args, premise), ...); }, tuple);
            }

            template <typename T, typename PrT>
            void removePremise(T t, shared_ptr<PrT> premise)
            {
            }

            template <typename T, typename PrT>
            void removePremise(Attribute<T>* attr, shared_ptr<PrT> premise)
            {
                attr->remove(premise);
            }

            template <typename ...Ts, typename PrT>
            void removePremise(std::tuple<Ts...> tuple, shared_ptr<PrT> premise)
            {
                std::apply([premise](auto... args){ (removePremise(args, premise), ...); }, tuple);
            }

            template <typename T, typename PrT>
            void addImpertinent(T t, shared_ptr<PrT> premise)
            {
            }

            template <typename T, typename PrT>
            void addImpertinent(Attribute<T>* attr, shared_ptr<PrT> premise)
            {
                attr->addImpertinent(premise);
            }

            template <typename ...Ts, typename PrT>
            void addImpertinent(std::tuple<Ts...> tuple, shared_ptr<PrT> premise)
            {
                std::apply([premise](auto... args){ (addImpertinent(args, premise), ...); }, tuple);
            }

        } // namespace NOPTrais
        
    } // namespace Utils
    
} // namespace JuNOCpp

#endif // !JUNOCPP_ATTRIBUTE_TRAITS_HPP