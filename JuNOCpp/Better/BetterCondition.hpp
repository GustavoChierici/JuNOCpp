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
    private:
        int quantity;
        int count_approved;
        int count_impertinents;
        List<BasePremise*> impertinents;
        bool persistant;
        int mode;
        bool is_impertinents_active {false};
    public:
        bool previous_status;
        bool current_status;

    public:
        BetterCondition();
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

        void setMode(const int mode) { this->mode = mode; }
        const int getMode() { return this->mode; }

        void addImpertinent(BasePremise* premise) { this->impertinents.insertInfo(premise); }

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
