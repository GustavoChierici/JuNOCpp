#ifndef JUNOCPP_TUPLE_HELPER_HPP
#define JUNOCPP_TUPLE_HELPER_HPP
#include <algorithm>
#include "./NOPTraits/attribute_traits.hpp"

namespace JuNOCpp
{   
    namespace Utils
    {
        template<typename Op, typename ... Args>
        struct tuple_helper;

        template<typename Op, typename ...Args>
        tuple_helper<Op, Args...> make_tuple_h(std::tuple<Args...> tup, Op _op);

        template<typename Op, typename ... Args>
        struct tuple_helper
        {
            std::tuple<Args...> tup;

            tuple_helper(std::tuple<Args...> tuple)
            : tup{tuple}
            {
            }

            ~tuple_helper() {}

            template<typename T>
            auto operator+(Core::Attribute<T>& attr)
            {
                if constexpr(std::is_same_v<Op, NOPTraits::at_add_at_t>)
                {
                    auto at_tup = std::make_tuple(&attr);
                    auto aux_tuple = std::tuple_cat(tup, at_tup);
                
                    auto th = make_tuple_h(aux_tuple, NOPTraits::at_add_at);

                    return th;
                }
                else if constexpr(std::is_same_v<Op, NOPTraits::val_add_at_t>)
                {
                    auto at_tup = std::make_tuple(&attr);
                    auto aux_tuple = std::tuple_cat(tup, at_tup);

                    auto th = make_tuple_h(aux_tuple, NOPTraits::val_add_at);
                    
                    return th;
                }
                else
                {
                    auto aux_tuple = std::make_tuple(NOPTraits::val_add_at, tup, &attr);
                    
                    auto th = make_tuple_h(aux_tuple, NOPTraits::val_add_at);

                    return th;
                }
            }

            template<typename T>
            auto operator+(T value)
            {
                if constexpr(std::is_same_v<Op, NOPTraits::at_add_val_t>)
                {
                    auto val_tup = std::make_tuple(value);
                    auto aux_tuple = std::tuple_cat(tup, val_tup);

                    auto th = make_tuple_h(aux_tuple, NOPTraits::at_add_val);

                    return th;
                }
                else if constexpr(std::is_same_v<Op, NOPTraits::val_add_val_t>)
                {
                    auto val_tup = std::make_tuple(value);
                    auto aux_tuple = std::tuple_cat(tup, val_tup);
                    
                    auto th = make_tuple_h(aux_tuple, NOPTraits::val_add_val);

                    return th;
                }
                else
                {
                    auto aux_tuple = std::make_tuple(NOPTraits::val_add_val, tup, value);
                    
                    auto th = make_tuple_h(aux_tuple, NOPTraits::val_add_val);

                    return th;
                }
                
            }

            template<typename ...T>
            auto operator+(tuple_helper<T...> tuple_h)
            {
                auto aux_tuple = std::make_tuple(NOPTraits::val_add_val, tup, tuple_h.tup);

                auto th = make_tuple_h(aux_tuple, NOPTraits::val_add_val);

                return th;
            }

            template<typename T>
            auto operator-(Core::Attribute<T>& attr)
            {
                if constexpr(std::is_same_v<Op, NOPTraits::at_sub_at_t>)
                {
                    auto at_tup = std::make_tuple(&attr);
                    auto aux_tuple = std::tuple_cat(tup,at_tup);
                
                    auto th = make_tuple_h(aux_tuple, NOPTraits::at_sub_at);

                    return th;
                }
                else if constexpr(std::is_same_v<Op, NOPTraits::val_sub_at_t>)
                {
                    auto at_tup = std::make_tuple(&attr);
                    auto aux_tuple = std::tuple_cat(tup, at_tup);

                    auto th = make_tuple_h(aux_tuple, NOPTraits::val_sub_at);
                    
                    return th;
                }
                else
                {
                    auto aux_tuple = std::make_tuple(Utils::NOPTraits::val_sub_at, tup, &attr);
                    
                    auto th = make_tuple_h(aux_tuple, NOPTraits::val_sub_at);

                    return th;
                }
            }

            template<typename T>
            auto operator-(T value)
            {
                if constexpr(std::is_same_v<Op, NOPTraits::at_sub_val_t>)
                {
                    auto val_tup = std::make_tuple(value);
                    auto aux_tuple = std::tuple_cat(tup, val_tup);

                    auto th = make_tuple_h(aux_tuple, NOPTraits::at_sub_val);

                    return th;
                }
                else if constexpr(std::is_same_v<Op, NOPTraits::val_sub_val_t>)
                {
                    auto val_tup = std::make_tuple(value);
                    auto aux_tuple = std::tuple_cat(tup, val_tup);
                    
                    auto th = make_tuple_h(aux_tuple, NOPTraits::val_sub_val);

                    return th;
                }
                else
                {
                    auto aux_tuple = std::make_tuple(NOPTraits::val_sub_val, tup, value);
                    
                    auto th = make_tuple_h(aux_tuple, NOPTraits::val_sub_val);

                    return th;
                } 
            }

            template<typename ...T>
            auto operator-(tuple_helper<T...> tuple_h)
            {
                auto aux_tuple = std::make_tuple(NOPTraits::val_sub_val, tup, tuple_h.tup);
                
                auto th = make_tuple_h(aux_tuple, NOPTraits::val_sub_val);

                return th;
            }

            template<typename T>
            auto operator*(Core::Attribute<T>& attr)
            {
                if constexpr(std::is_same_v<Op, NOPTraits::at_mult_at_t>)
                {
                    auto at_tup = std::make_tuple(&attr);
                    auto aux_tuple = std::tuple_cat(tup,at_tup);
                
                    auto th = make_tuple_h(aux_tuple, NOPTraits::at_mult_at);

                    return th;
                }
                else if constexpr(std::is_same_v<Op, NOPTraits::val_mult_at_t>)
                {
                    auto at_tup = std::make_tuple(&attr);
                    auto aux_tuple = std::tuple_cat(tup, at_tup);

                    auto th = make_tuple_h(aux_tuple, NOPTraits::val_mult_at);
                    
                    return th;
                }
                else
                {
                    auto aux_tuple = std::make_tuple(Utils::NOPTraits::val_mult_at, tup, &attr);
                    
                    auto th = make_tuple_h(aux_tuple, NOPTraits::val_mult_at);

                    return th;
                }
            }

            template<typename T>
            auto operator*(T value)
            {
                if constexpr(std::is_same_v<Op, NOPTraits::at_mult_val_t>)
                {
                    auto val_tup = std::make_tuple(value);
                    auto aux_tuple = std::tuple_cat(tup, val_tup);

                    auto th = make_tuple_h(aux_tuple, NOPTraits::at_mult_val);

                    return th;
                }
                else if constexpr(std::is_same_v<Op, NOPTraits::val_mult_val_t>)
                {
                    auto val_tup = std::make_tuple(value);
                    auto aux_tuple = std::tuple_cat(tup, val_tup);
                    
                    auto th = make_tuple_h(aux_tuple, NOPTraits::val_mult_val);

                    return th;
                }
                else
                {
                    auto aux_tuple = std::make_tuple(NOPTraits::val_mult_val, tup, value);
                    
                    auto th = make_tuple_h(aux_tuple, NOPTraits::val_mult_val);

                    return th;
                }
                
            }

            template<typename ...T>
            auto operator*(tuple_helper<T...> tuple_h)
            {
                auto aux_tuple = std::make_tuple(NOPTraits::val_mult_val, tup, tuple_h.tup);
                
                auto th = make_tuple_h(aux_tuple, NOPTraits::val_div_val);

                return th;
            }

            template<typename T>
            auto operator/(Core::Attribute<T>& attr)
            {
                if constexpr(std::is_same_v<Op, NOPTraits::at_div_at_t>)
                {
                    auto at_tup = std::make_tuple(&attr);
                    auto aux_tuple = std::tuple_cat(tup,at_tup);
                
                    auto th = make_tuple_h(aux_tuple, NOPTraits::at_div_at);

                    return th;
                }
                else if constexpr(std::is_same_v<Op, NOPTraits::val_div_at_t>)
                {
                    auto at_tup = std::make_tuple(&attr);
                    auto aux_tuple = std::tuple_cat(tup, at_tup);

                    auto th = make_tuple_h(aux_tuple, NOPTraits::val_div_at);
                    
                    return th;
                }
                else
                {
                    auto aux_tuple = std::make_tuple(Utils::NOPTraits::val_div_at, tup, &attr);
                    
                    auto th = make_tuple_h(aux_tuple, NOPTraits::val_div_at);

                    return th;
                }
            }

            template<typename T>
            auto operator/(T value)
            {
                if constexpr(std::is_same_v<Op, NOPTraits::at_div_val_t>)
                {
                    auto val_tup = std::make_tuple(value);
                    auto aux_tuple = std::tuple_cat(tup, val_tup);

                    auto th = make_tuple_h(aux_tuple, NOPTraits::at_div_val);

                    return th;
                }
                else if constexpr(std::is_same_v<Op, NOPTraits::val_div_val_t>)
                {
                    auto val_tup = std::make_tuple(value);
                    auto aux_tuple = std::tuple_cat(tup, val_tup);
                    
                    auto th = make_tuple_h(aux_tuple, NOPTraits::val_div_val);

                    return th;
                }
                else
                {
                    auto aux_tuple = std::make_tuple(NOPTraits::val_div_val, tup, value);
                    
                    auto th = make_tuple_h(aux_tuple, NOPTraits::val_div_val);

                    return th;
                }
                
            }

            template<typename ...T>
            auto operator/(tuple_helper<T...> tuple_h)
            {
                auto aux_tuple = std::make_tuple(NOPTraits::val_div_val, tup, tuple_h.tup);
                
                auto th = make_tuple_h(aux_tuple, NOPTraits::val_div_val);

                return th;
            }

        };

        template<typename Op, typename ...Args>
        tuple_helper<Op, Args...> make_tuple_h(std::tuple<Args...> tup, Op _op)
        {
            return {tup};
        }

    } // namespace Utils
    
} // namespace JuNOCpp

#endif // !JUNOCPP_TUPLE_HELPER_HPP