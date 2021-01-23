/**
 * @file rule_traits.hpp
 * @author Gustavo Brunholi Chierici (gustavobchierici@gmail.com)
 * @brief Algumas funções e metafunctions úteis para a manipulação de Rules
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef JUNOCPP_RULE_TRAITS_HPP
#define JUNOCPP_RULE_TRAITS_HPP

#include <type_traits>

namespace JuNOCpp
{
    class BetterRule;

    namespace Utils
    {
        namespace NOPTraits
        {
            template<typename RuleType>
            struct is_rule: std::false_type{};

            template<>
            struct is_rule<BetterRule>: std::true_type{};

            template<typename RuleType>
            inline constexpr bool is_rule_v = is_rule<RuleType>::value;
        } // namespace NOPTraits
        
    } // namespace Utils
    
} // namespace JuNOCpp


#endif // !JUNOCPP_RULE_TRAITS_HPP