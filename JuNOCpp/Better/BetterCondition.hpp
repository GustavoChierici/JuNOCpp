#pragma once

#include <iostream>
#include "Notifier.hpp"
#include "./Impertinent.hpp"

namespace JuNOCpp
{
    template<class TYPE>
    class BetterPremise;

    class BetterRule;
    class BetterCondition: public Notifiable, public Notifier
    {
    public:
        enum LogicalOperator {
            CONJUNCTION = 0,
            DISJUNCTION,
            SINGLE
        };
    private:
        int quantity;
        int count_approved;
        int count_impertinents;
        Utils::forward_list<Impertinent*> impertinents;
        bool persistant;
        LogicalOperator mode;
        bool is_impertinents_active {false};
    public:
        bool previous_status;
        bool current_status;

    public:
        BetterCondition(CustomString name = "UnnamedCondition");
        ~BetterCondition();

        static BetterCondition& sharedCondition(BetterCondition& b_condition)
        {
            b_condition.makePersistant();
            return b_condition;
        }

        void setQuantity(const int quant);

        void update(const bool renotify = false);
        void update(const bool renotify, const bool status);
        void notify(const bool renotify = false);
        void activateImpertinents();
        void deactivateImpertinents();

        void setMode(LogicalOperator mode) { this->mode = mode; }
        LogicalOperator getMode() { return mode; }

        void addImpertinent(Impertinent* premise) { this->impertinents.push_back(premise); }

        void makePersistant() { this->persistant = true; }
        bool isPersistant() { return this->persistant; }
    
        void incCountApproved() { this->count_approved++; }
        void decCountApproved() { this->count_approved--; } 
        void incCountImpertinents() { this->count_impertinents++; }
        void decCountImpertinents() { this->count_impertinents--; } 
    
        /**
         * Cria e retorna uma Condition do tipo CONJUNCTION
         * 
         * @tparam TYPE 
         * @param b_premise 
         * @return BetterCondition& 
         */
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
                #ifdef USE_CUSTOM_SMART_PTRS
                    shared_ptr<BetterCondition> condition(new BetterCondition());
                #else
                    shared_ptr<BetterCondition> condition = std::make_shared<BetterCondition>(*new BetterCondition());
                #endif // USE_CUSTOM_SMART_PTRS
                condition->setQuantity(2);
                condition->mode = BetterCondition::CONJUNCTION;

                this->insert(condition);
                b_premise.insert(condition);
                
                return *condition;
            }
        }

        /**
         * Cria e retorna uma Condition do tipo CONJUNCTION
         * 
         * @tparam TYPE 
         * @param b_premise 
         * @return BetterCondition& 
         */
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
                #ifdef USE_CUSTOM_SMART_PTRS
                    shared_ptr<BetterCondition> condition(new BetterCondition());
                #else
                    shared_ptr<BetterCondition> condition = std::make_shared<BetterCondition>(*new BetterCondition());
                #endif // USE_CUSTOM_SMART_PTRS
                condition->setQuantity(2);
                condition->mode = BetterCondition::CONJUNCTION;

                this->insert(condition);
                b_premise.insert(condition);
                
                return *condition;
            }
        }

        /**
         * Cria e retorna uma Condition do tipo DISJUNCTION
         * 
         * @tparam TYPE 
         * @param b_premise 
         * @return BetterCondition& 
         */
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
                #ifdef USE_CUSTOM_SMART_PTRS
                    shared_ptr<BetterCondition> condition(new BetterCondition());
                #else
                    shared_ptr<BetterCondition> condition = std::make_shared<BetterCondition>(*new BetterCondition());
                #endif // USE_CUSTOM_SMART_PTRS
                condition->setQuantity(1);
                condition->mode = BetterCondition::DISJUNCTION;

                this->insert(condition);
                b_premise.insert(condition);
                
                return *condition;
            }
        }

        /**
         * Cria e retorna uma Condition do tipo DISJUNCTION
         * 
         * @tparam TYPE 
         * @param b_premise 
         * @return BetterCondition& 
         */
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
                #ifdef USE_CUSTOM_SMART_PTRS
                    shared_ptr<BetterCondition> condition(new BetterCondition());
                #else
                    shared_ptr<BetterCondition> condition = std::make_shared<BetterCondition>(*new BetterCondition());
                #endif // USE_CUSTOM_SMART_PTRS> condition = std::make_shared<BetterCondition>(aux);
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
