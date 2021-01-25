/**
 * @file condition_traits.hpp
 * @author Gustavo Brunholi Chierici (gustavobchierici@gmail.com)
 * @brief Algumas funções e metafunctions úteis para a manipulação de Conditions
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef JUNOCPP_CONDITION_TRAITS_HPP
#define JUNOCPP_CONDITION_TRAITS_HPP

#include <type_traits>

namespace JuNOCpp
{
    class BetterCondition;

    namespace Utils
    {
        namespace NOPTraits
        {
            template<typename CondType>
            struct is_condition: std::false_type{};

            template<>
            struct is_condition<BetterCondition>: std::true_type{};

            template<typename CondType>
            inline constexpr bool is_condition_v = is_condition<CondType>::value;
        } // namespace NOPTraits
        
    } // namespace Utils
    
} // namespace JuNOCpp


#endif // !JUNOCPP_CONDITION_TRAITS_HPP