#ifndef JUNOCPP_ATTRIBUTE_HPP
#define JUNOCPP_ATTRIBUTE_HPP

#include "Notifier.hpp"
#include "NOPManager.hpp"
#include "tuple_helper.hpp"
#include "premise_traits.hpp"

namespace JuNOCpp
{
    namespace Core
    {
        enum class Comparison; 
        template <typename LT, typename RT, Comparison cmp_operator>
        class Premise;
        
        template<Comparison cmp_operator, typename LT, typename RT>
        auto make_premise(LT lhs, RT rhs, Utils::CustomString name);

        template<class TYPE>
        class Attribute: public Notifier, public Notifiable
        {
        public:
            Attribute(Utils::CustomString name = "UnnamedAttribute");
            Attribute(TYPE value, Utils::CustomString name = "UnnamedAttribute");
            Attribute(const Attribute& rhs);
            Attribute(Attribute&& rhs);
            ~Attribute();

            TYPE getPreviousValue();
            TYPE getValue();

            void setValue(TYPE value, bool renotify = false);

            void update(const bool renotify = false);
            void update(const bool renotify, const bool status) {}

            void addImpertinent(shared_ptr<Notifiable> impertinent)
            {
                _impertinents.push_back(impertinent);
            }

            auto operator+(Attribute<TYPE>& attr);
            template<typename ...T>
            auto operator+(Utils::tuple_helper<T...> tup_h);
            auto operator+(TYPE value);

            auto operator-(Attribute<TYPE>& b_attr);
            template<typename ...T>
            auto operator-(Utils::tuple_helper<T...> tup_h);
            auto operator-(TYPE value);

            auto operator*(Attribute<TYPE>& b_attr);
            template<typename ...T>
            auto operator*(Utils::tuple_helper<T...> tup_h);
            auto operator*(TYPE value);

            auto operator/(Attribute<TYPE>& b_attr);
            template<typename ...T>
            auto operator/(Utils::tuple_helper<T...> tup_h);
            auto operator/(TYPE value);

            void operator=(TYPE value);

            Premise<Attribute<TYPE>*, Attribute<TYPE>*, Comparison::EQUAL>& operator==(Attribute<TYPE>& b_attr);
            Premise<Attribute<TYPE>*, Attribute<TYPE>*, Comparison::EQUAL>& operator==(Attribute<TYPE>&& b_attr);
            template<typename _Op, typename ...T>
            Premise<Attribute<TYPE>*, std::tuple<T...>, Comparison::EQUAL>& operator==(Utils::tuple_helper<_Op, T...> tup_h);

            Premise<Attribute<TYPE>*, Attribute<TYPE>*, Comparison::NOT_EQUAL>& operator!=(Attribute<TYPE>& b_attr);
            Premise<Attribute<TYPE>*, Attribute<TYPE>*, Comparison::NOT_EQUAL>& operator!=(Attribute<TYPE>&& b_attr);
            template<typename _Op, typename ...T>
            Premise<Attribute<TYPE>*, std::tuple<T...>, Comparison::NOT_EQUAL>& operator!=(Utils::tuple_helper<_Op, T...> tup_h);

            Premise<Attribute<TYPE>*, Attribute<TYPE>*, Comparison::GREATER>& operator>(Attribute<TYPE>& b_attr);
            Premise<Attribute<TYPE>*, Attribute<TYPE>*, Comparison::GREATER>& operator>(Attribute<TYPE>&& b_attr);
            template<typename _Op, typename ...T>
            Premise<Attribute<TYPE>*, std::tuple<T...>, Comparison::GREATER>& operator>(Utils::tuple_helper<_Op, T...> tup_h);

            Premise<Attribute<TYPE>*, Attribute<TYPE>*, Comparison::GREATER_EQUAL>& operator>=(Attribute<TYPE>& b_attr);
            Premise<Attribute<TYPE>*, Attribute<TYPE>*, Comparison::GREATER_EQUAL>& operator>=(Attribute<TYPE>&& b_attr);
            template<typename _Op, typename ...T>
            Premise<Attribute<TYPE>*, std::tuple<T...>, Comparison::GREATER_EQUAL>& operator>=(Utils::tuple_helper<_Op, T...> tup_h);

            Premise<Attribute<TYPE>*, Attribute<TYPE>*, Comparison::LESS>& operator<(Attribute<TYPE>& b_attr);
            Premise<Attribute<TYPE>*, Attribute<TYPE>*, Comparison::LESS>& operator<(Attribute<TYPE>&& b_attr);
            template<typename _Op, typename ...T>
            Premise<Attribute<TYPE>*, std::tuple<T...>, Comparison::LESS>& operator<(Utils::tuple_helper<_Op, T...> tup_h);

            Premise<Attribute<TYPE>*, Attribute<TYPE>*, Comparison::LESS_EQUAL>& operator<=(Attribute<TYPE>& b_attr);
            Premise<Attribute<TYPE>*, Attribute<TYPE>*, Comparison::LESS_EQUAL>& operator<=(Attribute<TYPE>&& b_attr);
            template<typename _Op, typename ...T>
            Premise<Attribute<TYPE>*, std::tuple<T...>, Comparison::LESS_EQUAL>& operator<=(Utils::tuple_helper<_Op, T...> tup_h);

            Premise<Attribute<TYPE>*, TYPE, Comparison::EQUAL>& operator==(const TYPE value);
            Premise<Attribute<TYPE>*, TYPE, Comparison::NOT_EQUAL>& operator!=(const TYPE value);
            Premise<Attribute<TYPE>*, TYPE, Comparison::GREATER>& operator>(const TYPE value);
            Premise<Attribute<TYPE>*, TYPE, Comparison::GREATER_EQUAL>& operator>=(const TYPE value);
            Premise<Attribute<TYPE>*, TYPE, Comparison::LESS>& operator<(const TYPE value);
            Premise<Attribute<TYPE>*, TYPE, Comparison::LESS_EQUAL>& operator<=(const TYPE value);
            
        private:
            TYPE value;
            TYPE p_value;

            Utils::forward_list<shared_ptr<Notifiable>> _impertinents;
        };

        /**
         * Constrututor
         * 
         * @tparam TYPE 
         */
        template<class TYPE>
        Attribute<TYPE>::Attribute(Utils::CustomString name):
        Notifiable(name)
        {
        }

        /**
         * Construtor com valor inicial
         * 
         * @tparam TYPE 
         * @param value 
         */
        template<class TYPE>
        Attribute<TYPE>::Attribute(TYPE value, Utils::CustomString name):
        Notifiable(name),
        value{value},
        p_value{value}
        {
            // this->value = value;
            // this->p_value = value;
        }

        /**
         * @brief Construtor (copy constructor)
         * 
         * @tparam TYPE 
         * @param rhs 
         */
        template <class TYPE>
        Attribute<TYPE>::Attribute(const Attribute<TYPE>& rhs):
        Notifiable{rhs.name},
        Notifier{rhs.notifiables},
        value{rhs.value},
        p_value{rhs.p_value}
        {
        }

        /**
         * @brief Construtor (move constructor)
         * 
         * @tparam TYPE 
         * @param rhs 
         */
        template <class TYPE>
        Attribute<TYPE>::Attribute(Attribute&& rhs):
        Notifiable{rhs.name},
        Notifier{rhs.notifiables},
        value{rhs.value},
        p_value{rhs.p_value}
        {
        }

        /**
         * Destrutor
         * 
         * @tparam TYPE 
         */
        template<class TYPE>
        Attribute<TYPE>::~Attribute()
        {
        }

        /**
         * Getter do p_value 
         * 
         * @tparam TYPE 
         * @return TYPE 
         */
        template<class TYPE>
        TYPE Attribute<TYPE>::getPreviousValue()
        {
            return this->p_value;
        }

        /**
         * Getter do value
         * 
         * @tparam TYPE 
         * @return TYPE 
         */
        template<class TYPE>
        TYPE Attribute<TYPE>::getValue()
        {
            return this->value;
        }

        /**
         * Provoca uma cadeia de notificações se o valor do Attribute for alterado ou se a flag renotify for true
         * 
         * @tparam TYPE 
         * @param value 
         * @param renotify == false
         */
        template<class TYPE>
        void Attribute<TYPE>::setValue(TYPE value, bool renotify)
        {
            if(renotify || value != this->value)
            {
                #ifdef SHOW_NOP_LOGGER
                    Utils::NOPLogger::Get().writeAssignment(name, this, value, renotify);
                    Utils::NOPLogger::Get().writeNotifying(name, this, renotify);

                    Utils::NOPLogger::Get().incrementIdentation();
                #endif // SHOW_NOP_LOGGER

                this->p_value = this->value;
                this->value = value;

                notify(renotify);

                #ifdef SHOW_NOP_LOGGER
                    Utils::NOPLogger::Get().decrementIdentation();
                #endif // SHOW_NOP_LOGGER    
            }
        }

        /**
         * Atualiza o valor do Attribute composto e provoca uma cadeia de notificações
         * 
         * @tparam TYPE 
         * @param renotify 
         */
        template<class TYPE>
        void Attribute<TYPE>::update(bool renotify)
        {
            // this->value = this->updateOperation(this->value, value);
            std::cout << this << std::endl;
            std::cout << "Não era pra você estar aqui" << std::endl;
            // notify(renotify);
        }

        template <class TYPE>
        auto Attribute<TYPE>::operator+(Attribute<TYPE>& attr)
        {
            return Utils::make_tuple_h(std::make_tuple
                (Utils::NOPTraits::at_add_at, this, &attr), Utils::NOPTraits::at_add_at);
        }
        
        template <class TYPE>
        template<typename ...T>
        auto Attribute<TYPE>::operator+(Utils::tuple_helper<T...> tup_h)
        {
            return Utils::make_tuple_h(std::make_tuple
                (Utils::NOPTraits::at_add_val, this, tup_h.tup), Utils::NOPTraits::at_add_val);
        }

        template <class TYPE>
        auto Attribute<TYPE>::operator+(TYPE value)
        {
            return Utils::make_tuple_h(std::make_tuple
                (Utils::NOPTraits::at_add_val, this, value), Utils::NOPTraits::at_add_val);
        }

        template <class TYPE>
        auto Attribute<TYPE>::operator-(Attribute<TYPE>& attr)
        {
            return Utils::make_tuple_h(std::make_tuple
                (Utils::NOPTraits::at_sub_at, this, &attr), Utils::NOPTraits::at_sub_at);
        }
        
        template <class TYPE>
        template<typename ...T>
        auto Attribute<TYPE>::operator-(Utils::tuple_helper<T...> tup_h)
        {
            return Utils::make_tuple_h(std::make_tuple
                (Utils::NOPTraits::at_sub_val, this, tup_h.tup), Utils::NOPTraits::at_sub_val);
        }

        template <class TYPE>
        auto Attribute<TYPE>::operator-(TYPE value)
        {
            return Utils::make_tuple_h(std::make_tuple
                (Utils::NOPTraits::at_sub_val, this, value), Utils::NOPTraits::at_sub_val);
        }

        template <class TYPE>
        auto Attribute<TYPE>::operator*(Attribute<TYPE>& attr)
        {
            return Utils::make_tuple_h(std::make_tuple
                (Utils::NOPTraits::at_mult_at, this, &attr), Utils::NOPTraits::at_mult_at);
        }
        
        template <class TYPE>
        template<typename ...T>
        auto Attribute<TYPE>::operator*(Utils::tuple_helper<T...> tup_h)
        {
            return Utils::make_tuple_h(std::make_tuple
                (Utils::NOPTraits::at_mult_val, this, tup_h.tup), Utils::NOPTraits::at_mult_val);
        }

        template <class TYPE>
        auto Attribute<TYPE>::operator*(TYPE value)
        {
            return Utils::make_tuple_h(std::make_tuple
                (Utils::NOPTraits::at_mult_val, this, value), Utils::NOPTraits::at_mult_val);
        }

        template <class TYPE>
        auto Attribute<TYPE>::operator/(Attribute<TYPE>& attr)
        {
            return Utils::make_tuple_h(std::make_tuple
                (Utils::NOPTraits::at_div_at, this, &attr), Utils::NOPTraits::at_div_at);
        }
        
        template <class TYPE>
        template<typename ...T>
        auto Attribute<TYPE>::operator/(Utils::tuple_helper<T...> tup_h)
        {
            return Utils::make_tuple_h(std::make_tuple
                (Utils::NOPTraits::at_div_val, this, tup_h.tup), Utils::NOPTraits::at_div_val);
        }

        template <class TYPE>
        auto Attribute<TYPE>::operator/(TYPE value)
        {
            return Utils::make_tuple_h(std::make_tuple
                (Utils::NOPTraits::at_div_val, this, value), Utils::NOPTraits::at_div_val);
        }

        /**
         * Overload do operator = para chamar automaticamente o método setValue
         * 
         * @tparam TYPE 
         * @param value 
         */
        template<class TYPE>
        void Attribute<TYPE>::operator=(TYPE value)
        {
            setValue(value);
        }

        /**
         * @brief Cria e retorna uma Premise do tipo equal
         * 
         * @tparam TYPE 
         * @param b_attr 
         * @return Premise<Attribute<TYPE>*, Attribute<TYPE>*, Comparison::EQUAL>& 
         */
        template <class TYPE>
        Premise<Attribute<TYPE>*, Attribute<TYPE>*, Comparison::EQUAL>& Attribute<TYPE>::operator==(Attribute<TYPE>& b_attr)
        {
            std::string pr_name = name.getString();
            pr_name += "Equals";
            pr_name += b_attr.name.getString(); 

            auto premise = make_premise<Comparison::EQUAL>(this, &b_attr, pr_name);

            return *premise;
        }

        /**
         * @brief Cria e retorna uma Premise do tipo equal
         * 
         * @tparam TYPE 
         * @param b_attr 
         * @return Premise<Attribute<TYPE>*, Attribute<TYPE>*, Comparison::EQUAL>&
         */
        template <class TYPE>
        Premise<Attribute<TYPE>*, Attribute<TYPE>*, Comparison::EQUAL>& Attribute<TYPE>::operator==(Attribute<TYPE>&& b_attr)
        {
            std::string pr_name = name.getString();
            pr_name += "Equals";
            pr_name += b_attr.name.getString();

            auto premise = make_premise<Comparison::EQUAL>(this, &b_attr, pr_name);

            return *premise;
        }

        /**
         * @brief Cria e retorna uma Premise do tipo equal (com um tupla de Attributes)
         * 
         * @tparam TYPE 
         * @tparam _Op 
         * @tparam T 
         * @param tup_h 
         * @return Premise<Attribute<TYPE>*, std::tuple<T...>, Comparison::EQUAL>& 
         */
        template <class TYPE>
        template<typename _Op, typename ...T>
        Premise<Attribute<TYPE>*, std::tuple<T...>, Comparison::EQUAL>& Attribute<TYPE>::operator==(Utils::tuple_helper<_Op, T...> tup_h)
        {
            std::string pr_name = name.getString();
            pr_name += "EqualsArgs";

            auto premise = make_premise<Comparison::EQUAL>(this, tup_h.tup, pr_name);

            return *premise;
        }

        /**
         * @brief Cria e retorna uma Premise do tipo not_equal
         * 
         * @tparam TYPE 
         * @param b_attr 
         * @return Premise<Attribute<TYPE>*, Attribute<TYPE>*, Comparison::NOT_EQUAL>& 
         */
        template <class TYPE>
        Premise<Attribute<TYPE>*, Attribute<TYPE>*, Comparison::NOT_EQUAL>& Attribute<TYPE>::operator!=(Attribute<TYPE>& b_attr)
        {
            std::string pr_name = name.getString();
            pr_name += "NotEqual";
            pr_name += b_attr.name.getString(); 

            auto premise = make_premise<Comparison::NOT_EQUAL>(this, &b_attr, pr_name);

            return *premise;
        }

        /**
         * @brief Cria e retorna uma Premise do tipo not_equal
         * 
         * @tparam TYPE 
         * @param b_attr 
         * @return Premise<Attribute<TYPE>*, Attribute<TYPE>*, Comparison::NOT_EQUAL>& 
         */
        template <class TYPE>
        Premise<Attribute<TYPE>*, Attribute<TYPE>*, Comparison::NOT_EQUAL>& Attribute<TYPE>::operator!=(Attribute<TYPE>&& b_attr)
        {
            std::string pr_name = name.getString();
            pr_name += "NotEqual";
            pr_name += b_attr.name.getString(); 

            auto premise = make_premise<Comparison::NOT_EQUAL>(this, &b_attr, pr_name);

            return *premise;
        }

        /**
         * @brief Cria e retorna uma Premise do tipo not_equal (com um tupla de Attributes)
         * 
         * @tparam TYPE 
         * @tparam _Op 
         * @tparam T 
         * @param tup_h 
         * @return Premise<Attribute<TYPE>*, std::tuple<T...>, Comparison::NOT_EQUAL>& 
         */
        template <class TYPE>
        template<typename _Op, typename ...T>
        Premise<Attribute<TYPE>*, std::tuple<T...>, Comparison::NOT_EQUAL>& Attribute<TYPE>::operator!=(Utils::tuple_helper<_Op, T...> tup_h)
        {
            std::string pr_name = name.getString();
            pr_name += "EqualsArgs";

            auto premise = make_premise<Comparison::NOT_EQUAL>(this, tup_h.tup, pr_name);

            return *premise;
        }

        /**
         * @brief Cria e retorna uma Premise do tipo greater
         * 
         * @tparam TYPE 
         * @param b_attr 
         * @return Premise<Attribute<TYPE>*, Attribute<TYPE>*, Comparison::GREATER>& 
         */
        template <class TYPE>
        Premise<Attribute<TYPE>*, Attribute<TYPE>*, Comparison::GREATER>& Attribute<TYPE>::operator>(Attribute<TYPE>& b_attr)
        {
            std::string pr_name = name.getString();
            pr_name += "IsGreaterThan";
            pr_name += b_attr.name.getString(); 

            auto premise = make_premise<Comparison::GREATER>(this, &b_attr, pr_name);

            return *premise;
        }

        /**
         * @brief Cria e retorna uma Premise do tipo greater
         * 
         * @tparam TYPE 
         * @param b_attr 
         * @return Premise<Attribute<TYPE>*, Attribute<TYPE>*, Comparison::GREATER>& 
         */
        template <class TYPE>
        Premise<Attribute<TYPE>*, Attribute<TYPE>*, Comparison::GREATER>& Attribute<TYPE>::operator>(Attribute<TYPE>&& b_attr)
        {
            std::string pr_name = name.getString();
            pr_name += "IsGreaterThan";
            pr_name += b_attr.name.getString(); 

            auto premise = make_premise<Comparison::GREATER>(this, &b_attr, pr_name);

            return *premise;
        }

        /**
         * @brief Cria e retorna uma Premise do tipo greater (com um tupla de Attributes)
         * 
         * @tparam TYPE 
         * @tparam _Op 
         * @tparam T 
         * @param tup_h 
         * @return Premise<Attribute<TYPE>*, std::tuple<T...>, Comparison::GREATER>& 
         */
        template <class TYPE>
        template<typename _Op, typename ...T>
        Premise<Attribute<TYPE>*, std::tuple<T...>, Comparison::GREATER>& Attribute<TYPE>::operator>(Utils::tuple_helper<_Op, T...> tup_h)
        {
            std::string pr_name = name.getString();
            pr_name += "EqualsArgs";

            auto premise = make_premise<Comparison::GREATER>(this, tup_h.tup, pr_name);

            return *premise;
        }

        /**
         * @brief Cria e retorna uma Premise do tipo greater_equal
         * 
         * @tparam TYPE 
         * @param b_attr 
         * @return Premise<Attribute<TYPE>*, Attribute<TYPE>*, Comparison::GREATER_EQUAL>& 
         */
        template <class TYPE>
        Premise<Attribute<TYPE>*, Attribute<TYPE>*, Comparison::GREATER_EQUAL>& Attribute<TYPE>::operator>=(Attribute<TYPE>& b_attr)
        {
            std::string pr_name = name.getString();
            pr_name += "IsGreaterOrEqual";
            pr_name += b_attr.name.getString(); 

            auto premise = make_premise<Comparison::GREATER_EQUAL>(this, &b_attr, pr_name);

            return *premise;
        }

        /**
         * @brief Cria e retorna uma Premise do tipo greater_equal
         * 
         * @tparam TYPE 
         * @param b_attr 
         * @return Premise<Attribute<TYPE>*, Attribute<TYPE>*, Comparison::GREATER_EQUAL>& 
         */
        template <class TYPE>
        Premise<Attribute<TYPE>*, Attribute<TYPE>*, Comparison::GREATER_EQUAL>& Attribute<TYPE>::operator>=(Attribute<TYPE>&& b_attr)
        {
            std::string pr_name = name.getString();
            pr_name += "IsGreaterOrEqual";
            pr_name += b_attr.name.getString(); 

            auto premise = make_premise<Comparison::GREATER_EQUAL>(this, &b_attr, pr_name);

            return *premise;
        }

        /**
         * @brief Cria e retorna uma Premise do tipo greater_equal (com um tupla de Attributes)
         * 
         * @tparam TYPE 
         * @tparam _Op 
         * @tparam T 
         * @param tup_h 
         * @return Premise<Attribute<TYPE>*, std::tuple<T...>, Comparison::GREATER_EQUAL>& 
         */
        template <class TYPE>
        template<typename _Op, typename ...T>
        Premise<Attribute<TYPE>*, std::tuple<T...>, Comparison::GREATER_EQUAL>& Attribute<TYPE>::operator>=(Utils::tuple_helper<_Op, T...> tup_h)
        {
            std::string pr_name = name.getString();
            pr_name += "EqualsArgs";

            auto premise = make_premise<Comparison::GREATER_EQUAL>(this, tup_h.tup, pr_name);

            return *premise;
        }

        /**
         * @brief Cria e retorna uma Premise do tipo less
         * 
         * @tparam TYPE 
         * @param b_attr 
         * @return Premise<Attribute<TYPE>*, Attribute<TYPE>*, Comparison::LESS>& 
         */
        template <class TYPE>
        Premise<Attribute<TYPE>*, Attribute<TYPE>*, Comparison::LESS>& Attribute<TYPE>::operator<(Attribute<TYPE>& b_attr)
        {
            std::string pr_name = name.getString();
            pr_name += "IsLessThan";
            pr_name += b_attr.name.getString();

            auto premise = make_premise<Comparison::LESS>(this, &b_attr, pr_name);

            return *premise;
        }

        /**
         * @brief Cria e retorna uma Premise do tipo less
         * 
         * @tparam TYPE 
         * @param b_attr 
         * @return Premise<Attribute<TYPE>*, Attribute<TYPE>*, Comparison::LESS>& 
         */
        template <class TYPE>
        Premise<Attribute<TYPE>*, Attribute<TYPE>*, Comparison::LESS>& Attribute<TYPE>::operator<(Attribute<TYPE>&& b_attr)
        {
            std::string pr_name = name.getString();
            pr_name += "IsLessThan";
            pr_name += b_attr.name.getString(); 

            auto premise = make_premise<Comparison::LESS>(this, &b_attr, pr_name);

            return *premise;
        }

        /**
         * @brief Cria e retorna uma Premise do tipo less (com um tupla de Attributes)
         * 
         * @tparam TYPE 
         * @tparam _Op 
         * @tparam T 
         * @param tup_h 
         * @return Premise<Attribute<TYPE>*, std::tuple<T...>, Comparison::LESS>& 
         */
        template <class TYPE>
        template<typename _Op, typename ...T>
        Premise<Attribute<TYPE>*, std::tuple<T...>, Comparison::LESS>& Attribute<TYPE>::operator<(Utils::tuple_helper<_Op, T...> tup_h)
        {
            std::string pr_name = name.getString();
            pr_name += "EqualsArgs";

            auto premise = make_premise<Comparison::LESS>(this, tup_h.tup, pr_name);

            return *premise;
        }

        /**
         * @brief Cria e retorna uma Premise do tipo less_equal
         * 
         * @tparam TYPE 
         * @param b_attr 
         * @return Premise<Attribute<TYPE>*, Attribute<TYPE>*, Comparison::LESS_EQUAL>& 
         */
        template <class TYPE>
        Premise<Attribute<TYPE>*, Attribute<TYPE>*, Comparison::LESS_EQUAL>& Attribute<TYPE>::operator<=(Attribute<TYPE>& b_attr)
        {
            std::string pr_name = name.getString();
            pr_name += "IsLessOrEqual";
            pr_name += b_attr.name.getString(); 

            auto premise = make_premise<Comparison::LESS_EQUAL>(this, &b_attr, pr_name);

            return *premise;
        }

        /**
         * @brief Cria e retorna uma Premise do tipo less_equal
         * 
         * @tparam TYPE 
         * @param b_attr 
         * @return Premise<Attribute<TYPE>*, Attribute<TYPE>*, Comparison::LESS_EQUAL>& 
         */
        template <class TYPE>
        Premise<Attribute<TYPE>*, Attribute<TYPE>*, Comparison::LESS_EQUAL>& Attribute<TYPE>::operator<=(Attribute<TYPE>&& b_attr)
        {
            std::string pr_name = name.getString();
            pr_name += "IsLessOrEqual";
            pr_name += b_attr.name.getString(); 

            auto premise = make_premise<Comparison::LESS_EQUAL>(this, &b_attr, pr_name);

            return *premise;
        }

        /**
         * @brief Cria e retorna uma Premise do tipo less_equal (com um tupla de Attributes)
         * 
         * @tparam TYPE 
         * @tparam _Op 
         * @tparam T 
         * @param tup_h 
         * @return Premise<Attribute<TYPE>*, std::tuple<T...>, Comparison::LESS_EQUAL>& 
         */
        template <class TYPE>
        template<typename _Op, typename ...T>
        Premise<Attribute<TYPE>*, std::tuple<T...>, Comparison::LESS_EQUAL>& Attribute<TYPE>::operator<=(Utils::tuple_helper<_Op, T...> tup_h)
        {
            std::string pr_name = name.getString();
            pr_name += "EqualsArgs";

            auto premise = make_premise<Comparison::LESS_EQUAL>(this, tup_h.tup, pr_name);

            return *premise;
        }

        /**
         * Cria e retorna uma Premise do tipo equal (com valor constante)
         * 
         * @tparam TYPE 
         * @param value 
         * @return Premise<Attribute<TYPE>*, TYPE, Comparison::EQUAL>& 
         */
        template <class TYPE>
        Premise<Attribute<TYPE>*, TYPE, Comparison::EQUAL>& Attribute<TYPE>::operator==(const TYPE value)
        {
            std::string pr_name = name.getString();
            pr_name += "Equals";
            if constexpr(Utils::NOPTraits::is_string_v<TYPE>)
                pr_name += value;
            else if constexpr( std::is_integral_v<TYPE> or std::is_floating_point_v<TYPE>)
                pr_name += std::to_string(value);
            else
                pr_name += "Value";
                
            auto premise = make_premise<Comparison::EQUAL>(this, value, pr_name);

            return *premise;
        }

        /**
         * Cria e retorna uma Premise do tipo not_equal (com valor constante)
         * 
         * @tparam TYPE 
         * @param value 
         * @return Premise<Attribute<TYPE>*, TYPE, Comparison::NOT_EQUAL>& 
         */
        template <class TYPE>
        Premise<Attribute<TYPE>*, TYPE, Comparison::NOT_EQUAL>& Attribute<TYPE>::operator!=(const TYPE value)
        {
            std::string pr_name = name.getString();
            pr_name += "NotEqual";
            if constexpr(Utils::NOPTraits::is_string_v<TYPE>)
                pr_name += value;
            else if constexpr( std::is_integral_v<TYPE> or std::is_floating_point_v<TYPE>)
                pr_name += std::to_string(value);
            else
                pr_name += "Value";

            auto premise = make_premise<Comparison::NOT_EQUAL>(this, value, pr_name);

            return *premise;
        }

        /**
         * Cria e retorna uma Premise do tipo greater (com valor constante)
         * 
         * @tparam TYPE 
         * @param value 
         * @return Premise<Attribute<TYPE>*, TYPE, Comparison::GREATER>& 
         */
        template <class TYPE>
        Premise<Attribute<TYPE>*, TYPE, Comparison::GREATER>& Attribute<TYPE>::operator>(const TYPE value)
        {
            std::string pr_name = name.getString();
            pr_name += "IsGreaterThan";
            if constexpr(Utils::NOPTraits::is_string_v<TYPE>)
                pr_name += value;
            else if constexpr( std::is_integral_v<TYPE> or std::is_floating_point_v<TYPE>)
                pr_name += std::to_string(value);
            else
                pr_name += "Value";

            auto premise = make_premise<Comparison::GREATER>(this, value, pr_name);

            return *premise;
        }

        /**
         * Cria e retorna uma Premise do tipo greater_equal (com valor constante)
         * 
         * @tparam TYPE 
         * @param value 
         * @return Premise<Attribute<TYPE>*, TYPE, Comparison::GREATER_EQUAL>& 
         */
        template <class TYPE>
        Premise<Attribute<TYPE>*, TYPE, Comparison::GREATER_EQUAL>& Attribute<TYPE>::operator>=(const TYPE value)
        {
            std::string pr_name = name.getString();
            pr_name += "IsGreaterOrEqual";
            if constexpr(Utils::NOPTraits::is_string_v<TYPE>)
                pr_name += value;
            else if constexpr( std::is_integral_v<TYPE> or std::is_floating_point_v<TYPE>)
                pr_name += std::to_string(value);
            else
                pr_name += "Value";

            auto premise = make_premise<Comparison::GREATER_EQUAL>(this, value, pr_name);

            return *premise;
        }

        /**
         * Cria e retorna uma Premise do tipo less (com valor constante)
         * 
         * @tparam TYPE 
         * @param value 
         * @return Premise<Attribute<TYPE>*, TYPE, Comparison::LESS>& 
         */
        template <class TYPE>
        Premise<Attribute<TYPE>*, TYPE, Comparison::LESS>& Attribute<TYPE>::operator<(const TYPE value)
        {
            std::string pr_name = name.getString();
            pr_name += "IsLessThan";
            if constexpr(Utils::NOPTraits::is_string_v<TYPE>)
                pr_name += value;
            else if constexpr( std::is_integral_v<TYPE> or std::is_floating_point_v<TYPE>)
                pr_name += std::to_string(value);
            else
                pr_name += "Value";

            auto premise = make_premise<Comparison::LESS>(this, value, pr_name);

            return *premise;
        }

        /**
         * Cria e retorna uma Premise do tipo less_equal (com valor constante)
         * 
         * @tparam TYPE 
         * @param value 
         * @return Premise<Attribute<TYPE>*, TYPE, Comparison::LESS_EQUAL>& 
         */
        template <class TYPE>
        Premise<Attribute<TYPE>*, TYPE, Comparison::LESS_EQUAL>& Attribute<TYPE>::operator<=(const TYPE value)
        {
            std::string pr_name = name.getString();
            pr_name += "IsLessOrEqual";
            if constexpr(Utils::NOPTraits::is_string_v<TYPE>)
                pr_name += value;
            else if constexpr( std::is_integral_v<TYPE> or std::is_floating_point_v<TYPE>)
                pr_name += std::to_string(value);
            else
                pr_name += "Value";
            
            auto premise = make_premise<Comparison::LESS_EQUAL>(this, value, pr_name);

            return *premise;
        }
    } // namespace Core
    
}

#endif // !JUNOCPP_ATTRIBUTE_HPP