/**
 * @file instigation_traits.hpp
 * @author Gustavo Brunholi Chierici (gustavobchierici@gmail.com)
 * @brief Algumas funções e metafunctions úteis para a manipulação de Instigations
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef INSTIGATION_TRAITS_HPP
#define INSTIGATION_TRAITS_HPP

#include <type_traits>

namespace JuNOCpp
{
    class BetterInstigation;

    namespace Utils
    {
        namespace NOPTraits
        {
            template<typename InstType>
            struct is_instigation: std::false_type{};

            template<>
            struct is_instigation<BetterInstigation>: std::true_type{};

            template<typename InstType>
            inline constexpr bool is_instigation_v = is_instigation<InstType>::value;
        } // namespace NOPTraits
        
    } // namespace Utils
    
} // namespace JuNOCpp


#endif // !INSTIGATION_TRAITS_HPP