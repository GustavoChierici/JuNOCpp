#pragma once

//#include "BetterPremise.hpp"
#include "../List.hpp"

#include <iostream>
#include "Notifier.hpp"
#include "./BasePremise.hpp"

namespace JuNOCpp
{
    template<class TYPE>
    class BetterPremise;

    class BetterRule;
    class BetterCondition: public Notifiable, public Notifier
    {
    public:
        const static int CONJUNCTION = 0;
        const static int DISJUNCTION = 1;
        const static int SINGLE = 2;
    public:
        int quantity;
        int count_approved;
        int count_impertinents;
        List<BasePremise*> impertinents;
        bool persistant;
        int mode;
        BetterRule* rule;
        bool is_impertinents_active {false};
    public:
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
            b_condition.persistant = true;
            return b_condition;
        }

        void referenceBetterRule(BetterRule* rule);

        void setQuantity(const int quant);

        void update(const bool renotify = false);
        void update(const bool renotify, const bool status);
        void notify(const bool renotify = false);
        void activateImpertinents();
        void deactivateImpertinents();
    
        template <class TYPE>
        BetterCondition& operator &&(BetterPremise<TYPE>& b_premise)
        {
            if((this->mode == BetterCondition::CONJUNCTION or this->mode == BetterCondition::SINGLE) and !this->persistant)
            {
                b_premise.insert(this->shared_from_this());
                this->setQuantity(this->quantity + 1);

                return *this;
            }
            else
            {
                BetterCondition aux;

                std::shared_ptr<BetterCondition> condition = std::make_shared<BetterCondition>(aux);
                condition->setQuantity(2);
                condition->mode = BetterCondition::CONJUNCTION;

                this->insert(condition);
                b_premise.insert(condition);
                
                return *condition;
            }
        }

        template <class TYPE>
        BetterCondition& operator &&(BetterPremise<TYPE>&& b_premise)
        {
            if((this->mode == BetterCondition::CONJUNCTION or this->mode == BetterCondition::SINGLE) and !this->persistant)
            {
                b_premise.insert(this->shared_from_this());
                this->setQuantity(this->quantity + 1);

                return *this;
            }
            else
            {
                BetterCondition aux;

                std::shared_ptr<BetterCondition> condition = std::make_shared<BetterCondition>(aux);
                condition->setQuantity(2);
                condition->mode = BetterCondition::CONJUNCTION;

                this->insert(condition);
                b_premise.insert(condition);
                
                return *condition;
            }
        }

        template <class TYPE>
        BetterCondition& operator ||(BetterPremise<TYPE>& b_premise)
        {
            if((this->mode == BetterCondition::DISJUNCTION or this->mode == BetterCondition::SINGLE) and !this->persistant)
            {
                b_premise.insert(this->shared_from_this());

                return *this;
            }
            else
            {
                BetterCondition aux;

                std::shared_ptr<BetterCondition> condition = std::make_shared<BetterCondition>(aux);
                condition->setQuantity(1);
                condition->mode = BetterCondition::DISJUNCTION;

                this->insert(condition);
                b_premise.insert(condition);
                
                return *condition;
            }
        }

        template <class TYPE>
        BetterCondition& operator ||(BetterPremise<TYPE>&& b_premise)
        {
            if((this->mode == BetterCondition::DISJUNCTION or this->mode == BetterCondition::SINGLE) and !this->persistant)
            {
                b_premise.insert(this->shared_from_this());

                return *this;
            }
            else
            {
                BetterCondition aux;

                std::shared_ptr<BetterCondition> condition = std::make_shared<BetterCondition>(aux);
                condition->setQuantity(1);
                condition->mode = BetterCondition::DISJUNCTION;

                this->insert(condition);
                b_premise.insert(condition);
                
                return *condition;
            }
        }
        
        BetterCondition& operator &&(BetterCondition& b_condition);
        BetterCondition& operator &&(BetterCondition&& b_condition);
        BetterCondition& operator ||(BetterCondition& b_condition);
        BetterCondition& operator ||(BetterCondition&& b_condition);
    };
}
