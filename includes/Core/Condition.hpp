#ifndef JUNOCPP_CONDITION_HPP
#define JUNOCPP_CONDITION_HPP

#include <iostream>
#include "Notifier.hpp"
#include "Impertinent.hpp"

namespace JuNOCpp
{
    namespace Core
    {
        template<class PrT, typename RT, typename CmpOpT>
        class Premise;

        class Rule;
        class Condition: public Notifiable, public Notifier
        {
        template<class PrT, typename RT, typename CmpOpT>
        friend class Premise;
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
            bool previous_status;
            bool current_status;

        public:
            Condition(Utils::CustomString name = "UnnamedCondition");
            ~Condition();

            static Condition& persistantCondition(Condition& b_condition)
            {
                b_condition.makePersistant();
                return b_condition;
            }

            void setQuantity(const int quant);
            const int getQuantity() const { return quantity; }
            void incQuantity() { ++quantity; }
            void decQuantity() { --quantity; }

            const bool getCurrentStatus() const { return current_status; }

            void update(const bool renotify = false);
            void update(const bool renotify, const bool status);
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
             * @brief Cria e retorna uma Condition do tipo CONJUNCTION
             * 
             * @tparam PrT 
             * @tparam RT 
             * @tparam CmpOpT 
             * @param b_premise 
             * @return Condition& 
             */
            template <class PrT, typename RT, typename CmpOpT>
            Condition& operator &&(Premise<PrT, RT, CmpOpT>& b_premise)
            {
                if((this->mode == Condition::CONJUNCTION or this->mode == Condition::SINGLE) and !this->persistant)
                {
                    b_premise.insert(shared_from_this());
                    incQuantity();

                    if(b_premise.getCurrentStatus() and !b_premise.isImpertinent())
                        update(false, b_premise.getCurrentStatus());

                    return *this;
                }
                else
                {
                    #ifdef USE_CUSTOM_SMART_PTRS
                        shared_ptr<Condition> condition(new Condition());
                    #else
                        shared_ptr<Condition> condition = std::make_shared<Condition>(*new Condition());
                    #endif // USE_CUSTOM_SMART_PTRS
                    condition->setQuantity(2);
                    condition->mode = Condition::CONJUNCTION;

                    this->insert(condition);
                    b_premise.insert(condition);

                    if(b_premise.getCurrentStatus() and !b_premise.isImpertinent())
                        condition->update(false, b_premise.getCurrentStatus());
                    if(this->current_status)
                        condition->update(false, this->current_status);
                    
                    return *condition;
                }
            }

            /**
             * @brief Cria e retorna uma Condition do tipo CONJUNCTION
             * 
             * @tparam PrT 
             * @tparam RT 
             * @tparam CmpOpT 
             * @param b_premise 
             * @return Condition& 
             */
            template <class PrT, typename RT, typename CmpOpT>
            Condition& operator &&(Premise<PrT, RT, CmpOpT>&& b_premise)
            {
                if((this->mode == Condition::CONJUNCTION or this->mode == Condition::SINGLE) and !this->persistant)
                {
                    b_premise.insert(shared_from_this());
                    incQuantity();

                    if(b_premise.getCurrentStatus() and !b_premise.isImpertinent())
                        update(false, b_premise.getCurrentStatus());

                    return *this;
                }
                else
                {
                    #ifdef USE_CUSTOM_SMART_PTRS
                        shared_ptr<Condition> condition(new Condition());
                    #else
                        shared_ptr<Condition> condition = std::make_shared<Condition>(*new Condition());
                    #endif // USE_CUSTOM_SMART_PTRS
                    condition->setQuantity(2);
                    condition->mode = Condition::CONJUNCTION;

                    this->insert(condition);
                    b_premise.insert(condition);

                    if(b_premise.getCurrentStatus() and !b_premise.isImpertinent())
                        condition->update(false, b_premise.getCurrentStatus());
                    if(this->current_status)
                        condition->update(false, this->current_status);
                    
                    return *condition;
                }
            }

            /**
             * @brief Cria e retorna uma Condition do tipo DISJUNCTION
             * 
             * @tparam PrT 
             * @tparam RT 
             * @tparam CmpOpT 
             * @param b_premise 
             * @return Condition& 
             */
            template <class PrT, typename RT, typename CmpOpT>
            Condition& operator ||(Premise<PrT, RT, CmpOpT>& b_premise)
            {
                if((this->mode == Condition::DISJUNCTION or this->mode == Condition::SINGLE) and !this->persistant)
                {
                    b_premise.insert(shared_from_this());

                    if(b_premise.getCurrentStatus() and !b_premise.isImpertinent())
                        update(false, b_premise.getCurrentStatus());

                    return *this;
                }
                else
                {
                    #ifdef USE_CUSTOM_SMART_PTRS
                        shared_ptr<Condition> condition(new Condition());
                    #else
                        shared_ptr<Condition> condition = std::make_shared<Condition>(*new Condition());
                    #endif // USE_CUSTOM_SMART_PTRS
                    condition->setQuantity(1);
                    condition->mode = Condition::DISJUNCTION;

                    this->insert(condition);
                    b_premise.insert(condition);

                    if(b_premise.getCurrentStatus() and !b_premise.isImpertinent())
                        condition->update(false, b_premise.getCurrentStatus());
                    if(this->current_status)
                        condition->update(false, this->current_status);
                    
                    return *condition;
                }
            }

            /**
             * @brief Cria e retorna uma Condition do tipo DISJUNCTION
             * 
             * @tparam PrT 
             * @tparam RT 
             * @tparam CmpOpT 
             * @param b_premise 
             * @return Condition& 
             */
            template <class PrT, typename RT, typename CmpOpT>
            Condition& operator ||(Premise<PrT, RT, CmpOpT>&& b_premise)
            {
                if((this->mode == Condition::DISJUNCTION or this->mode == Condition::SINGLE) and !this->persistant)
                {
                    b_premise.insert(this->shared_from_this());

                    if(b_premise.getCurrentStatus() and !b_premise.isImpertinent())
                        update(false, b_premise.getCurrentStatus());

                    return *this;
                }
                else
                {
                    #ifdef USE_CUSTOM_SMART_PTRS
                        shared_ptr<Condition> condition(new Condition());
                    #else
                        shared_ptr<Condition> condition = std::make_shared<Condition>(*new Condition());
                    #endif // USE_CUSTOM_SMART_PTRS> condition = std::make_shared<Condition>(aux);
                    condition->setQuantity(1);
                    condition->mode = Condition::DISJUNCTION;

                    this->insert(condition);
                    b_premise.insert(condition);

                    if(b_premise.getCurrentStatus() and !b_premise.isImpertinent())
                        condition->update(false, b_premise.getCurrentStatus());
                    if(this->current_status)
                        condition->update(false, this->current_status);
                    
                    return *condition;
                }
            }
            
            Condition& operator &&(Condition& b_condition);
            Condition& operator &&(Condition&& b_condition);
            Condition& operator ||(Condition& b_condition);
            Condition& operator ||(Condition&& b_condition);
        };
    } // namespace Core
    
}
#endif // !JUNOCPP_CONDITION_HPP