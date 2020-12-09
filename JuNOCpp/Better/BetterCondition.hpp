#pragma once

//#include "BetterPremise.hpp"
#include "../List.hpp"

#include <iostream>
#include "Notifier.hpp"

namespace JuNOCpp
{
    template<class TYPE>
    class BetterPremise;

    class BetterRule;
    class BetterCondition: public Notifiable, public Notifier
    {
    public:
        int quantity;
        int approved_premises_and_subconds;
        bool permanent;
        BetterRule* rule;
    public:
        BetterCondition* better_condition_above;
        bool previous_status;
        bool current_status;

    public:
        BetterCondition();
        ~BetterCondition();

        template <class TYPE>
        void addBetterPremise(BetterPremise<TYPE>* prm)
        {
            prm->referenceBetterCondition(this);
        }

        void addBetterCondition(BetterCondition* b_condition);

        static BetterCondition& sharedCondition(BetterCondition& b_condition)
        {
            b_condition.permanent = true;
            return b_condition;
        }

        virtual void conditionalCheck(bool status, bool renotify = false);
        void referenceBetterRule(BetterRule* rule);

        void setQuantity(const int quant);

        void update(const bool renotify = false);
        void notify(const bool renotify = false);
    
        template <class TYPE>
        BetterCondition& operator &&(BetterPremise<TYPE>& b_premise)
        {
            BetterCondition aux;

            std::shared_ptr<BetterCondition> condition = std::make_shared<BetterCondition>(aux);
            condition->setQuantity(2);

            this->insert(condition);
            b_premise.insert(condition);
            
            return *condition;
        }

        template <class TYPE>
        BetterCondition& operator &&(BetterPremise<TYPE>&& b_premise)
        {
            BetterCondition aux;

            std::shared_ptr<BetterCondition> condition = std::make_shared<BetterCondition>(aux);
            condition->setQuantity(2);

            this->insert(condition);
            b_premise.insert(condition);
            
            return *condition;
        }

        template <class TYPE>
        BetterCondition& operator ||(BetterPremise<TYPE>& b_premise)
        {
            BetterCondition aux;

            std::shared_ptr<BetterCondition> condition = std::make_shared<BetterCondition>(aux);
            condition->setQuantity(1);

            this->insert(condition);
            b_premise.insert(condition);
            
            return *condition;
        }

        template <class TYPE>
        BetterCondition& operator ||(BetterPremise<TYPE>&& b_premise)
        {
            BetterCondition aux;

            std::shared_ptr<BetterCondition> condition = std::make_shared<BetterCondition>(aux);
            condition->setQuantity(1);

            this->insert(condition);
            b_premise.insert(condition);
            
            return *condition;
        }
        
        BetterCondition& operator &&(BetterCondition& b_condition);
        BetterCondition& operator &&(BetterCondition&& b_condition);
        BetterCondition& operator ||(BetterCondition& b_condition);
        BetterCondition& operator ||(BetterCondition&& b_condition);
    };
}
