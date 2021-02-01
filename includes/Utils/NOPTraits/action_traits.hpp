/**
 * @file action_traits.hpp
 * @author Gustavo Brunholi Chierici (gustavobchierici@gmail.com)
 * @brief Algumas funções e metafunctions úteis para a manipulação de Actions
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef JUNOCPP_ACTION_TRAITS_HPP
#define JUNOCPP_ACTION_TRAITS_HPP

#include <type_traits>

namespace JuNOCpp
{
    namespace Core
    {
        class Action;
    } // namespace Core
    

    namespace Utils
    {
        namespace NOPTraits
        {
            template<typename ActType>
            struct is_action: std::is_same<std::remove_pointer_t<std::remove_reference_t<std::remove_cv_t<ActType>>>, Core::Action>
            {};

            template<typename ActType>
            inline constexpr bool is_action_v = is_action<ActType>::value;
        } // namespace NOPTraits
        
    } // namespace Utils
    
} // namespace JuNOCpp


#endif // !JUNOCPP_ACTION_TRAITS_HPP