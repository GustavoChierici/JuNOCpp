/**
 * @file premise_traits.hpp
 * @author Gustavo Brunholi Chierici (gustavobchierici@gmail.com)
 * @brief Algumas funções e metafunctions úteis para a manipulação de Premises
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef JUNOCPP_PREMISE_TRAITS_HPP
#define JUNOCPP_PREMISE_TRAITS_HPP

#include <type_traits>

namespace JuNOCpp
{
    namespace Core
    {
        enum class Comparison
        {
            NOT_EQUAL = 0,
            EQUAL,
            GREATER,
            GREATER_EQUAL,
            LESS,
            LESS_EQUAL,
            CUSTOM
        };

        template<class PrT, typename RT, Comparison cmp_operator>
        class Premise;
        
    } // namespace Core

    namespace Utils
    {
        namespace NOPTraits
        {
            // auto not_equal = [](auto lhs, auto rhs){ return lhs != rhs; };
            // using not_equal_t = decltype(not_equal);
            // auto equal = [](auto lhs, auto rhs){ return lhs == rhs; };
            // using equal_t = decltype(equal);
            // auto greater = [](auto lhs, auto rhs){ return lhs > rhs; };
            // using greater_t = decltype(greater);
            // auto greater_equal = [](auto lhs, auto rhs){ return lhs >= rhs; };
            // using greater_equal_t = decltype(greater_equal);
            // auto less = [](auto lhs, auto rhs){ return lhs < rhs; };
            // using less_t = decltype(less);
            // auto less_equal = [](auto lhs, auto rhs){ return lhs <= rhs; };
            // using less_equal_t = decltype(less_equal);

            template<typename T>
            struct is_valid_cmp_op: std::false_type {};

            // template<>
            // struct is_valid_cmp_op<not_equal_t>
            // : std::true_type {};
            // template<>
            // struct is_valid_cmp_op<equal_t>
            // : std::true_type {};
            // template<>
            // struct is_valid_cmp_op<greater_t>
            // : std::true_type {};
            // template<>
            // struct is_valid_cmp_op<greater_equal_t>
            // : std::true_type {};
            // template<>
            // struct is_valid_cmp_op<less_t>
            // : std::true_type {};
            // template<>
            // struct is_valid_cmp_op<less_equal_t>
            // : std::true_type {};

            // template<typename T>
            // inline constexpr bool is_valid_cmp_op_v = is_valid_cmp_op<T>::value;

            template<typename PrType, typename LType, typename RType>
            struct is_premise_of: std::false_type {};

            // template<typename LType, typename RType>
            // struct is_premise_of<Core::Premise<LType, RType, not_equal_t>, LType, RType>
            // : std::true_type {};

            // template<typename LType, typename RType>
            // struct is_premise_of<Core::Premise<LType, RType, equal_t>, LType, RType>
            // : std::true_type {};

            // template<typename LType, typename RType>
            // struct is_premise_of<Core::Premise<LType, RType, greater_t>, LType, RType>
            // : std::true_type {};

            // template<typename LType, typename RType>
            // struct is_premise_of<Core::Premise<LType, RType, greater_equal_t>, LType, RType>
            // : std::true_type {};

            // template<typename LType, typename RType>
            // struct is_premise_of<Core::Premise<LType, RType, less_t>, LType, RType>
            // : std::true_type {};

            // template<typename LType, typename RType>
            // struct is_premise_of<Core::Premise<LType, RType, less_equal_t>, LType, RType>
            // : std::true_type {};

            // template<typename LType, typename RType>
            // struct is_premise_of<Core::Premise<LType, RType, not_equal_t>*, LType, RType>
            // : std::true_type {};

            // template<typename LType, typename RType>
            // struct is_premise_of<Core::Premise<LType, RType, equal_t>*, LType, RType>
            // : std::true_type {};

            // template<typename LType, typename RType>
            // struct is_premise_of<Core::Premise<LType, RType, greater_t>*, LType, RType>
            // : std::true_type {};

            // template<typename LType, typename RType>
            // struct is_premise_of<Core::Premise<LType, RType, greater_equal_t>*, LType, RType>
            // : std::true_type {};

            // template<typename LType, typename RType>
            // struct is_premise_of<Core::Premise<LType, RType, less_t>*, LType, RType>
            // : std::true_type {};

            // template<typename LType, typename RType>
            // struct is_premise_of<Core::Premise<LType, RType, less_equal_t>*, LType, RType>
            // : std::true_type {};

            template<typename PrType, typename LType, typename RType>
            inline constexpr bool is_premise_of_v = is_premise_of<PrType, LType, RType>::value;
        } // namespace NOPTraits
        
    } // namespace Utils
    
} // namespace JuNOCpp

#endif // !JUNOCPP_PREMISE_TRAITS_HPP