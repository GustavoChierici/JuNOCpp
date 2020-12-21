#ifndef BETTER_PREMISE_HPP
#define BETTER_PREMISE_HPP
#include <iostream>
#include "../CustomString.hpp"
#include "../List.hpp"
#include "./BetterAttribute.hpp"
#include "./BetterCondition.hpp"
namespace JuNOCpp
{
    template<class TYPE>
    class BetterPremise: public Notifiable, public Notifier
    {
    public:
        Attributes::BetterAttribute<TYPE>* attr1;
        Attributes::BetterAttribute<TYPE>* attr2;
        TYPE value;
        bool status;
        bool previous_status;
        List<BetterCondition> conditions;
        int operation;
        bool (*cmp)(TYPE, TYPE);

    public:
        const static int DIFFERENT = 0;
        const static int EQUAL = 1;
        const static int GREATER_THAN = 2;
        const static int GREATER_OR_EQUAL_THAN = 3;
        const static int LESS_THAN = 4;
        const static int LESS_OR_EQUAL_THAN = 5;

    public:
        BetterPremise();
        ~BetterPremise();

        void setOperation(const int op = BetterPremise::EQUAL);

        void setBetterAttribute(Attributes::BetterAttribute<TYPE>* b_attr1, Attributes::BetterAttribute<TYPE>* b_attr2);
        void setBetterAttribute(Attributes::BetterAttribute<TYPE>* b_attr1, TYPE value);

        void referenceBetterCondition(BetterCondition* b_cond);

        void update(const bool renotify = false);
        void update(const bool renotify, const bool status) {}

        template <class OT>
        BetterCondition& operator &&(BetterPremise<OT>& b_premise);
        template <class OT>
        BetterCondition& operator &&(BetterPremise<OT>&& b_premise);
        template <class OT>
        BetterCondition& operator ||(BetterPremise<OT>& b_premise);
        template <class OT>
        BetterCondition& operator ||(BetterPremise<OT>&& b_premise);

        BetterCondition& operator &&(BetterCondition& b_condition);
        BetterCondition& operator &&(BetterCondition&& b_condition);
        BetterCondition& operator ||(BetterCondition& b_condition);
        BetterCondition& operator ||(BetterCondition&& b_condition);

        operator BetterCondition&();
    };

    template <class TYPE>
    BetterPremise<TYPE>::BetterPremise()
    {
        this->conditions;
        this->conditions.setAutoDel(false);
        this->previous_status = false;
        this->status = false;

        this->attr1 = nullptr;
        this->attr2 = nullptr;
    }

    template <class TYPE>
    BetterPremise<TYPE>::~BetterPremise()
    {
    }

    template <class TYPE>
    void BetterPremise<TYPE>::setOperation(const int op /* = BetterPremise::EQUAL*/)
    {
        switch (op)
        {
        case BetterPremise::DIFFERENT:
            this->cmp = [](TYPE value1, TYPE value2){
                return value1 != value2;
            };
            break;
        case BetterPremise::EQUAL:
            this->cmp = [](TYPE value1, TYPE value2){
                return value1 == value2;
            };
            break;
        case BetterPremise::GREATER_THAN:
            this->cmp = [](TYPE value1, TYPE value2){
                return value1 > value2;
            };
            break;
        case BetterPremise::GREATER_OR_EQUAL_THAN:
            this->cmp = [](TYPE value1, TYPE value2){
                return value1 >= value2;
            };
            break;
        case BetterPremise::LESS_THAN:
            this->cmp = [](TYPE value1, TYPE value2){
                return value1 < value2;
            };
            break;
        case BetterPremise::LESS_OR_EQUAL_THAN:
            this->cmp = [](TYPE value1, TYPE value2){
                return value1 <= value2;
            };
            break;
        default:
            std::cout << "PREMISE INVÁLIDO!" << std::endl;
            exit(1);
            break;
        }
    }

    template <class TYPE>
    void BetterPremise<TYPE>::setBetterAttribute(Attributes::BetterAttribute<TYPE>* b_attr1, Attributes::BetterAttribute<TYPE>* b_attr2)
    {
        this->attr1 = b_attr1;
        this->attr2 = b_attr2;
        
        //this->conditionalCheck();
    }

    template <class TYPE>
    void BetterPremise<TYPE>::setBetterAttribute(Attributes::BetterAttribute<TYPE>* b_attr1, TYPE value)
    {
        this->attr1 = b_attr1;
        this->value = value;
        // b_attr1->insert(shared_from_this());
        
        //this->conditionalCheck();
    }

    template <class TYPE>
    void BetterPremise<TYPE>::referenceBetterCondition(BetterCondition* b_condition)
    {
        this->conditions.insertInfo(*b_condition);
    }

    template <class TYPE>
    void BetterPremise<TYPE>::update(const bool renotify)
    {
        // std::cout << "PREMISE (" << this << ") - "; 
        if(this->attr2)
            this->status = this->cmp(this->attr1->getCurrentStatus(), this->attr2->getCurrentStatus());
        else
            this->status = this->cmp(this->attr1->getCurrentStatus(), this->value);
        if(renotify || this->status != this->previous_status)
        {
            this->previous_status = this->status;
            this->notify(renotify, this->status);
        }
    }

    template <class TYPE>
    template <class OT>
    BetterCondition& BetterPremise<TYPE>::operator &&(BetterPremise<OT>& b_premise)
    {
        BetterCondition aux;
        std::shared_ptr<BetterCondition> condition = std::make_shared<BetterCondition>(aux);
        condition->setQuantity(2);
        condition->mode = BetterCondition::CONJUNCTION;

        this->insert(condition);
        b_premise.insert(condition);
        
        return *condition;
    }

    template <class TYPE>
    template <class OT>
    BetterCondition& BetterPremise<TYPE>::operator &&(BetterPremise<OT>&& b_premise)
    {
        BetterCondition aux;

        std::shared_ptr<BetterCondition> condition = std::make_shared<BetterCondition>(aux);
        condition->setQuantity(2);
        condition->mode = BetterCondition::CONJUNCTION;

        this->insert(condition);
        b_premise.insert(condition);
        
        return *condition;
    }

    template <class TYPE>
    template <class OT>
    BetterCondition& BetterPremise<TYPE>::operator ||(BetterPremise<OT>& b_premise)
    {
        BetterCondition aux;

        std::shared_ptr<BetterCondition> condition = std::make_shared<BetterCondition>(aux);
        condition->setQuantity(1);
        condition->mode = BetterCondition::DISJUNCTION;

        this->insert(condition);
        b_premise.insert(condition);
        
        return *condition;
    }

    template <class TYPE>
    template <class OT>
    BetterCondition& BetterPremise<TYPE>::operator ||(BetterPremise<OT>&& b_premise)
    {
        BetterCondition aux;

        std::shared_ptr<BetterCondition> condition = std::make_shared<BetterCondition>(aux);
        condition->setQuantity(1);
        condition->mode = BetterCondition::DISJUNCTION;

        this->insert(condition);
        b_premise.insert(condition);
        
        return *condition;
    }

    template <class TYPE>
    BetterCondition& BetterPremise<TYPE>::operator &&(BetterCondition& b_condition)
    {
        if((b_condition.mode == BetterCondition::CONJUNCTION or b_condition.mode == BetterCondition::SINGLE) and !b_condition.persistant)
        {
            this->insert(b_condition.shared_from_this());
            b_condition.setQuantity(b_condition.quantity + 1);
            
            return b_condition;
        }
        else
        {
            BetterCondition aux;

            std::shared_ptr<BetterCondition> condition = std::make_shared<BetterCondition>(aux);
            condition->setQuantity(2);
            condition->mode = BetterCondition::CONJUNCTION;

            this->insert(condition);
            b_condition.insert(condition);
            
            return *condition;
        }
    }

    template <class TYPE>
    BetterCondition& BetterPremise<TYPE>::operator &&(BetterCondition&& b_condition)
    {
        if((b_condition.mode == BetterCondition::CONJUNCTION or b_condition.mode == BetterCondition::SINGLE) and !b_condition.persistant)
        {
            this->insert(b_condition.shared_from_this());
            b_condition.setQuantity(b_condition.quantity + 1);
            
            return b_condition;
        }
        else
        {
            BetterCondition aux;

            std::shared_ptr<BetterCondition> condition = std::make_shared<BetterCondition>(aux);
            condition->setQuantity(2);
            condition->mode = BetterCondition::CONJUNCTION;

            this->insert(condition);
            b_condition.insert(condition);
            
            return *condition;
        }
    }

    template <class TYPE>
    BetterCondition& BetterPremise<TYPE>::operator ||(BetterCondition& b_condition)
    {
        if ((b_condition.mode == BetterCondition::DISJUNCTION or b_condition.mode == BetterCondition::SINGLE) and !b_condition.persistant)
        {
            this->insert(b_condition.shared_from_this());

            return b_condition;
        }
        else
        {
            BetterCondition aux;

            std::shared_ptr<BetterCondition> condition = std::make_shared<BetterCondition>(aux);
            condition->setQuantity(1);
            condition->mode = BetterCondition::DISJUNCTION;

            this->insert(condition);
            b_condition.insert(condition);
            
            return *condition;
        }
    }

    template <class TYPE>
    BetterCondition& BetterPremise<TYPE>::operator ||(BetterCondition&& b_condition)
    {
        if ((b_condition.mode == BetterCondition::DISJUNCTION or b_condition.mode == BetterCondition::SINGLE) and !b_condition.persistant)
        {
            this->insert(b_condition.shared_from_this());

            return b_condition;
        }
        else
        {
            BetterCondition aux;

            std::shared_ptr<BetterCondition> condition = std::make_shared<BetterCondition>(aux);
            condition->setQuantity(1);
            condition->mode = BetterCondition::DISJUNCTION;

            this->insert(condition);
            b_condition.insert(condition);
            
            return *condition;
        }
    }

    template <class TYPE>
    BetterPremise<TYPE>::operator JuNOCpp::BetterCondition&()
    {
        BetterCondition aux;

        std::shared_ptr<BetterCondition> condition = std::make_shared<BetterCondition>(aux);
        condition->setQuantity(1);
        condition->mode = BetterCondition::SINGLE;

        this->insert(condition);
        
        return *condition;
    }
}

#endif