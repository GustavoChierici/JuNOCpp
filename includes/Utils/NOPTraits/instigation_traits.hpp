/**
 * @file instigation_traits.hpp
 * @author Gustavo Brunholi Chierici (gustavobchierici@gmail.com)
 * @brief Algumas funções e metafunctions úteis para a manipulação de Instigations
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef JUNOCPP_INSTIGATION_TRAITS_HPP
#define JUNOCPP_INSTIGATION_TRAITS_HPP

#include <type_traits>

namespace JuNOCpp
{
    namespace Core
    {
        class Instigation;
    } // namespace Core
    

    namespace Utils
    {
        namespace NOPTraits
        {
            template<typename InstType>
            struct is_instigation: std::is_same<std::remove_pointer_t<std::remove_reference_t<std::remove_cv_t<InstType>>>, Core::Instigation>
            {};

            template<typename InstType>
            inline constexpr bool is_instigation_v = is_instigation<InstType>::value;
        } // namespace NOPTraits
        
    } // namespace Utils
    
} // namespace JuNOCpp


#endif // !JUNOCPP_INSTIGATION_TRAITS_HPP