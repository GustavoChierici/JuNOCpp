/**
 * @file common_traits.hpp
 * @author Gustavo Brunholi Chierici (gustavobchierici@gmail.com)
 * @brief Algumas funções e metafunctions úteis no geral
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef COMMON_TRAITS_HPP
#define COMMON_TRAITS_HPP

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


        } // namespace NOPTraits
        
    } // namespace Utils
    
} // namespace JuNOCpp


#endif // !COMMON_TRAITS_HPP