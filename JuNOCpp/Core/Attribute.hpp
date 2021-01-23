#ifndef JUNOCPP_ATTRIBUTE_HPP
#define JUNOCPP_ATTRIBUTE_HPP

#include "Notifier.hpp"
#include "NOPManager.hpp"
#include "../Utils/tuple_helper.hpp"
#include "../Utils/NOPTraits/premise_traits.hpp"
#include "../Utils/NOPTraits/attribute_traits.hpp"

namespace JuNOCpp
{
    template <class PrT, typename RT, typename CmpOpT>
    class Premise;
    template<class TYPE>
    class Attribute: public Notifier, public Notifiable
    {
    public:
        Attribute(Utils::CustomString name = "UnnamedAttribute");
        Attribute(TYPE value, Utils::CustomString name = "UnnamedAttribute");
        Attribute(const Attribute& rhs);
        Attribute(Attribute&& rhs);
        ~Attribute();

        TYPE getPreviousStatus();
        TYPE getCurrentStatus();

        void setStatus(TYPE value, bool renotify = false);

        void referenceAttributeAbove(Attribute<TYPE>* b_attr);

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

        Premise<TYPE, Attribute<TYPE>*, Utils::NOPTraits::equal_t>& operator==(Attribute<TYPE>& b_attr);
        Premise<TYPE, Attribute<TYPE>*, Utils::NOPTraits::equal_t>& operator==(Attribute<TYPE>&& b_attr);
        template<typename _Op, typename ...T>
        Premise<TYPE, std::tuple<T...>, Utils::NOPTraits::equal_t>& operator==(Utils::tuple_helper<_Op, T...> tup_h);

        Premise<TYPE, Attribute<TYPE>*, Utils::NOPTraits::not_equal_t>& operator!=(Attribute<TYPE>& b_attr);
        Premise<TYPE, Attribute<TYPE>*, Utils::NOPTraits::not_equal_t>& operator!=(Attribute<TYPE>&& b_attr);
        template<typename _Op, typename ...T>
        Premise<TYPE, std::tuple<T...>, Utils::NOPTraits::not_equal_t>& operator!=(Utils::tuple_helper<_Op, T...> tup_h);

        Premise<TYPE, Attribute<TYPE>*, Utils::NOPTraits::greater_t>& operator>(Attribute<TYPE>& b_attr);
        Premise<TYPE, Attribute<TYPE>*, Utils::NOPTraits::greater_t>& operator>(Attribute<TYPE>&& b_attr);
        template<typename _Op, typename ...T>
        Premise<TYPE, std::tuple<T...>, Utils::NOPTraits::greater_t>& operator>(Utils::tuple_helper<_Op, T...> tup_h);

        Premise<TYPE, Attribute<TYPE>*, Utils::NOPTraits::greater_equal_t>& operator>=(Attribute<TYPE>& b_attr);
        Premise<TYPE, Attribute<TYPE>*, Utils::NOPTraits::greater_equal_t>& operator>=(Attribute<TYPE>&& b_attr);
        template<typename _Op, typename ...T>
        Premise<TYPE, std::tuple<T...>, Utils::NOPTraits::greater_equal_t>& operator>=(Utils::tuple_helper<_Op, T...> tup_h);

        Premise<TYPE, Attribute<TYPE>*, Utils::NOPTraits::less_t>& operator<(Attribute<TYPE>& b_attr);
        Premise<TYPE, Attribute<TYPE>*, Utils::NOPTraits::less_t>& operator<(Attribute<TYPE>&& b_attr);
        template<typename _Op, typename ...T>
        Premise<TYPE, std::tuple<T...>, Utils::NOPTraits::less_t>& operator<(Utils::tuple_helper<_Op, T...> tup_h);

        Premise<TYPE, Attribute<TYPE>*, Utils::NOPTraits::less_equal_t>& operator<=(Attribute<TYPE>& b_attr);
        Premise<TYPE, Attribute<TYPE>*, Utils::NOPTraits::less_equal_t>& operator<=(Attribute<TYPE>&& b_attr);
        template<typename _Op, typename ...T>
        Premise<TYPE, std::tuple<T...>, Utils::NOPTraits::less_equal_t>& operator<=(Utils::tuple_helper<_Op, T...> tup_h);

        Premise<TYPE, TYPE, Utils::NOPTraits::equal_t>& operator==(const TYPE value);
        Premise<TYPE, TYPE, Utils::NOPTraits::not_equal_t>& operator!=(const TYPE value);
        Premise<TYPE, TYPE, Utils::NOPTraits::greater_t>& operator>(const TYPE value);
        Premise<TYPE, TYPE, Utils::NOPTraits::greater_equal_t>& operator>=(const TYPE value);
        Premise<TYPE, TYPE, Utils::NOPTraits::less_t>& operator<(const TYPE value);
        Premise<TYPE, TYPE, Utils::NOPTraits::less_equal_t>& operator<=(const TYPE value);
        
    private:
        TYPE current_status;
        TYPE previous_status;

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
    Notifiable(name)
    {
        this->current_status = value;
        this->previous_status = value;
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
    current_status{rhs.current_status},
    previous_status{rhs.previous_status}
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
    current_status{rhs.current_status},
    previous_status{rhs.previous_status}
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
     * Getter do previous_status 
     * 
     * @tparam TYPE 
     * @return TYPE 
     */
    template<class TYPE>
    TYPE Attribute<TYPE>::getPreviousStatus()
    {
        return this->previous_status;
    }

    /**
     * Getter do current_status
     * 
     * @tparam TYPE 
     * @return TYPE 
     */
    template<class TYPE>
    TYPE Attribute<TYPE>::getCurrentStatus()
    {
        return this->current_status;
    }

    /**
     * Provoca uma cadeia de notificações se o valor do Attribute for alterado ou se a flag renotify for true
     * 
     * @tparam TYPE 
     * @param value 
     * @param renotify == false
     */
    template<class TYPE>
    void Attribute<TYPE>::setStatus(TYPE value, bool renotify)
    {
        if(renotify || value != this->current_status)
        {
            #ifdef SHOW_NOP_LOGGER
                Utils::NOPLogger::Get().writeAssignment(name, this, value, renotify);
                Utils::NOPLogger::Get().writeNotifying(name, this, renotify);

                Utils::NOPLogger::Get().incrementIdentation();
            #endif // SHOW_NOP_LOGGER

            this->previous_status = this->current_status;
            this->current_status = value;

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
        // this->current_status = this->updateOperation(this->current_status, value);
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
            (Utils::NOPTraits::at_add_val<TYPE>, this, tup_h.tup), Utils::NOPTraits::at_add_val<TYPE>);
    }

    template <class TYPE>
    auto Attribute<TYPE>::operator+(TYPE value)
    {
        return Utils::make_tuple_h(std::make_tuple
            (Utils::NOPTraits::at_add_val<TYPE>, this, value), Utils::NOPTraits::at_add_val<TYPE>);
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
            (Utils::NOPTraits::at_sub_val<TYPE>, this, tup_h.tup), Utils::NOPTraits::at_sub_val<TYPE>);
    }

    template <class TYPE>
    auto Attribute<TYPE>::operator-(TYPE value)
    {
        return Utils::make_tuple_h(std::make_tuple
            (Utils::NOPTraits::at_sub_val<TYPE>, this, value), Utils::NOPTraits::at_sub_val<TYPE>);
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
            (Utils::NOPTraits::at_mult_val<TYPE>, this, tup_h.tup), Utils::NOPTraits::at_mult_val<TYPE>);
    }

    template <class TYPE>
    auto Attribute<TYPE>::operator*(TYPE value)
    {
        return Utils::make_tuple_h(std::make_tuple
            (Utils::NOPTraits::at_mult_val<TYPE>, this, value), Utils::NOPTraits::at_mult_val<TYPE>);
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
            (Utils::NOPTraits::at_div_val<TYPE>, this, tup_h.tup), Utils::NOPTraits::at_div_val<TYPE>);
    }

    template <class TYPE>
    auto Attribute<TYPE>::operator/(TYPE value)
    {
        return Utils::make_tuple_h(std::make_tuple
            (Utils::NOPTraits::at_div_val<TYPE>, this, value), Utils::NOPTraits::at_div_val<TYPE>);
    }

    /**
     * Overload do operator = para chamar automaticamente o método setStatus
     * 
     * @tparam TYPE 
     * @param value 
     */
    template<class TYPE>
    void Attribute<TYPE>::operator=(TYPE value)
    {
        setStatus(value);
    }

    /**
     * @brief Cria e retorna uma Premise do tipo equal
     * 
     * @tparam TYPE 
     * @param b_attr 
     * @return Premise<TYPE, Attribute<TYPE>*, Utils::NOPTraits::equal_t>& 
     */
    template <class TYPE>
    Premise<TYPE, Attribute<TYPE>*, Utils::NOPTraits::equal_t>& Attribute<TYPE>::operator==(Attribute<TYPE>& b_attr)
    {
        std::string pr_name = name.getString();
        pr_name += "Equals";
        pr_name += b_attr.name.getString(); 

        #ifdef USE_CUSTOM_SMART_PTRS
            shared_ptr<Premise<TYPE, Attribute<TYPE>*, Utils::NOPTraits::equal_t>> premise
                (new Premise<TYPE, Attribute<TYPE>*, Utils::NOPTraits::equal_t>
                    (this, &b_attr, Utils::NOPTraits::equal, pr_name));
        #else
            shared_ptr<Premise<TYPE, Attribute<TYPE>*, Utils::NOPTraits::equal_t>> premise = 
                std::make_shared<Premise<TYPE, Attribute<TYPE>*, Utils::NOPTraits::equal_t>>
                    (*new Premise<TYPE, Attribute<TYPE>*, Utils::NOPTraits::equal_t>(this, &b_attr, Utils::NOPTraits::equal, pr_name));
        #endif // USE_CUSTOM_SMART_PTRS

        this->insert(premise);
        b_attr.insert(premise);

        return *premise;
    }

    /**
     * @brief Cria e retorna uma Premise do tipo equal
     * 
     * @tparam TYPE 
     * @param b_attr 
     * @return Premise<TYPE, Attribute<TYPE>*, Utils::NOPTraits::equal_t>&
     */
    template <class TYPE>
    Premise<TYPE, Attribute<TYPE>*, Utils::NOPTraits::equal_t>& Attribute<TYPE>::operator==(Attribute<TYPE>&& b_attr)
    {
        std::string pr_name = name.getString();
        pr_name += "Equals";
        pr_name += b_attr.name.getString(); 

        #ifdef USE_CUSTOM_SMART_PTRS
            shared_ptr<Premise<TYPE, Attribute<TYPE>*, Utils::NOPTraits::equal_t>> premise
                (new Premise<TYPE, Attribute<TYPE>*, Utils::NOPTraits::equal_t>
                    (this, &b_attr, Utils::NOPTraits::equal, pr_name));
        #else
            shared_ptr<Premise<TYPE, Attribute<TYPE>*, Utils::NOPTraits::equal_t>> premise = 
                std::make_shared<Premise<TYPE, Attribute<TYPE>*, Utils::NOPTraits::equal_t>>
                    (*new Premise<TYPE, Attribute<TYPE>*, Utils::NOPTraits::equal_t>(this, &b_attr, Utils::NOPTraits::equal, pr_name));
        #endif // USE_CUSTOM_SMART_PTRS

        this->insert(premise);
        b_attr.insert(premise);

        return *premise;
    }

    /**
     * @brief Cria e retorna uma Premise do tipo equal (com um tupla de Attributes)
     * 
     * @tparam TYPE 
     * @tparam _Op 
     * @tparam T 
     * @param tup_h 
     * @return Premise<TYPE, std::tuple<T...>, Utils::NOPTraits::equal_t>& 
     */
    template <class TYPE>
    template<typename _Op, typename ...T>
    Premise<TYPE, std::tuple<T...>, Utils::NOPTraits::equal_t>& Attribute<TYPE>::operator==(Utils::tuple_helper<_Op, T...> tup_h)
    {
        std::string pr_name = name.getString();
        pr_name += "EqualsArgs";

        #ifdef USE_CUSTOM_SMART_PTRS
            shared_ptr<Premise<TYPE, std::tuple<T...>, Utils::NOPTraits::equal_t>> premise
                (new Premise<TYPE, std::tuple<T...>, Utils::NOPTraits::equal_t>
                    (this, tup_h.tup, Utils::NOPTraits::equal, pr_name));
        #else
            shared_ptr<Premise<TYPE, std::tuple<T...>, Utils::NOPTraits::equal_t>> premise = 
                std::make_shared<Premise<TYPE, std::tuple<T...>, Utils::NOPTraits::equal_t>>
                    (*new Premise<TYPE, std::tuple<T...>, Utils::NOPTraits::equal_t>(this, tup_h.tup, Utils::NOPTraits::equal, pr_name));
        #endif // USE_CUSTOM_SMART_PTRS

        this->insert(premise);
        Utils::NOPTraits::insertPremise(tup_h.tup, premise);

        return *premise;
    }

    /**
     * @brief Cria e retorna uma Premise do tipo not_equal
     * 
     * @tparam TYPE 
     * @param b_attr 
     * @return Premise<TYPE, Attribute<TYPE>*, Utils::NOPTraits::not_equal_t>& 
     */
    template <class TYPE>
    Premise<TYPE, Attribute<TYPE>*, Utils::NOPTraits::not_equal_t>& Attribute<TYPE>::operator!=(Attribute<TYPE>& b_attr)
    {
        std::string pr_name = name.getString();
        pr_name += "NotEqual";
        pr_name += b_attr.name.getString(); 

        #ifdef USE_CUSTOM_SMART_PTRS
            shared_ptr<Premise<TYPE, Attribute<TYPE>*, Utils::NOPTraits::not_equal_t>> premise
                (new Premise<TYPE, Attribute<TYPE>*, Utils::NOPTraits::not_equal_t>
                    (this, &b_attr, Utils::NOPTraits::not_equal, pr_name));
        #else
            shared_ptr<Premise<TYPE, Attribute<TYPE>*, Utils::NOPTraits::not_equal_t>> premise = 
                std::make_shared<Premise<TYPE, Attribute<TYPE>*, Utils::NOPTraits::not_equal_t>>
                    (*new Premise<TYPE, Attribute<TYPE>*, Utils::NOPTraits::not_equal_t>(this, &b_attr, Utils::NOPTraits::not_equal, pr_name));
        #endif // USE_CUSTOM_SMART_PTRS

        this->insert(premise);
        b_attr.insert(premise);

        return *premise;
    }

    /**
     * @brief Cria e retorna uma Premise do tipo not_equal
     * 
     * @tparam TYPE 
     * @param b_attr 
     * @return Premise<TYPE, Attribute<TYPE>*, Utils::NOPTraits::not_equal_t>& 
     */
    template <class TYPE>
    Premise<TYPE, Attribute<TYPE>*, Utils::NOPTraits::not_equal_t>& Attribute<TYPE>::operator!=(Attribute<TYPE>&& b_attr)
    {
        std::string pr_name = name.getString();
        pr_name += "NotEqual";
        pr_name += b_attr.name.getString(); 

        #ifdef USE_CUSTOM_SMART_PTRS
            shared_ptr<Premise<TYPE, Attribute<TYPE>*, Utils::NOPTraits::not_equal_t>> premise
                (new Premise<TYPE, Attribute<TYPE>*, Utils::NOPTraits::not_equal_t>
                    (this, &b_attr, Utils::NOPTraits::not_equal, pr_name));
        #else
            shared_ptr<Premise<TYPE, Attribute<TYPE>*, Utils::NOPTraits::not_equal_t>> premise = 
                std::make_shared<Premise<TYPE, Attribute<TYPE>*, Utils::NOPTraits::not_equal_t>>
                    (*new Premise<TYPE, Attribute<TYPE>*, Utils::NOPTraits::not_equal_t>(this, &b_attr, Utils::NOPTraits::not_equal, pr_name));
        #endif // USE_CUSTOM_SMART_PTRS

        this->insert(premise);
        b_attr.insert(premise);

        return *premise;
    }

    /**
     * @brief Cria e retorna uma Premise do tipo not_equal (com um tupla de Attributes)
     * 
     * @tparam TYPE 
     * @tparam _Op 
     * @tparam T 
     * @param tup_h 
     * @return Premise<TYPE, std::tuple<T...>, Utils::NOPTraits::not_equal_t>& 
     */
    template <class TYPE>
    template<typename _Op, typename ...T>
    Premise<TYPE, std::tuple<T...>, Utils::NOPTraits::not_equal_t>& Attribute<TYPE>::operator!=(Utils::tuple_helper<_Op, T...> tup_h)
    {
        std::string pr_name = name.getString();
        pr_name += "EqualsArgs";

        #ifdef USE_CUSTOM_SMART_PTRS
            shared_ptr<Premise<TYPE, std::tuple<T...>, Utils::NOPTraits::not_equal_t>> premise
                (new Premise<TYPE, std::tuple<T...>, Utils::NOPTraits::not_equal_t>
                    (this, tup_h.tup, Utils::NOPTraits::not_equal, pr_name));
        #else
            shared_ptr<Premise<TYPE, std::tuple<T...>, Utils::NOPTraits::not_equal_t>> premise = 
                std::make_shared<Premise<TYPE, std::tuple<T...>, Utils::NOPTraits::not_equal_t>>
                    (*new Premise<TYPE, std::tuple<T...>, Utils::NOPTraits::not_equal_t>(this, tup_h.tup, Utils::NOPTraits::not_equal, pr_name));
        #endif // USE_CUSTOM_SMART_PTRS

        this->insert(premise);
        Utils::NOPTraits::insertPremise(tup_h.tup, premise);

        return *premise;
    }

    /**
     * @brief Cria e retorna uma Premise do tipo greater
     * 
     * @tparam TYPE 
     * @param b_attr 
     * @return Premise<TYPE, Attribute<TYPE>*, Utils::NOPTraits::greater_t>& 
     */
    template <class TYPE>
    Premise<TYPE, Attribute<TYPE>*, Utils::NOPTraits::greater_t>& Attribute<TYPE>::operator>(Attribute<TYPE>& b_attr)
    {
        std::string pr_name = name.getString();
        pr_name += "IsGreaterThan";
        pr_name += b_attr.name.getString(); 

        #ifdef USE_CUSTOM_SMART_PTRS
            shared_ptr<Premise<TYPE, Attribute<TYPE>*, Utils::NOPTraits::greater_t>> premise
                (new Premise<TYPE, Attribute<TYPE>*, Utils::NOPTraits::greater_t>
                    (this, &b_attr, Utils::NOPTraits::greater, pr_name));
        #else
            shared_ptr<Premise<TYPE, Attribute<TYPE>*, Utils::NOPTraits::greater_t>> premise = 
                std::make_shared<Premise<TYPE, Attribute<TYPE>*, Utils::NOPTraits::greater_t>>
                    (*new Premise<TYPE, Attribute<TYPE>*, Utils::NOPTraits::greater_t>(this, &b_attr, Utils::NOPTraits::greater, pr_name));
        #endif // USE_CUSTOM_SMART_PTRS

        this->insert(premise);
        b_attr.insert(premise);

        return *premise;
    }

    /**
     * @brief Cria e retorna uma Premise do tipo greater
     * 
     * @tparam TYPE 
     * @param b_attr 
     * @return Premise<TYPE, Attribute<TYPE>*, Utils::NOPTraits::greater_t>& 
     */
    template <class TYPE>
    Premise<TYPE, Attribute<TYPE>*, Utils::NOPTraits::greater_t>& Attribute<TYPE>::operator>(Attribute<TYPE>&& b_attr)
    {
        std::string pr_name = name.getString();
        pr_name += "IsGreaterThan";
        pr_name += b_attr.name.getString(); 

        #ifdef USE_CUSTOM_SMART_PTRS
            shared_ptr<Premise<TYPE, Attribute<TYPE>*, Utils::NOPTraits::greater_t>> premise
                (new Premise<TYPE, Attribute<TYPE>*, Utils::NOPTraits::greater_t>
                    (this, &b_attr, Utils::NOPTraits::greater, pr_name));
        #else
            shared_ptr<Premise<TYPE, Attribute<TYPE>*, Utils::NOPTraits::greater_t>> premise = 
                std::make_shared<Premise<TYPE, Attribute<TYPE>*, Utils::NOPTraits::greater_t>>
                    (*new Premise<TYPE, Attribute<TYPE>*, Utils::NOPTraits::greater_t>(this, &b_attr, Utils::NOPTraits::greater, pr_name));
        #endif // USE_CUSTOM_SMART_PTRS

        this->insert(premise);
        b_attr.insert(premise);

        return *premise;
    }

    /**
     * @brief Cria e retorna uma Premise do tipo greater (com um tupla de Attributes)
     * 
     * @tparam TYPE 
     * @tparam _Op 
     * @tparam T 
     * @param tup_h 
     * @return Premise<TYPE, std::tuple<T...>, Utils::NOPTraits::greater_t>& 
     */
    template <class TYPE>
    template<typename _Op, typename ...T>
    Premise<TYPE, std::tuple<T...>, Utils::NOPTraits::greater_t>& Attribute<TYPE>::operator>(Utils::tuple_helper<_Op, T...> tup_h)
    {
        std::string pr_name = name.getString();
        pr_name += "EqualsArgs";

        #ifdef USE_CUSTOM_SMART_PTRS
            shared_ptr<Premise<TYPE, std::tuple<T...>, Utils::NOPTraits::greater_t>> premise
                (new Premise<TYPE, std::tuple<T...>, Utils::NOPTraits::greater_t>
                    (this, tup_h.tup, Utils::NOPTraits::greater, pr_name));
        #else
            shared_ptr<Premise<TYPE, std::tuple<T...>, Utils::NOPTraits::greater_t>> premise = 
                std::make_shared<Premise<TYPE, std::tuple<T...>, Utils::NOPTraits::greater_t>>
                    (*new Premise<TYPE, std::tuple<T...>, Utils::NOPTraits::greater_t>(this, tup_h.tup, Utils::NOPTraits::greater, pr_name));
        #endif // USE_CUSTOM_SMART_PTRS

        this->insert(premise);
        Utils::NOPTraits::insertPremise(tup_h.tup, premise);

        return *premise;
    }

    /**
     * @brief Cria e retorna uma Premise do tipo greater_equal
     * 
     * @tparam TYPE 
     * @param b_attr 
     * @return Premise<TYPE, Attribute<TYPE>*, Utils::NOPTraits::greater_equal_t>& 
     */
    template <class TYPE>
    Premise<TYPE, Attribute<TYPE>*, Utils::NOPTraits::greater_equal_t>& Attribute<TYPE>::operator>=(Attribute<TYPE>& b_attr)
    {
        std::string pr_name = name.getString();
        pr_name += "IsGreaterOrEqual";
        pr_name += b_attr.name.getString(); 

        #ifdef USE_CUSTOM_SMART_PTRS
            shared_ptr<Premise<TYPE, Attribute<TYPE>*, Utils::NOPTraits::greater_equal_t>> premise
                (new Premise<TYPE, Attribute<TYPE>*, Utils::NOPTraits::greater_equal_t>
                    (this, &b_attr, Utils::NOPTraits::greater_equal, pr_name));
        #else
            shared_ptr<Premise<TYPE, Attribute<TYPE>*, Utils::NOPTraits::greater_equal_t>> premise = 
                std::make_shared<Premise<TYPE, Attribute<TYPE>*, Utils::NOPTraits::greater_equal_t>>
                    (*new Premise<TYPE, Attribute<TYPE>*, Utils::NOPTraits::greater_equal_t>(this, &b_attr, Utils::NOPTraits::greater_equal, pr_name));
        #endif // USE_CUSTOM_SMART_PTRS

        this->insert(premise);
        b_attr.insert(premise);

        return *premise;
    }

    /**
     * @brief Cria e retorna uma Premise do tipo greater_equal
     * 
     * @tparam TYPE 
     * @param b_attr 
     * @return Premise<TYPE, Attribute<TYPE>*, Utils::NOPTraits::greater_equal_t>& 
     */
    template <class TYPE>
    Premise<TYPE, Attribute<TYPE>*, Utils::NOPTraits::greater_equal_t>& Attribute<TYPE>::operator>=(Attribute<TYPE>&& b_attr)
    {
        std::string pr_name = name.getString();
        pr_name += "IsGreaterOrEqual";
        pr_name += b_attr.name.getString(); 

        #ifdef USE_CUSTOM_SMART_PTRS
            shared_ptr<Premise<TYPE, Attribute<TYPE>*, Utils::NOPTraits::greater_equal_t>> premise
                (new Premise<TYPE, Attribute<TYPE>*, Utils::NOPTraits::greater_equal_t>
                    (this, &b_attr, Utils::NOPTraits::greater_equal, pr_name));
        #else
            shared_ptr<Premise<TYPE, Attribute<TYPE>*, Utils::NOPTraits::greater_equal_t>> premise = 
                std::make_shared<Premise<TYPE, Attribute<TYPE>*, Utils::NOPTraits::greater_equal_t>>
                    (*new Premise<TYPE, Attribute<TYPE>*, Utils::NOPTraits::greater_equal_t>(this, &b_attr, Utils::NOPTraits::greater_equal, pr_name));
        #endif // USE_CUSTOM_SMART_PTRS

        this->insert(premise);
        b_attr.insert(premise);

        return *premise;
    }

    /**
     * @brief Cria e retorna uma Premise do tipo greater_equal (com um tupla de Attributes)
     * 
     * @tparam TYPE 
     * @tparam _Op 
     * @tparam T 
     * @param tup_h 
     * @return Premise<TYPE, std::tuple<T...>, Utils::NOPTraits::greater_equal_t>& 
     */
    template <class TYPE>
    template<typename _Op, typename ...T>
    Premise<TYPE, std::tuple<T...>, Utils::NOPTraits::greater_equal_t>& Attribute<TYPE>::operator>=(Utils::tuple_helper<_Op, T...> tup_h)
    {
        std::string pr_name = name.getString();
        pr_name += "EqualsArgs";

        #ifdef USE_CUSTOM_SMART_PTRS
            shared_ptr<Premise<TYPE, std::tuple<T...>, Utils::NOPTraits::greater_equal_t>> premise
                (new Premise<TYPE, std::tuple<T...>, Utils::NOPTraits::greater_equal_t>
                    (this, tup_h.tup, Utils::NOPTraits::greater_equal, pr_name));
        #else
            shared_ptr<Premise<TYPE, std::tuple<T...>, Utils::NOPTraits::greater_equal_t>> premise = 
                std::make_shared<Premise<TYPE, std::tuple<T...>, Utils::NOPTraits::greater_equal_t>>
                    (*new Premise<TYPE, std::tuple<T...>, Utils::NOPTraits::greater_equal_t>(this, tup_h.tup, Utils::NOPTraits::greater_equal, pr_name));
        #endif // USE_CUSTOM_SMART_PTRS

        this->insert(premise);
        Utils::NOPTraits::insertPremise(tup_h.tup, premise);

        return *premise;
    }

    /**
     * @brief Cria e retorna uma Premise do tipo less
     * 
     * @tparam TYPE 
     * @param b_attr 
     * @return Premise<TYPE, Attribute<TYPE>*, Utils::NOPTraits::less_t>& 
     */
    template <class TYPE>
    Premise<TYPE, Attribute<TYPE>*, Utils::NOPTraits::less_t>& Attribute<TYPE>::operator<(Attribute<TYPE>& b_attr)
    {
        std::string pr_name = name.getString();
        pr_name += "IsLessThan";
        pr_name += b_attr.name.getString(); 

        #ifdef USE_CUSTOM_SMART_PTRS
            shared_ptr<Premise<TYPE, Attribute<TYPE>*, Utils::NOPTraits::less_t>> premise
                (new Premise<TYPE, Attribute<TYPE>*, Utils::NOPTraits::less_t>
                    (this, &b_attr, Utils::NOPTraits::less, pr_name));
        #else
            shared_ptr<Premise<TYPE, Attribute<TYPE>*, Utils::NOPTraits::less_t>> premise = 
                std::make_shared<Premise<TYPE, Attribute<TYPE>*, Utils::NOPTraits::less_t>>
                    (*new Premise<TYPE, Attribute<TYPE>*, Utils::NOPTraits::less_t>(this, &b_attr, Utils::NOPTraits::less, pr_name));
        #endif // USE_CUSTOM_SMART_PTRS

        this->insert(premise);
        b_attr.insert(premise);

        return *premise;
    }

    /**
     * @brief Cria e retorna uma Premise do tipo less
     * 
     * @tparam TYPE 
     * @param b_attr 
     * @return Premise<TYPE, Attribute<TYPE>*, Utils::NOPTraits::less_t>& 
     */
    template <class TYPE>
    Premise<TYPE, Attribute<TYPE>*, Utils::NOPTraits::less_t>& Attribute<TYPE>::operator<(Attribute<TYPE>&& b_attr)
    {
        std::string pr_name = name.getString();
        pr_name += "IsLessThan";
        pr_name += b_attr.name.getString(); 

        #ifdef USE_CUSTOM_SMART_PTRS
            shared_ptr<Premise<TYPE, Attribute<TYPE>*, Utils::NOPTraits::less_t>> premise
                (new Premise<TYPE, Attribute<TYPE>*, Utils::NOPTraits::less_t>
                    (this, &b_attr, Utils::NOPTraits::less, pr_name));
        #else
            shared_ptr<Premise<TYPE, Attribute<TYPE>*, Utils::NOPTraits::less_t>> premise = 
                std::make_shared<Premise<TYPE, Attribute<TYPE>*, Utils::NOPTraits::less_t>>
                    (*new Premise<TYPE, Attribute<TYPE>*, Utils::NOPTraits::less_t>(this, &b_attr, Utils::NOPTraits::less, pr_name));
        #endif // USE_CUSTOM_SMART_PTRS

        this->insert(premise);
        b_attr.insert(premise);

        return *premise;
    }

    /**
     * @brief Cria e retorna uma Premise do tipo less (com um tupla de Attributes)
     * 
     * @tparam TYPE 
     * @tparam _Op 
     * @tparam T 
     * @param tup_h 
     * @return Premise<TYPE, std::tuple<T...>, Utils::NOPTraits::less_t>& 
     */
    template <class TYPE>
    template<typename _Op, typename ...T>
    Premise<TYPE, std::tuple<T...>, Utils::NOPTraits::less_t>& Attribute<TYPE>::operator<(Utils::tuple_helper<_Op, T...> tup_h)
    {
        std::string pr_name = name.getString();
        pr_name += "EqualsArgs";

        #ifdef USE_CUSTOM_SMART_PTRS
            shared_ptr<Premise<TYPE, std::tuple<T...>, Utils::NOPTraits::less_t>> premise
                (new Premise<TYPE, std::tuple<T...>, Utils::NOPTraits::less_t>
                    (this, tup_h.tup, Utils::NOPTraits::less, pr_name));
        #else
            shared_ptr<Premise<TYPE, std::tuple<T...>, Utils::NOPTraits::less_t>> premise = 
                std::make_shared<Premise<TYPE, std::tuple<T...>, Utils::NOPTraits::less_t>>
                    (*new Premise<TYPE, std::tuple<T...>, Utils::NOPTraits::less_t>(this, tup_h.tup, Utils::NOPTraits::less, pr_name));
        #endif // USE_CUSTOM_SMART_PTRS

        this->insert(premise);
        Utils::NOPTraits::insertPremise(tup_h.tup, premise);

        return *premise;
    }

    /**
     * @brief Cria e retorna uma Premise do tipo less_equal
     * 
     * @tparam TYPE 
     * @param b_attr 
     * @return Premise<TYPE, Attribute<TYPE>*, Utils::NOPTraits::less_equal_t>& 
     */
    template <class TYPE>
    Premise<TYPE, Attribute<TYPE>*, Utils::NOPTraits::less_equal_t>& Attribute<TYPE>::operator<=(Attribute<TYPE>& b_attr)
    {
        std::string pr_name = name.getString();
        pr_name += "IsLessOrEqual";
        pr_name += b_attr.name.getString(); 

        #ifdef USE_CUSTOM_SMART_PTRS
            shared_ptr<Premise<TYPE, Attribute<TYPE>*, Utils::NOPTraits::less_equal_t>> premise
                (new Premise<TYPE, Attribute<TYPE>*, Utils::NOPTraits::less_equal_t>
                    (this, &b_attr, Utils::NOPTraits::less_equal, pr_name));
        #else
            shared_ptr<Premise<TYPE, Attribute<TYPE>*, Utils::NOPTraits::less_equal_t>> premise = 
                std::make_shared<Premise<TYPE, Attribute<TYPE>*, Utils::NOPTraits::less_equal_t>>
                    (*new Premise<TYPE, Attribute<TYPE>*, Utils::NOPTraits::less_equal_t>(this, &b_attr, Utils::NOPTraits::less_equal, pr_name));
        #endif // USE_CUSTOM_SMART_PTRS

        this->insert(premise);
        b_attr.insert(premise);

        return *premise;
    }

    /**
     * @brief Cria e retorna uma Premise do tipo less_equal
     * 
     * @tparam TYPE 
     * @param b_attr 
     * @return Premise<TYPE, Attribute<TYPE>*, Utils::NOPTraits::less_equal_t>& 
     */
    template <class TYPE>
    Premise<TYPE, Attribute<TYPE>*, Utils::NOPTraits::less_equal_t>& Attribute<TYPE>::operator<=(Attribute<TYPE>&& b_attr)
    {
        std::string pr_name = name.getString();
        pr_name += "IsLessOrEqual";
        pr_name += b_attr.name.getString(); 

        #ifdef USE_CUSTOM_SMART_PTRS
            shared_ptr<Premise<TYPE, Attribute<TYPE>*, Utils::NOPTraits::less_equal_t>> premise
                (new Premise<TYPE, Attribute<TYPE>*, Utils::NOPTraits::less_equal_t>
                    (this, &b_attr, Utils::NOPTraits::less_equal, pr_name));
        #else
            shared_ptr<Premise<TYPE, Attribute<TYPE>*, Utils::NOPTraits::less_equal_t>> premise = 
                std::make_shared<Premise<TYPE, Attribute<TYPE>*, Utils::NOPTraits::less_equal_t>>
                    (*new Premise<TYPE, Attribute<TYPE>*, Utils::NOPTraits::less_equal_t>(this, &b_attr, Utils::NOPTraits::less_equal, pr_name));
        #endif // USE_CUSTOM_SMART_PTRS

        this->insert(premise);
        b_attr.insert(premise);

        return *premise;
    }

    /**
     * @brief Cria e retorna uma Premise do tipo less_equal (com um tupla de Attributes)
     * 
     * @tparam TYPE 
     * @tparam _Op 
     * @tparam T 
     * @param tup_h 
     * @return Premise<TYPE, std::tuple<T...>, Utils::NOPTraits::less_equal_t>& 
     */
    template <class TYPE>
    template<typename _Op, typename ...T>
    Premise<TYPE, std::tuple<T...>, Utils::NOPTraits::less_equal_t>& Attribute<TYPE>::operator<=(Utils::tuple_helper<_Op, T...> tup_h)
    {
        std::string pr_name = name.getString();
        pr_name += "EqualsArgs";

        #ifdef USE_CUSTOM_SMART_PTRS
            shared_ptr<Premise<TYPE, std::tuple<T...>, Utils::NOPTraits::less_equal_t>> premise
                (new Premise<TYPE, std::tuple<T...>, Utils::NOPTraits::less_equal_t>
                    (this, tup_h.tup, Utils::NOPTraits::less_equal, pr_name));
        #else
            shared_ptr<Premise<TYPE, std::tuple<T...>, Utils::NOPTraits::less_equal_t>> premise = 
                std::make_shared<Premise<TYPE, std::tuple<T...>, Utils::NOPTraits::less_equal_t>>
                    (*new Premise<TYPE, std::tuple<T...>, Utils::NOPTraits::less_equal_t>(this, tup_h.tup, Utils::NOPTraits::less_equal, pr_name));
        #endif // USE_CUSTOM_SMART_PTRS

        this->insert(premise);
        Utils::NOPTraits::insertPremise(tup_h.tup, premise);

        return *premise;
    }

    /**
     * Cria e retorna uma Premise do tipo equal (com valor constante)
     * 
     * @tparam TYPE 
     * @param value 
     * @return Premise<TYPE, TYPE, Utils::NOPTraits::equal_t>& 
     */
    template <class TYPE>
    Premise<TYPE, TYPE, Utils::NOPTraits::equal_t>& Attribute<TYPE>::operator==(const TYPE value)
    {
        std::string pr_name = name.getString();
        pr_name += "Equals";
        pr_name += std::to_string(value);
        #ifdef USE_CUSTOM_SMART_PTRS
            shared_ptr<Premise<TYPE, TYPE, Utils::NOPTraits::equal_t>> premise
                (new Premise<TYPE, TYPE, Utils::NOPTraits::equal_t>(this, value, Utils::NOPTraits::equal, pr_name));
        #else
            shared_ptr<Premise<TYPE, TYPE, Utils::NOPTraits::equal_t>> premise = 
                std::make_shared<Premise<TYPE, TYPE, Utils::NOPTraits::equal_t>>
                    (*new Premise<TYPE, TYPE, Utils::NOPTraits::equal_t>(this, value, Utils::NOPTraits::equal, pr_name));
        #endif // USE_CUSTOM_SMART_PTRS

        this->insert(premise);

        return *premise;
    }

    /**
     * Cria e retorna uma Premise do tipo not_equal (com valor constante)
     * 
     * @tparam TYPE 
     * @param value 
     * @return Premise<TYPE, TYPE, Utils::NOPTraits::not_equal_t>& 
     */
    template <class TYPE>
    Premise<TYPE, TYPE, Utils::NOPTraits::not_equal_t>& Attribute<TYPE>::operator!=(const TYPE value)
    {
        std::string pr_name = name.getString();
        pr_name += "NotEqual";
        pr_name += std::to_string(value);
        #ifdef USE_CUSTOM_SMART_PTRS
            shared_ptr<Premise<TYPE, TYPE, Utils::NOPTraits::not_equal_t>> premise
                (new Premise<TYPE, TYPE, Utils::NOPTraits::not_equal_t>(this, value, Utils::NOPTraits::not_equal, pr_name));
        #else
            shared_ptr<Premise<TYPE, TYPE, Utils::NOPTraits::not_equal_t>> premise = 
                std::make_shared<Premise<TYPE, TYPE, Utils::NOPTraits::not_equal_t>>
                    (*new Premise<TYPE, TYPE, Utils::NOPTraits::not_equal_t>(this, value, Utils::NOPTraits::not_equal, pr_name));
        #endif // USE_CUSTOM_SMART_PTRS

        this->insert(premise);

        return *premise;
    }

    /**
     * Cria e retorna uma Premise do tipo greater (com valor constante)
     * 
     * @tparam TYPE 
     * @param value 
     * @return Premise<TYPE, TYPE, Utils::NOPTraits::greater_t>& 
     */
    template <class TYPE>
    Premise<TYPE, TYPE, Utils::NOPTraits::greater_t>& Attribute<TYPE>::operator>(const TYPE value)
    {
        std::string pr_name = name.getString();
        pr_name += "IsGreaterThan";
        pr_name += std::to_string(value);
        #ifdef USE_CUSTOM_SMART_PTRS
            shared_ptr<Premise<TYPE, TYPE, Utils::NOPTraits::greater_t>> premise
                (new Premise<TYPE, TYPE, Utils::NOPTraits::greater_t>(this, value, Utils::NOPTraits::greater, pr_name));
        #else
            shared_ptr<Premise<TYPE, TYPE, Utils::NOPTraits::greater_t>> premise = 
                std::make_shared<Premise<TYPE, TYPE, Utils::NOPTraits::greater_t>>
                    (*new Premise<TYPE, TYPE, Utils::NOPTraits::greater_t>(this, value, Utils::NOPTraits::greater, pr_name));
        #endif // USE_CUSTOM_SMART_PTRS

        this->insert(premise);

        return *premise;
    }

    /**
     * Cria e retorna uma Premise do tipo greater_equal (com valor constante)
     * 
     * @tparam TYPE 
     * @param value 
     * @return Premise<TYPE, TYPE, Utils::NOPTraits::greater_equal_t>& 
     */
    template <class TYPE>
    Premise<TYPE, TYPE, Utils::NOPTraits::greater_equal_t>& Attribute<TYPE>::operator>=(const TYPE value)
    {
        std::string pr_name = name.getString();
        pr_name += "IsGreaterOrEqual";
        pr_name += std::to_string(value);
        #ifdef USE_CUSTOM_SMART_PTRS
            shared_ptr<Premise<TYPE, TYPE, Utils::NOPTraits::greater_equal_t>> premise
                (new Premise<TYPE, TYPE, Utils::NOPTraits::greater_equal_t>(this, value, Utils::NOPTraits::greater_equal, pr_name));
        #else
            shared_ptr<Premise<TYPE, TYPE, Utils::NOPTraits::greater_equal_t>> premise = 
                std::make_shared<Premise<TYPE, TYPE, Utils::NOPTraits::greater_equal_t>>
                    (*new Premise<TYPE, TYPE, Utils::NOPTraits::greater_equal_t>(this, value, Utils::NOPTraits::greater_equal, pr_name));
        #endif // USE_CUSTOM_SMART_PTRS

        this->insert(premise);

        return *premise;
    }

    /**
     * Cria e retorna uma Premise do tipo less (com valor constante)
     * 
     * @tparam TYPE 
     * @param value 
     * @return Premise<TYPE, TYPE, Utils::NOPTraits::less_t>& 
     */
    template <class TYPE>
    Premise<TYPE, TYPE, Utils::NOPTraits::less_t>& Attribute<TYPE>::operator<(const TYPE value)
    {
        std::string pr_name = name.getString();
        pr_name += "IsLessThan";
        pr_name += std::to_string(value);
        #ifdef USE_CUSTOM_SMART_PTRS
            shared_ptr<Premise<TYPE, TYPE, Utils::NOPTraits::less_t>> premise
                (new Premise<TYPE, TYPE, Utils::NOPTraits::less_t>(this, value, Utils::NOPTraits::less, pr_name));
        #else
            shared_ptr<Premise<TYPE, TYPE, Utils::NOPTraits::less_t>> premise = 
                std::make_shared<Premise<TYPE, TYPE, Utils::NOPTraits::less_t>>
                    (*new Premise<TYPE, TYPE, Utils::NOPTraits::less_t>(this, value, Utils::NOPTraits::less, pr_name));
        #endif // USE_CUSTOM_SMART_PTRS

        this->insert(premise);

        return *premise;
    }

    /**
     * Cria e retorna uma Premise do tipo less_equal (com valor constante)
     * 
     * @tparam TYPE 
     * @param value 
     * @return Premise<TYPE, TYPE, Utils::NOPTraits::less_equal_t>& 
     */
    template <class TYPE>
    Premise<TYPE, TYPE, Utils::NOPTraits::less_equal_t>& Attribute<TYPE>::operator<=(const TYPE value)
    {
        std::string pr_name = name.getString();
        pr_name += "IsLessOrEqual";
        pr_name += std::to_string(value);
        #ifdef USE_CUSTOM_SMART_PTRS
            shared_ptr<Premise<TYPE, TYPE, Utils::NOPTraits::less_equal_t>> premise
                (new Premise<TYPE, TYPE, Utils::NOPTraits::less_equal_t>(this, value, Utils::NOPTraits::less_equal, pr_name));
        #else
            shared_ptr<Premise<TYPE, TYPE, Utils::NOPTraits::less_equal_t>> premise = 
                std::make_shared<Premise<TYPE, TYPE, Utils::NOPTraits::less_equal_t>>
                    (*new Premise<TYPE, TYPE, Utils::NOPTraits::less_equal_t>(this, value, Utils::NOPTraits::less_equal, pr_name));
        #endif // USE_CUSTOM_SMART_PTRS

        this->insert(premise);

        return *premise;
    }
}

#endif // !JUNOCPP_ATTRIBUTE_HPP