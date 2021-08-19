/**
 * @file common_traits.hpp
 * @author Gustavo Brunholi Chierici (gustavobchierici@gmail.com)
 * @brief Algumas funções e metafunctions úteis no geral
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef JUNOCPP_COMMON_TRAITS_HPP
#define JUNOCPP_COMMON_TRAITS_HPP

#include <type_traits>
#include <tuple>
#include <functional>

namespace JuNOCpp
{
    namespace Utils
    {
        namespace NOPTraits
        {
            template <typename> 
            struct is_tuple: std::false_type {};

            template <typename ...T> 
            struct is_tuple<std::tuple<T...>>: std::true_type {};

            template<typename ...T>
            inline constexpr bool is_tuple_v = is_tuple<T...>::value;

            template <typename T>
            auto eval(T t)
            {
                return t;
            }

            template <typename ...Ts>
            auto eval(std::tuple<Ts...> tuple)
            {
                return std::apply([](auto... args){ return std::invoke(eval(args)...); }, tuple);
            }

            template<typename T>
            struct is_string: std::is_same<std::remove_cv_t<std::remove_reference_t<T>>, std::string>
            {};

            template<>
            struct is_string<char*>: std::true_type
            {};

            template<>
            struct is_string<const char*>: std::true_type
            {};

            template<typename T>
            inline constexpr bool is_string_v= is_string<T>::value;

            enum NotificationFlag
            {
                NoNotify = 0,
                Notify,
                ReNotify,
            };

            template<typename T>
            std::tuple<T, NotificationFlag> operator,(T value, NotificationFlag flag)
            {
                return {value, flag};
            }

        } // namespace NOPTraits
        
    } // namespace Utils
    
} // namespace JuNOCpp


#endif // !JUNOCPP_COMMON_TRAITS_HPP