#ifndef BETTER_ATTRIBUTE_HPP
#define BETTER_ATTRIBUTE_HPP
#include "../List.hpp"
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
        public:
            TYPE current_status;
            TYPE previous_status;

            TYPE (*updateOperation)(TYPE value1, TYPE value2);

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

        template<class TYPE>
        BetterAttribute<TYPE>::BetterAttribute()
        {
            this->updateOperation = nullptr;
        }

        template<class TYPE>
        BetterAttribute<TYPE>::BetterAttribute(TYPE value) : current_status{value}, previous_status{value} {}

        template<class TYPE>
        BetterAttribute<TYPE>::~BetterAttribute()
        {
        }

        template<class TYPE>
        TYPE BetterAttribute<TYPE>::getPreviousStatus()
        {
            return this->previous_status;
        }

        template<class TYPE>
        TYPE BetterAttribute<TYPE>::getCurrentStatus()
        {
            return this->current_status;
        }

        template<class TYPE>
        void BetterAttribute<TYPE>::setStatus(TYPE value, bool renotify /* = false */)
        {
            if(renotify || value != this->current_status)
            {
                this->previous_status = this->current_status;
                this->current_status = value;

                notify(renotify);
            }
        }

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
            auto aux = std::make_shared<BetterAttribute<TYPE>>(b_attr);
            this->insert(aux);
        }

        template<class TYPE>
        void BetterAttribute<TYPE>::operator=(TYPE value)
        {
            this->setStatus(value);
        }

        template <class TYPE>
        BetterPremise<TYPE>& BetterAttribute<TYPE>::operator==(BetterAttribute<TYPE>& b_attr)
        {
            BetterPremise<TYPE> aux;
            std::shared_ptr<BetterPremise<TYPE>> premise = std::make_shared<BetterPremise<TYPE>>(aux);
            premise->setOperation(BetterPremise<TYPE>::EQUAL);
            premise->setBetterAttribute(this, &b_attr);

            this->insert(premise);
            b_attr.insert(premise);

            return *premise;
        }

        template <class TYPE>
        BetterPremise<TYPE>& BetterAttribute<TYPE>::operator==(BetterAttribute<TYPE>&& b_attr)
        {
            BetterPremise<TYPE> aux;
            std::shared_ptr<BetterPremise<TYPE>> premise = std::make_shared<BetterPremise<TYPE>>(aux);
            premise->setOperation(BetterPremise<TYPE>::EQUAL);
            premise->setBetterAttribute(this, &b_attr);

            this->insert(premise);
            b_attr.insert(premise);

            return *premise;
        }

        template <class TYPE>
        BetterPremise<TYPE>& BetterAttribute<TYPE>::operator!=(BetterAttribute<TYPE>& b_attr)
        {
            BetterPremise<TYPE> aux;
            std::shared_ptr<BetterPremise<TYPE>> premise = std::make_shared<BetterPremise<TYPE>>(aux);
            premise->setOperation(BetterPremise<TYPE>::DIFFERENT);
            premise->setBetterAttribute(this, &b_attr);

            this->insert(premise);
            b_attr.insert(premise);

            return *premise;
        }

        template <class TYPE>
        BetterPremise<TYPE>& BetterAttribute<TYPE>::operator!=(BetterAttribute<TYPE>&& b_attr)
        {
            BetterPremise<TYPE> aux;
            std::shared_ptr<BetterPremise<TYPE>> premise = std::make_shared<BetterPremise<TYPE>>(aux);
            premise->setOperation(BetterPremise<TYPE>::DIFFERENT);
            premise->setBetterAttribute(this, &b_attr);

            this->insert(premise);
            b_attr.insert(premise);

            return *premise;
        }

        template <class TYPE>
        BetterPremise<TYPE>& BetterAttribute<TYPE>::operator>(BetterAttribute<TYPE>& b_attr)
        {
            BetterPremise<TYPE> aux;
            std::shared_ptr<BetterPremise<TYPE>> premise = std::make_shared<BetterPremise<TYPE>>(aux);
            premise->setOperation(BetterPremise<TYPE>::GREATHER_THAN);
            premise->setBetterAttribute(this, &b_attr);

            this->insert(premise);
            b_attr.insert(premise);

            return *premise;
        }

        template <class TYPE>
        BetterPremise<TYPE>& BetterAttribute<TYPE>::operator>(BetterAttribute<TYPE>&& b_attr)
        {
            BetterPremise<TYPE> aux;
            std::shared_ptr<BetterPremise<TYPE>> premise = std::make_shared<BetterPremise<TYPE>>(aux);
            premise->setOperation(BetterPremise<TYPE>::GREATHER_THAN);
            premise->setBetterAttribute(this, &b_attr);

            this->insert(premise);
            b_attr.insert(premise);

            return *premise;
        }

        template <class TYPE>
        BetterPremise<TYPE>& BetterAttribute<TYPE>::operator>=(BetterAttribute<TYPE>& b_attr)
        {
            BetterPremise<TYPE> aux;
            std::shared_ptr<BetterPremise<TYPE>> premise = std::make_shared<BetterPremise<TYPE>>(aux);
            premise->setOperation(BetterPremise<TYPE>::GREATHER_OR_THAN_EQUAL);
            premise->setBetterAttribute(this, &b_attr);

            this->insert(premise);
            b_attr.insert(premise);

            return *premise;
        }

        template <class TYPE>
        BetterPremise<TYPE>& BetterAttribute<TYPE>::operator>=(BetterAttribute<TYPE>&& b_attr)
        {
            BetterPremise<TYPE> aux;
            std::shared_ptr<BetterPremise<TYPE>> premise = std::make_shared<BetterPremise<TYPE>>(aux);
            premise->setOperation(BetterPremise<TYPE>::GREATHER_OR_THAN_EQUAL);
            premise->setBetterAttribute(this, &b_attr);

            this->insert(premise);
            b_attr.insert(premise);

            return *premise;
        }

        template <class TYPE>
        BetterPremise<TYPE>& BetterAttribute<TYPE>::operator<(BetterAttribute<TYPE>& b_attr)
        {
            BetterPremise<TYPE> aux;
            std::shared_ptr<BetterPremise<TYPE>> premise = std::make_shared<BetterPremise<TYPE>>(aux);
            premise->setOperation(BetterPremise<TYPE>::LESS_THAN);
            premise->setBetterAttribute(this, &b_attr);

            this->insert(premise);
            b_attr.insert(premise);

            return *premise;
        }

        template <class TYPE>
        BetterPremise<TYPE>& BetterAttribute<TYPE>::operator<(BetterAttribute<TYPE>&& b_attr)
        {
            BetterPremise<TYPE> aux;
            std::shared_ptr<BetterPremise<TYPE>> premise = std::make_shared<BetterPremise<TYPE>>(aux);
            premise->setOperation(BetterPremise<TYPE>::LESS_THAN);
            premise->setBetterAttribute(this, &b_attr);

            this->insert(premise);
            b_attr.insert(premise);

            return *premise;
        }

        template <class TYPE>
        BetterPremise<TYPE>& BetterAttribute<TYPE>::operator<=(BetterAttribute<TYPE>& b_attr)
        {
            BetterPremise<TYPE> aux;
            std::shared_ptr<BetterPremise<TYPE>> premise = std::make_shared<BetterPremise<TYPE>>(aux);
            premise->setOperation(BetterPremise<TYPE>::LESS_OR_EQUAL_THAN);
            premise->setBetterAttribute(this, &b_attr);

            this->insert(premise);
            b_attr.insert(premise);

            return *premise;
        }

        template <class TYPE>
        BetterPremise<TYPE>& BetterAttribute<TYPE>::operator<=(BetterAttribute<TYPE>&& b_attr)
        {
            BetterPremise<TYPE> aux;
            std::shared_ptr<BetterPremise<TYPE>> premise = std::make_shared<BetterPremise<TYPE>>(aux);
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
    
        template <class TYPE>
        BetterPremise<TYPE>& BetterAttribute<TYPE>::operator==(const TYPE value)
        {
            BetterPremise<TYPE> aux;
            std::shared_ptr<BetterPremise<TYPE>> premise = std::make_shared<BetterPremise<TYPE>>(aux);
            premise->setOperation(BetterPremise<TYPE>::EQUAL);
            premise->setBetterAttribute(this, value);

            this->insert(premise);

            return *premise;
        }

        template <class TYPE>
        BetterPremise<TYPE>& BetterAttribute<TYPE>::operator!=(const TYPE value)
        {
            BetterPremise<TYPE> aux;
            std::shared_ptr<BetterPremise<TYPE>> premise = std::make_shared<BetterPremise<TYPE>>(aux);
            premise->setOperation(BetterPremise<TYPE>::DIFFERENT);
            premise->setBetterAttribute(this, value);

            this->insert(premise);

            return *premise;
        }

        template <class TYPE>
        BetterPremise<TYPE>& BetterAttribute<TYPE>::operator>(const TYPE value)
        {
            BetterPremise<TYPE> aux;
            std::shared_ptr<BetterPremise<TYPE>> premise = std::make_shared<BetterPremise<TYPE>>(aux);
            premise->setOperation(BetterPremise<TYPE>::GREATER_THAN);
            premise->setBetterAttribute(this, value);

            this->insert(premise);

            return *premise;
        }

        template <class TYPE>
        BetterPremise<TYPE>& BetterAttribute<TYPE>::operator>=(const TYPE value)
        {
            BetterPremise<TYPE> aux;
            std::shared_ptr<BetterPremise<TYPE>> premise = std::make_shared<BetterPremise<TYPE>>(aux);
            premise->setOperation(BetterPremise<TYPE>::GREATER_OR_EQUAL_THAN);
            premise->setBetterAttribute(this, value);

            this->insert(premise);

            return *premise;
        }

        template <class TYPE>
        BetterPremise<TYPE>& BetterAttribute<TYPE>::operator<(const TYPE value)
        {
            BetterPremise<TYPE> aux;
            std::shared_ptr<BetterPremise<TYPE>> premise = std::make_shared<BetterPremise<TYPE>>(aux);
            premise->setOperation(BetterPremise<TYPE>::LESS_THAN);
            premise->setBetterAttribute(this, value);

            this->insert(premise);

            return *premise;
        }

        template <class TYPE>
        BetterPremise<TYPE>& BetterAttribute<TYPE>::operator<=(const TYPE value)
        {
            BetterPremise<TYPE> aux;
            std::shared_ptr<BetterPremise<TYPE>> premise = std::make_shared<BetterPremise<TYPE>>(aux);
            premise->setOperation(BetterPremise<TYPE>::LESS_OR_EQUAL_THAN);
            premise->setBetterAttribute(this, value);

            this->insert(premise);

            return *premise;
        }
    }
}

#endif