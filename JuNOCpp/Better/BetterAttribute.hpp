#ifndef BETTER_ATTRIBUTE_HPP
#define BETTER_ATTRIBUTE_HPP

#include "Notifier.hpp"
#include "NOPManager.hpp"

namespace JuNOCpp
{
    template <class TYPE>
    class BetterPremise;
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
            BetterAttribute();
            BetterAttribute(TYPE value);
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

            //BetterAttribute<TYPE> operator=(BetterAttribute<TYPE>& b_attr);

            void operator=(TYPE value);

            BetterPremise<TYPE>& operator==(BetterAttribute<TYPE>& b_attr);
            BetterPremise<TYPE>& operator==(BetterAttribute<TYPE>&& b_attr);

            BetterPremise<TYPE>& operator!=(BetterAttribute<TYPE>& b_attr);
            BetterPremise<TYPE>& operator!=(BetterAttribute<TYPE>&& b_attr);

            BetterPremise<TYPE>& operator>(BetterAttribute<TYPE>& b_attr);
            BetterPremise<TYPE>& operator>(BetterAttribute<TYPE>&& b_attr);

            BetterPremise<TYPE>& operator>=(BetterAttribute<TYPE>& b_attr);
            BetterPremise<TYPE>& operator>=(BetterAttribute<TYPE>&& b_attr);

            BetterPremise<TYPE>& operator<(BetterAttribute<TYPE>& b_attr);
            BetterPremise<TYPE>& operator<(BetterAttribute<TYPE>&& b_attr);

            BetterPremise<TYPE>& operator<=(BetterAttribute<TYPE>& b_attr);
            BetterPremise<TYPE>& operator<=(BetterAttribute<TYPE>&& b_attr);

            BetterPremise<TYPE>& operator==(const TYPE value);
            BetterPremise<TYPE>& operator!=(const TYPE value);
            BetterPremise<TYPE>& operator>(const TYPE value);
            BetterPremise<TYPE>& operator>=(const TYPE value);
            BetterPremise<TYPE>& operator<(const TYPE value);
            BetterPremise<TYPE>& operator<=(const TYPE value);
        };

        /**
         * Constrututor
         * 
         * @tparam TYPE 
         */
        template<class TYPE>
        BetterAttribute<TYPE>::BetterAttribute()
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
        BetterAttribute<TYPE>::BetterAttribute(TYPE value)
        {
            this->current_status = value;
            this->previous_status = value;
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
                this->previous_status = this->current_status;
                this->current_status = value;

                notify(renotify);
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
         * Cria e retorna uma Premise do tipo EQUAL
         * 
         * @tparam TYPE 
         * @param b_attr 
         * @return BetterPremise<TYPE>& 
         */
        template <class TYPE>
        BetterPremise<TYPE>& BetterAttribute<TYPE>::operator==(BetterAttribute<TYPE>& b_attr)
        {
            #ifdef USE_CUSTOM_SMART_PTRS
                shared_ptr<BetterPremise<TYPE>> premise(new BetterPremise<TYPE>());
            #else
                shared_ptr<BetterPremise<TYPE>> premise = std::make_shared<BetterPremise<TYPE>>(*new BetterPremise<TYPE>());
            #endif // USE_CUSTOM_SMART_PTRS

            premise->setOperation(BetterPremise<TYPE>::EQUAL);
            premise->setBetterAttribute(this, &b_attr);

            this->insert(premise);
            b_attr.insert(premise);

            return *premise;
        }

        /**
         * Cria e retorna uma Premise do tipo EQUAL
         * 
         * @tparam TYPE 
         * @param b_attr 
         * @return BetterPremise<TYPE>& 
         */
        template <class TYPE>
        BetterPremise<TYPE>& BetterAttribute<TYPE>::operator==(BetterAttribute<TYPE>&& b_attr)
        {
            #ifdef USE_CUSTOM_SMART_PTRS
                shared_ptr<BetterPremise<TYPE>> premise(new BetterPremise<TYPE>());
            #else
                shared_ptr<BetterPremise<TYPE>> premise = std::make_shared<BetterPremise<TYPE>>(*new BetterPremise<TYPE>());
            #endif // USE_CUSTOM_SMART_PTRS
            premise->setOperation(BetterPremise<TYPE>::EQUAL);
            premise->setBetterAttribute(this, &b_attr);

            this->insert(premise);
            b_attr.insert(premise);

            return *premise;
        }

        /**
         * Cria e retorna uma Premise do tipo DIFFERENT
         * 
         * @tparam TYPE 
         * @param b_attr 
         * @return BetterPremise<TYPE>& 
         */
        template <class TYPE>
        BetterPremise<TYPE>& BetterAttribute<TYPE>::operator!=(BetterAttribute<TYPE>& b_attr)
        {
            #ifdef USE_CUSTOM_SMART_PTRS
                shared_ptr<BetterPremise<TYPE>> premise(new BetterPremise<TYPE>());
            #else
                shared_ptr<BetterPremise<TYPE>> premise = std::make_shared<BetterPremise<TYPE>>(*new BetterPremise<TYPE>());
            #endif // USE_CUSTOM_SMART_PTRS
            premise->setOperation(BetterPremise<TYPE>::DIFFERENT);
            premise->setBetterAttribute(this, &b_attr);

            this->insert(premise);
            b_attr.insert(premise);

            return *premise;
        }

        /**
         * Cria e retorna uma Premise do tipo DIFFERENT
         * 
         * @tparam TYPE 
         * @param b_attr 
         * @return BetterPremise<TYPE>& 
         */
        template <class TYPE>
        BetterPremise<TYPE>& BetterAttribute<TYPE>::operator!=(BetterAttribute<TYPE>&& b_attr)
        {
            #ifdef USE_CUSTOM_SMART_PTRS
                shared_ptr<BetterPremise<TYPE>> premise(new BetterPremise<TYPE>());
            #else
                shared_ptr<BetterPremise<TYPE>> premise = std::make_shared<BetterPremise<TYPE>>(*new BetterPremise<TYPE>());
            #endif // USE_CUSTOM_SMART_PTRS
            premise->setOperation(BetterPremise<TYPE>::DIFFERENT);
            premise->setBetterAttribute(this, &b_attr);

            this->insert(premise);
            b_attr.insert(premise);

            return *premise;
        }

        /**
         * Cria e retorna uma Premise do tipo GREATER_THAN
         * 
         * @tparam TYPE 
         * @param b_attr 
         * @return BetterPremise<TYPE>& 
         */
        template <class TYPE>
        BetterPremise<TYPE>& BetterAttribute<TYPE>::operator>(BetterAttribute<TYPE>& b_attr)
        {
            #ifdef USE_CUSTOM_SMART_PTRS
                shared_ptr<BetterPremise<TYPE>> premise(new BetterPremise<TYPE>());
            #else
                shared_ptr<BetterPremise<TYPE>> premise = std::make_shared<BetterPremise<TYPE>>(*new BetterPremise<TYPE>());
            #endif // USE_CUSTOM_SMART_PTRS
            premise->setOperation(BetterPremise<TYPE>::GREATER_THAN);
            premise->setBetterAttribute(this, &b_attr);

            this->insert(premise);
            b_attr.insert(premise);

            return *premise;
        }

        /**
         * Cria e retorna uma Premise do tipo GREATER_THAN
         * 
         * @tparam TYPE 
         * @param b_attr 
         * @return BetterPremise<TYPE>& 
         */
        template <class TYPE>
        BetterPremise<TYPE>& BetterAttribute<TYPE>::operator>(BetterAttribute<TYPE>&& b_attr)
        {
            #ifdef USE_CUSTOM_SMART_PTRS
                shared_ptr<BetterPremise<TYPE>> premise(new BetterPremise<TYPE>());
            #else
                shared_ptr<BetterPremise<TYPE>> premise = std::make_shared<BetterPremise<TYPE>>(*new BetterPremise<TYPE>());
            #endif // USE_CUSTOM_SMART_PTRS
            premise->setOperation(BetterPremise<TYPE>::GREATER_THAN);
            premise->setBetterAttribute(this, &b_attr);

            this->insert(premise);
            b_attr.insert(premise);

            return *premise;
        }

        /**
         * Cria e retorna uma Premise do tipo GREATER_OR_EQUAL_THAN
         * 
         * @tparam TYPE 
         * @param b_attr 
         * @return BetterPremise<TYPE>& 
         */
        template <class TYPE>
        BetterPremise<TYPE>& BetterAttribute<TYPE>::operator>=(BetterAttribute<TYPE>& b_attr)
        {
            #ifdef USE_CUSTOM_SMART_PTRS
                shared_ptr<BetterPremise<TYPE>> premise(new BetterPremise<TYPE>());
            #else
                shared_ptr<BetterPremise<TYPE>> premise = std::make_shared<BetterPremise<TYPE>>(*new BetterPremise<TYPE>());
            #endif // USE_CUSTOM_SMART_PTRS
            premise->setOperation(BetterPremise<TYPE>::GREATER_OR_THAN_EQUAL);
            premise->setBetterAttribute(this, &b_attr);

            this->insert(premise);
            b_attr.insert(premise);

            return *premise;
        }

        /**
         * Cria e retorna uma Premise do tipo GREATER_OR_EQUAL_THAN
         * 
         * @tparam TYPE 
         * @param b_attr 
         * @return BetterPremise<TYPE>& 
         */
        template <class TYPE>
        BetterPremise<TYPE>& BetterAttribute<TYPE>::operator>=(BetterAttribute<TYPE>&& b_attr)
        {
            #ifdef USE_CUSTOM_SMART_PTRS
                shared_ptr<BetterPremise<TYPE>> premise(new BetterPremise<TYPE>());
            #else
                shared_ptr<BetterPremise<TYPE>> premise = std::make_shared<BetterPremise<TYPE>>(*new BetterPremise<TYPE>());
            #endif // USE_CUSTOM_SMART_PTRS
            premise->setOperation(BetterPremise<TYPE>::GREATER_OR_THAN_EQUAL);
            premise->setBetterAttribute(this, &b_attr);

            this->insert(premise);
            b_attr.insert(premise);

            return *premise;
        }

        /**
         * Cria e retorna uma Premise do tipo LESS_THAN
         * 
         * @tparam TYPE 
         * @param b_attr 
         * @return BetterPremise<TYPE>& 
         */
        template <class TYPE>
        BetterPremise<TYPE>& BetterAttribute<TYPE>::operator<(BetterAttribute<TYPE>& b_attr)
        {
            #ifdef USE_CUSTOM_SMART_PTRS
                shared_ptr<BetterPremise<TYPE>> premise(new BetterPremise<TYPE>());
            #else
                shared_ptr<BetterPremise<TYPE>> premise = std::make_shared<BetterPremise<TYPE>>(*new BetterPremise<TYPE>());
            #endif // USE_CUSTOM_SMART_PTRS
            premise->setOperation(BetterPremise<TYPE>::LESS_THAN);
            premise->setBetterAttribute(this, &b_attr);

            this->insert(premise);
            b_attr.insert(premise);

            return *premise;
        }

        /**
         * Cria e retorna uma Premise do tipo LESS_THAN
         * 
         * @tparam TYPE 
         * @param b_attr 
         * @return BetterPremise<TYPE>& 
         */
        template <class TYPE>
        BetterPremise<TYPE>& BetterAttribute<TYPE>::operator<(BetterAttribute<TYPE>&& b_attr)
        {
            #ifdef USE_CUSTOM_SMART_PTRS
                shared_ptr<BetterPremise<TYPE>> premise(new BetterPremise<TYPE>());
            #else
                shared_ptr<BetterPremise<TYPE>> premise = std::make_shared<BetterPremise<TYPE>>(*new BetterPremise<TYPE>());
            #endif // USE_CUSTOM_SMART_PTRS
            premise->setOperation(BetterPremise<TYPE>::LESS_THAN);
            premise->setBetterAttribute(this, &b_attr);

            this->insert(premise);
            b_attr.insert(premise);

            return *premise;
        }

        /**
         * Cria e retorna uma Premise do tipo LESS_OR_EQUAL_THAN
         * 
         * @tparam TYPE 
         * @param b_attr 
         * @return BetterPremise<TYPE>& 
         */
        template <class TYPE>
        BetterPremise<TYPE>& BetterAttribute<TYPE>::operator<=(BetterAttribute<TYPE>& b_attr)
        {
            #ifdef USE_CUSTOM_SMART_PTRS
                shared_ptr<BetterPremise<TYPE>> premise(new BetterPremise<TYPE>());
            #else
                shared_ptr<BetterPremise<TYPE>> premise = std::make_shared<BetterPremise<TYPE>>(*new BetterPremise<TYPE>());
            #endif // USE_CUSTOM_SMART_PTRS
            premise->setOperation(BetterPremise<TYPE>::LESS_OR_EQUAL_THAN);
            premise->setBetterAttribute(this, &b_attr);

            this->insert(premise);
            b_attr.insert(premise);

            return *premise;
        }

        /**
         * Cria e retorna uma Premise do tipo LESS_OR_EQUAL_THAN
         * 
         * @tparam TYPE 
         * @param b_attr 
         * @return BetterPremise<TYPE>& 
         */
        template <class TYPE>
        BetterPremise<TYPE>& BetterAttribute<TYPE>::operator<=(BetterAttribute<TYPE>&& b_attr)
        {
            #ifdef USE_CUSTOM_SMART_PTRS
                shared_ptr<BetterPremise<TYPE>> premise(new BetterPremise<TYPE>());
            #else
                shared_ptr<BetterPremise<TYPE>> premise = std::make_shared<BetterPremise<TYPE>>(*new BetterPremise<TYPE>());
            #endif // USE_CUSTOM_SMART_PTRS
            premise->setOperation(BetterPremise<TYPE>::LESS_OR_EQUAL_THAN);
            premise->setBetterAttribute(this, &b_attr);

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
         * Cria e retorna uma Premise do tipo EQUAL (com valor constante)
         * 
         * @tparam TYPE 
         * @param value 
         * @return BetterPremise<TYPE>& 
         */
        template <class TYPE>
        BetterPremise<TYPE>& BetterAttribute<TYPE>::operator==(const TYPE value)
        {
            #ifdef USE_CUSTOM_SMART_PTRS
                shared_ptr<BetterPremise<TYPE>> premise(new BetterPremise<TYPE>());
            #else
                shared_ptr<BetterPremise<TYPE>> premise = std::make_shared<BetterPremise<TYPE>>(*new BetterPremise<TYPE>());
            #endif // USE_CUSTOM_SMART_PTRS

            premise->setOperation(BetterPremise<TYPE>::EQUAL);
            premise->setBetterAttribute(this, value);

            this->insert(premise);

            return *premise;
        }

        /**
         * Cria e retorna uma Premise do tipo DIFFERENT (com valor constante)
         * 
         * @tparam TYPE 
         * @param value 
         * @return BetterPremise<TYPE>& 
         */
        template <class TYPE>
        BetterPremise<TYPE>& BetterAttribute<TYPE>::operator!=(const TYPE value)
        {
            #ifdef USE_CUSTOM_SMART_PTRS
                shared_ptr<BetterPremise<TYPE>> premise(new BetterPremise<TYPE>());
            #else
                shared_ptr<BetterPremise<TYPE>> premise = std::make_shared<BetterPremise<TYPE>>(*new BetterPremise<TYPE>());
            #endif // USE_CUSTOM_SMART_PTRS
            premise->setOperation(BetterPremise<TYPE>::DIFFERENT);
            premise->setBetterAttribute(this, value);

            this->insert(premise);

            return *premise;
        }

        /**
         * Cria e retorna uma Premise do tipo GREATER_THAN (com valor constante)
         * 
         * @tparam TYPE 
         * @param value 
         * @return BetterPremise<TYPE>& 
         */
        template <class TYPE>
        BetterPremise<TYPE>& BetterAttribute<TYPE>::operator>(const TYPE value)
        {
            #ifdef USE_CUSTOM_SMART_PTRS
                shared_ptr<BetterPremise<TYPE>> premise(new BetterPremise<TYPE>());
            #else
                shared_ptr<BetterPremise<TYPE>> premise = std::make_shared<BetterPremise<TYPE>>(*new BetterPremise<TYPE>());
            #endif // USE_CUSTOM_SMART_PTRS
            premise->setOperation(BetterPremise<TYPE>::GREATER_THAN);
            premise->setBetterAttribute(this, value);

            this->insert(premise);

            return *premise;
        }

        /**
         * Cria e retorna uma Premise do tipo GREATER_OR_EQUAL_THAN (com valor constante)
         * 
         * @tparam TYPE 
         * @param value 
         * @return BetterPremise<TYPE>& 
         */
        template <class TYPE>
        BetterPremise<TYPE>& BetterAttribute<TYPE>::operator>=(const TYPE value)
        {
            #ifdef USE_CUSTOM_SMART_PTRS
                shared_ptr<BetterPremise<TYPE>> premise(new BetterPremise<TYPE>());
            #else
                shared_ptr<BetterPremise<TYPE>> premise = std::make_shared<BetterPremise<TYPE>>(*new BetterPremise<TYPE>());
            #endif // USE_CUSTOM_SMART_PTRS
            premise->setOperation(BetterPremise<TYPE>::GREATER_OR_EQUAL_THAN);
            premise->setBetterAttribute(this, value);

            this->insert(premise);

            return *premise;
        }

        /**
         * Cria e retorna uma Premise do tipo LESS_THAN (com valor constante)
         * 
         * @tparam TYPE 
         * @param value 
         * @return BetterPremise<TYPE>& 
         */
        template <class TYPE>
        BetterPremise<TYPE>& BetterAttribute<TYPE>::operator<(const TYPE value)
        {
            #ifdef USE_CUSTOM_SMART_PTRS
                shared_ptr<BetterPremise<TYPE>> premise(new BetterPremise<TYPE>());
            #else
                shared_ptr<BetterPremise<TYPE>> premise = std::make_shared<BetterPremise<TYPE>>(*new BetterPremise<TYPE>());
            #endif // USE_CUSTOM_SMART_PTRS
            premise->setOperation(BetterPremise<TYPE>::LESS_THAN);
            premise->setBetterAttribute(this, value);

            this->insert(premise);

            return *premise;
        }

        /**
         * Cria e retorna uma Premise do tipo LESS_OR_EQUAL_THAN (com valor constante)
         * 
         * @tparam TYPE 
         * @param value 
         * @return BetterPremise<TYPE>& 
         */
        template <class TYPE>
        BetterPremise<TYPE>& BetterAttribute<TYPE>::operator<=(const TYPE value)
        {
            #ifdef USE_CUSTOM_SMART_PTRS
                shared_ptr<BetterPremise<TYPE>> premise(new BetterPremise<TYPE>());
            #else
                shared_ptr<BetterPremise<TYPE>> premise = std::make_shared<BetterPremise<TYPE>>(*new BetterPremise<TYPE>());
            #endif // USE_CUSTOM_SMART_PTRS
            premise->setOperation(BetterPremise<TYPE>::LESS_OR_EQUAL_THAN);
            premise->setBetterAttribute(this, value);

            this->insert(premise);

            return *premise;
        }
    }
}

#endif