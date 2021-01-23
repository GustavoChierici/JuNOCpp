#ifndef BETTER_ATTRIBUTE_HPP
#define BETTER_ATTRIBUTE_HPP

#include "Notifier.hpp"
#include "NOPManager.hpp"
#include "../Utils/NOPTraits/attribute_traits.hpp"
#include "../Utils/NOPTraits/premise_traits.hpp"

namespace JuNOCpp
{
    template <class PrT, typename RT, typename CmpOpT>
    class Premise;
    namespace Attributes
    {
        template<class TYPE>
        class BetterAttribute: public Notifier, public Notifiable
        {
        private:
            TYPE current_status;
            TYPE previous_status;

            TYPE (*updateOperation)(TYPE value1, TYPE value2);

            Utils::forward_list<shared_ptr<Notifiable>> _impertinents;

        public:
            BetterAttribute(CustomString name = "UnnamedAttribute");
            BetterAttribute(TYPE value, CustomString name = "UnnamedAttribute");
            BetterAttribute(const BetterAttribute& rhs);
            BetterAttribute(BetterAttribute&& rhs);
            ~BetterAttribute();

            TYPE getPreviousStatus();
            TYPE getCurrentStatus();

            void setStatus(TYPE value, bool renotify = false);

            void referenceBetterAttributeAbove(BetterAttribute<TYPE>* b_attr);

            void update(const bool renotify = false);
            void update(const bool renotify, const bool status) {}

            void addImpertinent(shared_ptr<Notifiable> impertinent)
            {
                _impertinents.push_back(impertinent);
            }

            // BetterAttribute<TYPE> operator+(BetterAttribute<TYPE>& b_attr);
            // BetterAttribute<TYPE> operator-(BetterAttribute<TYPE>& b_attr);
            // BetterAttribute<TYPE> operator*(BetterAttribute<TYPE>& b_attr);
            // BetterAttribute<TYPE> operator/(BetterAttribute<TYPE>& b_attr);

            //CoreAttribute<TYPE> operator=(BetterAttribute<TYPE>& b_attr);

            void operator=(TYPE value);

            Premise<TYPE, BetterAttribute<TYPE>*, Utils::NOPTraits::equal_t>& operator==(BetterAttribute<TYPE>& b_attr);
            Premise<TYPE, BetterAttribute<TYPE>*, Utils::NOPTraits::equal_t>& operator==(BetterAttribute<TYPE>&& b_attr);

            Premise<TYPE, BetterAttribute<TYPE>*, Utils::NOPTraits::not_equal_t>& operator!=(BetterAttribute<TYPE>& b_attr);
            Premise<TYPE, BetterAttribute<TYPE>*, Utils::NOPTraits::not_equal_t>& operator!=(BetterAttribute<TYPE>&& b_attr);

            Premise<TYPE, BetterAttribute<TYPE>*, Utils::NOPTraits::greater_t>& operator>(BetterAttribute<TYPE>& b_attr);
            Premise<TYPE, BetterAttribute<TYPE>*, Utils::NOPTraits::greater_t>& operator>(BetterAttribute<TYPE>&& b_attr);

            Premise<TYPE, BetterAttribute<TYPE>*, Utils::NOPTraits::greater_equal_t>& operator>=(BetterAttribute<TYPE>& b_attr);
            Premise<TYPE, BetterAttribute<TYPE>*, Utils::NOPTraits::greater_equal_t>& operator>=(BetterAttribute<TYPE>&& b_attr);

            Premise<TYPE, BetterAttribute<TYPE>*, Utils::NOPTraits::less_t>& operator<(BetterAttribute<TYPE>& b_attr);
            Premise<TYPE, BetterAttribute<TYPE>*, Utils::NOPTraits::less_t>& operator<(BetterAttribute<TYPE>&& b_attr);

            Premise<TYPE, BetterAttribute<TYPE>*, Utils::NOPTraits::less_equal_t>& operator<=(BetterAttribute<TYPE>& b_attr);
            Premise<TYPE, BetterAttribute<TYPE>*, Utils::NOPTraits::less_equal_t>& operator<=(BetterAttribute<TYPE>&& b_attr);

            Premise<TYPE, TYPE, Utils::NOPTraits::equal_t>& operator==(const TYPE value);
            Premise<TYPE, TYPE, Utils::NOPTraits::not_equal_t>& operator!=(const TYPE value);
            Premise<TYPE, TYPE, Utils::NOPTraits::greater_t>& operator>(const TYPE value);
            Premise<TYPE, TYPE, Utils::NOPTraits::greater_equal_t>& operator>=(const TYPE value);
            Premise<TYPE, TYPE, Utils::NOPTraits::less_t>& operator<(const TYPE value);
            Premise<TYPE, TYPE, Utils::NOPTraits::less_equal_t>& operator<=(const TYPE value);
        };

        /**
         * Constrututor
         * 
         * @tparam TYPE 
         */
        template<class TYPE>
        BetterAttribute<TYPE>::BetterAttribute(CustomString name):
        Notifiable(name)
        {
            this->updateOperation = nullptr;
        }

        /**
         * Construtor com valor inicial
         * 
         * @tparam TYPE 
         * @param value 
         */
        template<class TYPE>
        BetterAttribute<TYPE>::BetterAttribute(TYPE value, CustomString name):
        Notifiable(name)
        {
            this->current_status = value;
            this->previous_status = value;

            this->updateOperation = nullptr;
        }

        /**
         * @brief Construtor (copy constructor)
         * 
         * @tparam TYPE 
         * @param rhs 
         */
        template <class TYPE>
        BetterAttribute<TYPE>::BetterAttribute(const BetterAttribute<TYPE>& rhs):
        Notifiable{rhs.name},
        Notifier{rhs.notifiables},
        current_status{rhs.current_status},
        previous_status{rhs.previous_status},
        updateOperation{rhs.updateOperation}
        {
        }

        /**
         * @brief Construtor (move constructor)
         * 
         * @tparam TYPE 
         * @param rhs 
         */
        template <class TYPE>
        BetterAttribute<TYPE>::BetterAttribute(BetterAttribute&& rhs):
        Notifiable{rhs.name},
        Notifier{rhs.notifiables},
        current_status{rhs.current_status},
        previous_status{rhs.previous_status},
        updateOperation{rhs.updateOperation}
        {
        }

        /**
         * Destrutor
         * 
         * @tparam TYPE 
         */
        template<class TYPE>
        BetterAttribute<TYPE>::~BetterAttribute()
        {
        }

        /**
         * Getter do previous_status 
         * 
         * @tparam TYPE 
         * @return TYPE 
         */
        template<class TYPE>
        TYPE BetterAttribute<TYPE>::getPreviousStatus()
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
        TYPE BetterAttribute<TYPE>::getCurrentStatus()
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
        void BetterAttribute<TYPE>::setStatus(TYPE value, bool renotify)
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
        void BetterAttribute<TYPE>::update(bool renotify)
        {
            // this->current_status = this->updateOperation(this->current_status, value);
            std::cout << this << std::endl;
            std::cout << "Não era pra você estar aqui" << std::endl;
            // notify(renotify);
        }


        template <class TYPE>
        void BetterAttribute<TYPE>::referenceBetterAttributeAbove(BetterAttribute<TYPE>* b_attr)
        {
            // auto aux = std::make_shared<BetterAttribute<TYPE>>(b_attr);
            // this->insert(aux);
        }

        /**
         * Overload do operator = para chamar automaticamente o método setStatus
         * 
         * @tparam TYPE 
         * @param value 
         */
        template<class TYPE>
        void BetterAttribute<TYPE>::operator=(TYPE value)
        {
            this->setStatus(value);
        }

        /**
         * @brief Cria e retorna uma Premise do tipo equal
         * 
         * @tparam TYPE 
         * @param b_attr 
         * @return Premise<TYPE, BetterAttribute<TYPE>*, Utils::NOPTraits::equal_t>& 
         */
        template <class TYPE>
        Premise<TYPE, BetterAttribute<TYPE>*, Utils::NOPTraits::equal_t>& BetterAttribute<TYPE>::operator==(BetterAttribute<TYPE>& b_attr)
        {
            std::string pr_name = name.getString();
            pr_name += "Equals";
            pr_name += b_attr.name.getString(); 

            #ifdef USE_CUSTOM_SMART_PTRS
                shared_ptr<Premise<TYPE, BetterAttribute<TYPE>*, Utils::NOPTraits::equal_t>> premise
                    (new Premise<TYPE, BetterAttribute<TYPE>*, Utils::NOPTraits::equal_t>
                        (this, &b_attr, Utils::NOPTraits::equal, pr_name));
            #else
                shared_ptr<Premise<TYPE, BetterAttribute<TYPE>*, Utils::NOPTraits::equal_t>> premise = 
                    std::make_shared<Premise<TYPE, BetterAttribute<TYPE>*, Utils::NOPTraits::equal_t>>
                        (*new Premise<TYPE, BetterAttribute<TYPE>*, Utils::NOPTraits::equal_t>(this, &b_attr, Utils::NOPTraits::equal, pr_name));
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
         * @return Premise<TYPE, BetterAttribute<TYPE>*, Utils::NOPTraits::equal_t>&
         */
        template <class TYPE>
        Premise<TYPE, BetterAttribute<TYPE>*, Utils::NOPTraits::equal_t>& BetterAttribute<TYPE>::operator==(BetterAttribute<TYPE>&& b_attr)
        {
            std::string pr_name = name.getString();
            pr_name += "Equals";
            pr_name += b_attr.name.getString(); 

            #ifdef USE_CUSTOM_SMART_PTRS
                shared_ptr<Premise<TYPE, BetterAttribute<TYPE>*, Utils::NOPTraits::equal_t>> premise
                    (new Premise<TYPE, BetterAttribute<TYPE>*, Utils::NOPTraits::equal_t>
                        (this, &b_attr, Utils::NOPTraits::equal, pr_name));
            #else
                shared_ptr<Premise<TYPE, BetterAttribute<TYPE>*, Utils::NOPTraits::equal_t>> premise = 
                    std::make_shared<Premise<TYPE, BetterAttribute<TYPE>*, Utils::NOPTraits::equal_t>>
                        (*new Premise<TYPE, BetterAttribute<TYPE>*, Utils::NOPTraits::equal_t>(this, &b_attr, Utils::NOPTraits::equal, pr_name));
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
         * @return Premise<TYPE, BetterAttribute<TYPE>*, Utils::NOPTraits::not_equal_t>& 
         */
        template <class TYPE>
        Premise<TYPE, BetterAttribute<TYPE>*, Utils::NOPTraits::not_equal_t>& BetterAttribute<TYPE>::operator!=(BetterAttribute<TYPE>& b_attr)
        {
            std::string pr_name = name.getString();
            pr_name += "NotEqual";
            pr_name += b_attr.name.getString(); 

            #ifdef USE_CUSTOM_SMART_PTRS
                shared_ptr<Premise<TYPE, BetterAttribute<TYPE>*, Utils::NOPTraits::not_equal_t>> premise
                    (new Premise<TYPE, BetterAttribute<TYPE>*, Utils::NOPTraits::not_equal_t>
                        (this, &b_attr, Utils::NOPTraits::not_equal, pr_name));
            #else
                shared_ptr<Premise<TYPE, BetterAttribute<TYPE>*, Utils::NOPTraits::not_equal_t>> premise = 
                    std::make_shared<Premise<TYPE, BetterAttribute<TYPE>*, Utils::NOPTraits::not_equal_t>>
                        (*new Premise<TYPE, BetterAttribute<TYPE>*, Utils::NOPTraits::not_equal_t>(this, &b_attr, Utils::NOPTraits::not_equal, pr_name));
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
         * @return Premise<TYPE, BetterAttribute<TYPE>*, Utils::NOPTraits::not_equal_t>& 
         */
        template <class TYPE>
        Premise<TYPE, BetterAttribute<TYPE>*, Utils::NOPTraits::not_equal_t>& BetterAttribute<TYPE>::operator!=(BetterAttribute<TYPE>&& b_attr)
        {
            std::string pr_name = name.getString();
            pr_name += "NotEqual";
            pr_name += b_attr.name.getString(); 

            #ifdef USE_CUSTOM_SMART_PTRS
                shared_ptr<Premise<TYPE, BetterAttribute<TYPE>*, Utils::NOPTraits::not_equal_t>> premise
                    (new Premise<TYPE, BetterAttribute<TYPE>*, Utils::NOPTraits::not_equal_t>
                        (this, &b_attr, Utils::NOPTraits::not_equal, pr_name));
            #else
                shared_ptr<Premise<TYPE, BetterAttribute<TYPE>*, Utils::NOPTraits::not_equal_t>> premise = 
                    std::make_shared<Premise<TYPE, BetterAttribute<TYPE>*, Utils::NOPTraits::not_equal_t>>
                        (*new Premise<TYPE, BetterAttribute<TYPE>*, Utils::NOPTraits::not_equal_t>(this, &b_attr, Utils::NOPTraits::not_equal, pr_name));
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
         * @return Premise<TYPE, BetterAttribute<TYPE>*, Utils::NOPTraits::greater_t>& 
         */
        template <class TYPE>
        Premise<TYPE, BetterAttribute<TYPE>*, Utils::NOPTraits::greater_t>& BetterAttribute<TYPE>::operator>(BetterAttribute<TYPE>& b_attr)
        {
            std::string pr_name = name.getString();
            pr_name += "IsGreaterThan";
            pr_name += b_attr.name.getString(); 

            #ifdef USE_CUSTOM_SMART_PTRS
                shared_ptr<Premise<TYPE, BetterAttribute<TYPE>*, Utils::NOPTraits::greater_t>> premise
                    (new Premise<TYPE, BetterAttribute<TYPE>*, Utils::NOPTraits::greater_t>
                        (this, &b_attr, Utils::NOPTraits::greater, pr_name));
            #else
                shared_ptr<Premise<TYPE, BetterAttribute<TYPE>*, Utils::NOPTraits::greater_t>> premise = 
                    std::make_shared<Premise<TYPE, BetterAttribute<TYPE>*, Utils::NOPTraits::greater_t>>
                        (*new Premise<TYPE, BetterAttribute<TYPE>*, Utils::NOPTraits::greater_t>(this, &b_attr, Utils::NOPTraits::greater, pr_name));
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
         * @return Premise<TYPE, BetterAttribute<TYPE>*, Utils::NOPTraits::greater_t>& 
         */
        template <class TYPE>
        Premise<TYPE, BetterAttribute<TYPE>*, Utils::NOPTraits::greater_t>& BetterAttribute<TYPE>::operator>(BetterAttribute<TYPE>&& b_attr)
        {
            std::string pr_name = name.getString();
            pr_name += "IsGreaterThan";
            pr_name += b_attr.name.getString(); 

            #ifdef USE_CUSTOM_SMART_PTRS
                shared_ptr<Premise<TYPE, BetterAttribute<TYPE>*, Utils::NOPTraits::greater_t>> premise
                    (new Premise<TYPE, BetterAttribute<TYPE>*, Utils::NOPTraits::greater_t>
                        (this, &b_attr, Utils::NOPTraits::greater, pr_name));
            #else
                shared_ptr<Premise<TYPE, BetterAttribute<TYPE>*, Utils::NOPTraits::greater_t>> premise = 
                    std::make_shared<Premise<TYPE, BetterAttribute<TYPE>*, Utils::NOPTraits::greater_t>>
                        (*new Premise<TYPE, BetterAttribute<TYPE>*, Utils::NOPTraits::greater_t>(this, &b_attr, Utils::NOPTraits::greater, pr_name));
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
         * @return Premise<TYPE, BetterAttribute<TYPE>*, Utils::NOPTraits::greater_equal_t>& 
         */
        template <class TYPE>
        Premise<TYPE, BetterAttribute<TYPE>*, Utils::NOPTraits::greater_equal_t>& BetterAttribute<TYPE>::operator>=(BetterAttribute<TYPE>& b_attr)
        {
            std::string pr_name = name.getString();
            pr_name += "IsGreaterOrEqual";
            pr_name += b_attr.name.getString(); 

            #ifdef USE_CUSTOM_SMART_PTRS
                shared_ptr<Premise<TYPE, BetterAttribute<TYPE>*, Utils::NOPTraits::greater_equal_t>> premise
                    (new Premise<TYPE, BetterAttribute<TYPE>*, Utils::NOPTraits::greater_equal_t>
                        (this, &b_attr, Utils::NOPTraits::greater_equal, pr_name));
            #else
                shared_ptr<Premise<TYPE, BetterAttribute<TYPE>*, Utils::NOPTraits::greater_equal_t>> premise = 
                    std::make_shared<Premise<TYPE, BetterAttribute<TYPE>*, Utils::NOPTraits::greater_equal_t>>
                        (*new Premise<TYPE, BetterAttribute<TYPE>*, Utils::NOPTraits::greater_equal_t>(this, &b_attr, Utils::NOPTraits::greater_equal, pr_name));
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
         * @return Premise<TYPE, BetterAttribute<TYPE>*, Utils::NOPTraits::greater_equal_t>& 
         */
        template <class TYPE>
        Premise<TYPE, BetterAttribute<TYPE>*, Utils::NOPTraits::greater_equal_t>& BetterAttribute<TYPE>::operator>=(BetterAttribute<TYPE>&& b_attr)
        {
            std::string pr_name = name.getString();
            pr_name += "IsGreaterOrEqual";
            pr_name += b_attr.name.getString(); 

            #ifdef USE_CUSTOM_SMART_PTRS
                shared_ptr<Premise<TYPE, BetterAttribute<TYPE>*, Utils::NOPTraits::greater_equal_t>> premise
                    (new Premise<TYPE, BetterAttribute<TYPE>*, Utils::NOPTraits::greater_equal_t>
                        (this, &b_attr, Utils::NOPTraits::greater_equal, pr_name));
            #else
                shared_ptr<Premise<TYPE, BetterAttribute<TYPE>*, Utils::NOPTraits::greater_equal_t>> premise = 
                    std::make_shared<Premise<TYPE, BetterAttribute<TYPE>*, Utils::NOPTraits::greater_equal_t>>
                        (*new Premise<TYPE, BetterAttribute<TYPE>*, Utils::NOPTraits::greater_equal_t>(this, &b_attr, Utils::NOPTraits::greater_equal, pr_name));
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
         * @return Premise<TYPE, BetterAttribute<TYPE>*, Utils::NOPTraits::less_t>& 
         */
        template <class TYPE>
        Premise<TYPE, BetterAttribute<TYPE>*, Utils::NOPTraits::less_t>& BetterAttribute<TYPE>::operator<(BetterAttribute<TYPE>& b_attr)
        {
            std::string pr_name = name.getString();
            pr_name += "IsLessThan";
            pr_name += b_attr.name.getString(); 

            #ifdef USE_CUSTOM_SMART_PTRS
                shared_ptr<Premise<TYPE, BetterAttribute<TYPE>*, Utils::NOPTraits::less_t>> premise
                    (new Premise<TYPE, BetterAttribute<TYPE>*, Utils::NOPTraits::less_t>
                        (this, &b_attr, Utils::NOPTraits::less, pr_name));
            #else
                shared_ptr<Premise<TYPE, BetterAttribute<TYPE>*, Utils::NOPTraits::less_t>> premise = 
                    std::make_shared<Premise<TYPE, BetterAttribute<TYPE>*, Utils::NOPTraits::less_t>>
                        (*new Premise<TYPE, BetterAttribute<TYPE>*, Utils::NOPTraits::less_t>(this, &b_attr, Utils::NOPTraits::less, pr_name));
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
         * @return Premise<TYPE, BetterAttribute<TYPE>*, Utils::NOPTraits::less_t>& 
         */
        template <class TYPE>
        Premise<TYPE, BetterAttribute<TYPE>*, Utils::NOPTraits::less_t>& BetterAttribute<TYPE>::operator<(BetterAttribute<TYPE>&& b_attr)
        {
            std::string pr_name = name.getString();
            pr_name += "IsLessThan";
            pr_name += b_attr.name.getString(); 

            #ifdef USE_CUSTOM_SMART_PTRS
                shared_ptr<Premise<TYPE, BetterAttribute<TYPE>*, Utils::NOPTraits::less_t>> premise
                    (new Premise<TYPE, BetterAttribute<TYPE>*, Utils::NOPTraits::less_t>
                        (this, &b_attr, Utils::NOPTraits::less, pr_name));
            #else
                shared_ptr<Premise<TYPE, BetterAttribute<TYPE>*, Utils::NOPTraits::less_t>> premise = 
                    std::make_shared<Premise<TYPE, BetterAttribute<TYPE>*, Utils::NOPTraits::less_t>>
                        (*new Premise<TYPE, BetterAttribute<TYPE>*, Utils::NOPTraits::less_t>(this, &b_attr, Utils::NOPTraits::less, pr_name));
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
         * @return Premise<TYPE, BetterAttribute<TYPE>*, Utils::NOPTraits::less_equal_t>& 
         */
        template <class TYPE>
        Premise<TYPE, BetterAttribute<TYPE>*, Utils::NOPTraits::less_equal_t>& BetterAttribute<TYPE>::operator<=(BetterAttribute<TYPE>& b_attr)
        {
            std::string pr_name = name.getString();
            pr_name += "IsLessOrEqual";
            pr_name += b_attr.name.getString(); 

            #ifdef USE_CUSTOM_SMART_PTRS
                shared_ptr<Premise<TYPE, BetterAttribute<TYPE>*, Utils::NOPTraits::less_equal_t>> premise
                    (new Premise<TYPE, BetterAttribute<TYPE>*, Utils::NOPTraits::less_equal_t>
                        (this, &b_attr, Utils::NOPTraits::less_equal, pr_name));
            #else
                shared_ptr<Premise<TYPE, BetterAttribute<TYPE>*, Utils::NOPTraits::less_equal_t>> premise = 
                    std::make_shared<Premise<TYPE, BetterAttribute<TYPE>*, Utils::NOPTraits::less_equal_t>>
                        (*new Premise<TYPE, BetterAttribute<TYPE>*, Utils::NOPTraits::less_equal_t>(this, &b_attr, Utils::NOPTraits::less_equal, pr_name));
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
         * @return Premise<TYPE, BetterAttribute<TYPE>*, Utils::NOPTraits::less_equal_t>& 
         */
        template <class TYPE>
        Premise<TYPE, BetterAttribute<TYPE>*, Utils::NOPTraits::less_equal_t>& BetterAttribute<TYPE>::operator<=(BetterAttribute<TYPE>&& b_attr)
        {
            std::string pr_name = name.getString();
            pr_name += "IsLessOrEqual";
            pr_name += b_attr.name.getString(); 

            #ifdef USE_CUSTOM_SMART_PTRS
                shared_ptr<Premise<TYPE, BetterAttribute<TYPE>*, Utils::NOPTraits::less_equal_t>> premise
                    (new Premise<TYPE, BetterAttribute<TYPE>*, Utils::NOPTraits::less_equal_t>
                        (this, &b_attr, Utils::NOPTraits::less_equal, pr_name));
            #else
                shared_ptr<Premise<TYPE, BetterAttribute<TYPE>*, Utils::NOPTraits::less_equal_t>> premise = 
                    std::make_shared<Premise<TYPE, BetterAttribute<TYPE>*, Utils::NOPTraits::less_equal_t>>
                        (*new Premise<TYPE, BetterAttribute<TYPE>*, Utils::NOPTraits::less_equal_t>(this, &b_attr, Utils::NOPTraits::less_equal, pr_name));
            #endif // USE_CUSTOM_SMART_PTRS

            this->insert(premise);
            b_attr.insert(premise);

            return *premise;
        }

        // template <class TYPE>
        // BetterAttribute<TYPE> BetterAttribute<TYPE>::operator+(BetterAttribute<TYPE>& b_attr)
        // {
        //     BetterAttribute<TYPE> aux;

        //     this->referenceBetterAttributeAbove(&aux);
        //     b_attr.referenceBetterAttributeAbove(&aux);

        //     aux.updateOperation = [](TYPE value1, TYPE value2)
        //     {
        //         return value1 + value2;
        //     };

        //     aux.setStatus(this->current_status);
        //     aux.updateStatus(b_attr.current_status);

        //     return aux;
        // }

        // template <class TYPE>
        // BetterAttribute<TYPE> BetterAttribute<TYPE>::operator-(BetterAttribute<TYPE>& b_attr)
        // {
        //     BetterAttribute<TYPE> aux;

        //     this->referenceBetterAttributeAbove(&aux);
        //     b_attr.referenceBetterAttributeAbove(&aux);

        //     aux.updateOperation = [](TYPE value1, TYPE value2)
        //     {
        //         return value1 - value2;
        //     };

        //     aux.setStatus(this->current_status);
        //     aux.updateStatus(b_attr.current_status);

        //     return aux;
        // }

        // template <class TYPE>
        // BetterAttribute<TYPE> BetterAttribute<TYPE>::operator*(BetterAttribute<TYPE>& b_attr)
        // {
        //     BetterAttribute<TYPE> aux;

        //     this->referenceBetterAttributeAbove(&aux);
        //     b_attr.referenceBetterAttributeAbove(&aux);

        //     aux.updateOperation = [](TYPE value1, TYPE value2)
        //     {
        //         return value1 * value2;
        //     };

        //     aux.setStatus(this->current_status);
        //     aux.updateStatus(b_attr.current_status);

        //     return aux;
        // }
    
        /**
         * Cria e retorna uma Premise do tipo equal (com valor constante)
         * 
         * @tparam TYPE 
         * @param value 
         * @return Premise<TYPE, TYPE, Utils::NOPTraits::equal_t>& 
         */
        template <class TYPE>
        Premise<TYPE, TYPE, Utils::NOPTraits::equal_t>& BetterAttribute<TYPE>::operator==(const TYPE value)
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
        Premise<TYPE, TYPE, Utils::NOPTraits::not_equal_t>& BetterAttribute<TYPE>::operator!=(const TYPE value)
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
        Premise<TYPE, TYPE, Utils::NOPTraits::greater_t>& BetterAttribute<TYPE>::operator>(const TYPE value)
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
        Premise<TYPE, TYPE, Utils::NOPTraits::greater_equal_t>& BetterAttribute<TYPE>::operator>=(const TYPE value)
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
        Premise<TYPE, TYPE, Utils::NOPTraits::less_t>& BetterAttribute<TYPE>::operator<(const TYPE value)
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
        Premise<TYPE, TYPE, Utils::NOPTraits::less_equal_t>& BetterAttribute<TYPE>::operator<=(const TYPE value)
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
}

#endif