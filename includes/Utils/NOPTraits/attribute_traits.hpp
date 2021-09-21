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
#include <tuple>

namespace JuNOCpp
{
    namespace Core
    {
        template<class TYPE>
        class Attribute;
    }

    namespace Utils
    {
        namespace NOPTraits
        {
            template<typename AttrType>
            struct is_attribute: std::false_type
            {};

            template<template<typename> typename AttrType, typename Type>
            struct is_attribute<AttrType<Type>>: std::is_same<std::remove_pointer_t<std::remove_reference_t<std::remove_cv_t<AttrType<Type>>>>, Core::Attribute<Type>>
            {
                 typedef Type type;
            };

            template<template<typename> typename AttrType, typename Type>
            struct is_attribute<AttrType<Type>*>: std::is_same<std::remove_pointer_t<std::remove_reference_t<std::remove_cv_t<AttrType<Type>>>>, Core::Attribute<Type>>
            {
                 typedef Type type;
            };
            
            template<typename AttrType>
            inline constexpr bool is_attribute_v = is_attribute<AttrType>::value;

            template<typename AttrType>
            struct attribute_type
            {};


            template<typename AttrType>
            using is_attribute_t = typename is_attribute<AttrType>::type;  

            template<typename AttrType, typename Type>
            struct is_attribute_of: std::is_same<std::remove_pointer_t<std::remove_reference_t<std::remove_cv_t<AttrType>>>, Core::Attribute<Type>>
            {};

            template<typename AttrType, typename Type>
            inline constexpr bool is_attribute_of_v = is_attribute_of<AttrType, Type>::value;
            
            /** Attribute opertions (used in tuples) **/
            /** + operator **/

            static auto at_add_at = [](auto ... args) { return (... + args->getValue()); };
            using at_add_at_t = decltype(at_add_at);

            static auto at_add_val = [](auto attr, auto ... values) { return attr->getValue() + (... + values); };
            using at_add_val_t = decltype(at_add_val);

            static auto val_add_at = [](auto value, auto ... attrs) { return value + (... + attrs->getValue()); };
            using val_add_at_t = decltype(val_add_at);

            static auto val_add_val = [](auto... args) { return (... + args); };
            using val_add_val_t = decltype(val_add_val);

            /** - operator **/

            static auto at_sub_at = [](auto ... args) { return (... - args->getValue()); };
            using at_sub_at_t = decltype(at_sub_at);

            static auto at_sub_val = [](auto attr, auto ... values) { return attr->getValue() - (... - values); };
            using at_sub_val_t = decltype(at_sub_val);

            static auto val_sub_at = [](auto value, auto ... attrs) { return value - (... - attrs->getValue()); };
            using val_sub_at_t = decltype(val_sub_at);

            static auto val_sub_val = [](auto... args) { return (... - args); };
            using val_sub_val_t = decltype(val_sub_val);

            /** * operator **/

            static auto at_mult_at = [](auto ... args) { return (... * args->getValue()); };
            using at_mult_at_t = decltype(at_mult_at);

            static auto at_mult_val = [](auto attr, auto ... values) { return attr->getValue() * (... * values); };
            using at_mult_val_t = decltype(at_mult_val);

            static auto val_mult_at = [](auto value, auto ... attrs) { return value * (... * attrs->getValue()); };
            using val_mult_at_t = decltype(val_mult_at);

            static auto val_mult_val = [](auto... args) { return (... * args); };
            using val_mult_val_t = decltype(val_mult_val);

            /** / operator **/

            static auto at_div_at = [](auto ... args) { return (... / args->getValue()); };
            using at_div_at_t = decltype(at_div_at);

            static auto at_div_val = [](auto attr, auto ... values) { return attr->getValue() / (... / values); };
            using at_div_val_t = decltype(at_div_val);

            static auto val_div_at = [](auto value, auto ... attrs) { return value / (... / attrs->getValue()); };
            using val_div_at_t = decltype(val_div_at);

            static auto val_div_val = [](auto... args) { return (... / args); };
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
            void insertPremise(Core::Attribute<T>* attr, shared_ptr<PrT> premise)
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
            void removePremise(Core::Attribute<T>* attr, shared_ptr<PrT> premise)
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
            void addImpertinent(Core::Attribute<T>* attr, shared_ptr<PrT> premise)
            {
                attr->addImpertinent(premise);
            }

            template <typename ...Ts, typename PrT>
            void addImpertinent(std::tuple<Ts...> tuple, shared_ptr<PrT> premise)
            {
                std::apply([premise](auto... args){ (addImpertinent(args, premise), ...); }, tuple);
            }


            // CONCEPTS

            template<typename T>
            concept NOPAttribute = is_attribute_v<T>;

            template<typename T>
            concept Incrementable = requires(T a) {a++; ++a;};
            template<typename T>
            concept Decrementable = requires(T a) {a--; --a;};
            template<typename LT, typename RT>
            concept Addables = requires(LT lhs, RT rhs) {lhs + rhs;};
            template<typename LT, typename RT>
            concept Subtractables = requires(LT lhs, RT rhs) {lhs - rhs;};
            template<typename LT, typename RT>
            concept Multipliables = requires(LT lhs, RT rhs) {lhs * rhs;};
            template<typename LT, typename RT>
            concept Divisibles = requires(LT lhs, RT rhs) {lhs / rhs;};



        } // namespace NOPTraits
        
    } // namespace Utils
    
} // namespace JuNOCpp

#endif // !JUNOCPP_ATTRIBUTE_TRAITS_HPP