#ifndef JUNOCPP_CONDITION_HPP
#define JUNOCPP_CONDITION_HPP

#include <iostream>
#include "Notifier.hpp"
#include "Impertinent.hpp"
#include "condition_traits.hpp"

namespace JuNOCpp
{
    namespace Core
    {
        template<typename LT, typename RT>
        Condition* make_condition(LT lhs, int op, RT rhs);

        // template<typename LT>
        // auto make_condition(LT lhs, int op, Condition* rhs);

        enum class Comparison;

        template<class PrT, typename RT, Comparison cmp_operator>
        class Premise;

        class Rule;
        class Condition: public Notifiable, public Notifier
        {
        template<class PrT, typename RT, Comparison cmp_operator>
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

            template<typename LT, typename RT>
            friend Condition* make_condition(LT lhs, int op, RT rhs);
            // template<typename LT>
            // friend auto make_condition(LT lhs, int op, Condition* rhs);

            template<typename PrT>
            friend shared_ptr<Condition> make_condition(PrT premise, int op);

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
            template <class PrT, typename RT, Comparison cmp_operator>
            Condition& operator &&(Premise<PrT, RT, cmp_operator>& b_premise)
            {
                return *make_condition(this, Condition::LogicalOperator::CONJUNCTION, &b_premise);
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
            template <class PrT, typename RT, Comparison cmp_operator>
            Condition& operator &&(Premise<PrT, RT, cmp_operator>&& b_premise)
            {
                return *make_condition(this, Condition::LogicalOperator::CONJUNCTION, &b_premise);
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
            template <class PrT, typename RT, Comparison cmp_operator>
            Condition& operator ||(Premise<PrT, RT, cmp_operator>& b_premise)
            {
                return *make_condition(this, Condition::LogicalOperator::DISJUNCTION, &b_premise);
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
            template <class PrT, typename RT, Comparison cmp_operator>
            Condition& operator ||(Premise<PrT, RT, cmp_operator>&& b_premise)
            {
                return *make_condition(this, Condition::LogicalOperator::DISJUNCTION, &b_premise);
            }
            
            Condition& operator &&(Condition& b_condition);
            Condition& operator &&(Condition&& b_condition);
            Condition& operator ||(Condition& b_condition);
            Condition& operator ||(Condition&& b_condition);
        };


         /**
         * @brief Recebe um par Pr-Pr, Pr-Cd, Cd-Pr, Cd-Cd, retorna uma Condition
         * composta pelo par
         * 
         * TODO: Quebrar em mais funcões
         * 
         * @tparam LT 
         * @tparam RT 
         * @param lhs 
         * @param op 
         * @param rhs 
         * @return shared_ptr<Condition>
         */
        template<typename LT, typename RT>
        Condition* make_condition(LT lhs, int op, RT rhs)
        {
            if constexpr(Utils::NOPTraits::is_condition_v<LT>) // Par Cd-?
            {
                if constexpr(Utils::NOPTraits::is_condition_v<RT>) // Par Cd-Cd
                {
                    if(op == Condition::CONJUNCTION)
                    {
                        if((lhs->mode == Condition::CONJUNCTION or lhs->mode == Condition::SINGLE)
                            and (rhs->mode == Condition::CONJUNCTION or rhs->mode == Condition::SINGLE) 
                            and !lhs->persistant and !rhs->persistant)
                        {
                            rhs->insert(lhs->shared_from_this());
                            lhs->incQuantity();

                            if(rhs->getCurrentStatus())
                                lhs->update(false, rhs->getCurrentStatus());

                            return lhs;
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

                            lhs->insert(condition);
                            rhs->insert(condition);

                            if(lhs->current_status)
                                condition->update(false, lhs->current_status);
                            if(rhs->getCurrentStatus())
                                condition->update(false, rhs->getCurrentStatus());
                            
                            return &*condition;
                        }
                    }
                    else if(op == Condition::DISJUNCTION)
                    {
                        if((rhs->mode == Condition::DISJUNCTION or rhs->mode == Condition::SINGLE)
                            and (lhs->mode == Condition::DISJUNCTION or lhs->mode == Condition::SINGLE) 
                            and !rhs->persistant and !lhs->persistant)
                        {
                            rhs->insert(lhs->shared_from_this());

                            if(rhs->getCurrentStatus())
                                lhs->update(false, rhs->getCurrentStatus());

                            return lhs;
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

                            lhs->insert(condition);
                            rhs->insert(condition);

                            if(lhs->current_status)
                                condition->update(false, lhs->current_status);
                            if(rhs->getCurrentStatus())
                                condition->update(false, rhs->getCurrentStatus());
                            
                            return &*condition;
                        }           
                    }
                    else
                    {
                        std::cout << "INVALID LOGICAL OPERATION!" << std::endl;
                        exit(1);
                    }
                }
                else // Par Cd-Pr
                {
                    if(op == Condition::CONJUNCTION)
                    {
                        if((lhs->mode == Condition::CONJUNCTION or lhs->mode == Condition::SINGLE) and !lhs->persistant)
                        {
                            rhs->insert(lhs->shared_from_this());
                            lhs->incQuantity();

                            if(rhs->getCurrentStatus() and !rhs->isImpertinent())
                                lhs->update(false, rhs->getCurrentStatus());

                            return lhs;
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

                            lhs->insert(condition);
                            rhs->insert(condition);

                            if(rhs->getCurrentStatus() and !rhs->isImpertinent())
                                condition->update(false, rhs->getCurrentStatus());
                            if(lhs->current_status)
                                condition->update(false, lhs->current_status);
                            
                            return &*condition;
                        }
                    }
                    else if(op == Condition::DISJUNCTION)
                    {
                        if((lhs->mode == Condition::DISJUNCTION or lhs->mode == Condition::SINGLE) and !lhs->persistant)
                        {
                            rhs->insert(lhs->shared_from_this());

                            if(rhs->isImpertinent())
                            {
                                lhs->addImpertinent(rhs);
                                lhs->incCountImpertinents();
                            }

                            if(rhs->getCurrentStatus() and !rhs->isImpertinent())
                                lhs->update(false, rhs->getCurrentStatus());

                            return lhs;
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

                            lhs->insert(condition);
                            rhs->insert(condition);

                            if(rhs->isImpertinent())
                            {
                                lhs->addImpertinent(rhs);
                                lhs->incCountImpertinents();
                            }

                            if(rhs->getCurrentStatus() and !rhs->isImpertinent())
                                condition->update(false, rhs->getCurrentStatus());
                            if(lhs->current_status)
                                condition->update(false, lhs->current_status);
                            
                            return &*condition;
                        }
                    }
                    else
                    {
                        std::cout << "INVALID LOGICAL OPERATION!" << std::endl;
                        exit(1);
                    }
                }
            }
            else // Par Pr-?
            {
                if constexpr(Utils::NOPTraits::is_condition_v<RT>) // Par Pr-Cd
                {
                    if(op == Condition::CONJUNCTION)
                    {
                        if((rhs->getMode() == Condition::CONJUNCTION or rhs->getMode() == Condition::SINGLE) and !rhs->isPersistant())
                        {
                            lhs->insert(rhs->shared_from_this());
                            rhs->incQuantity();

                            if(lhs->getCurrentStatus() and !lhs->isImpertinent())
                                rhs->update(false, lhs->getCurrentStatus());
                            
                            return rhs;                           
                        }
                        else
                        {
                            #ifdef USE_CUSTOM_SMART_PTRS
                                shared_ptr<Condition> condition(new Condition());
                            #else
                                shared_ptr<Condition> condition = std::make_shared<Condition>(*new Condition());
                            #endif // USE_CUSTOM_SMART_PTRS
                            condition->setQuantity(2);
                            condition->setMode(Condition::CONJUNCTION);

                            lhs->insert(condition);
                            rhs->insert(condition);

                            if(lhs->getCurrentStatus() and !lhs->isImpertinent())
                                condition->update(false, lhs->getCurrentStatus());
                            if(rhs->getCurrentStatus())
                                condition->update(false, rhs->getCurrentStatus());
                                                       
                            return &*condition;
                        }
                    }
                    else if (op == Condition::DISJUNCTION)
                    {
                        if ((rhs->getMode() == Condition::DISJUNCTION or rhs->getMode() == Condition::SINGLE) and !rhs->isPersistant())
                        {
                            lhs->insert(rhs->shared_from_this());

                            if(lhs->getCurrentStatus() and !lhs->isImpertinent())
                                rhs->update(false, lhs->getCurrentStatus());

                            return rhs;
                        }
                        else
                        {
                            #ifdef USE_CUSTOM_SMART_PTRS
                                shared_ptr<Condition> condition(new Condition());
                            #else
                                shared_ptr<Condition> condition = std::make_shared<Condition>(*new Condition());
                            #endif // USE_CUSTOM_SMART_PTRS
                            condition->setQuantity(1);
                            condition->setMode(Condition::DISJUNCTION);

                            lhs->insert(condition);
                            rhs->insert(condition);

                            if(lhs->getCurrentStatus() and !lhs->isImpertinent())
                                condition->update(false, lhs->getCurrentStatus());
                            if(rhs->getCurrentStatus())
                                condition->update(false, rhs->getCurrentStatus());
                            
                            return &*condition;
                        }
                    }
                    else
                    {
                        std::cout << "INVALID LOGICAL OPERATION!" << std::endl;
                        exit(1);
                    }
                }
                else // Par Pr-Pr
                {
                    if(op == Condition::CONJUNCTION)
                    {                    
                        #ifdef USE_CUSTOM_SMART_PTRS
                            shared_ptr<Condition> condition(new Condition());
                        #else
                            shared_ptr<Condition> condition = std::make_shared<Condition>(*new Condition());
                        #endif // USE_CUSTOM_SMART_PTRS

                        condition->setQuantity(2);
                        condition->setMode(Condition::CONJUNCTION);

                        if(lhs->isImpertinent())
                        {
                            condition->incCountImpertinents();
                            condition->addImpertinent(lhs);
                        }
                        if(rhs->isImpertinent())
                        {
                            condition->incCountImpertinents();
                            condition->addImpertinent(rhs);
                        }
                        // std::cout << condition->count_impertinents << std::endl;
                        lhs->insert(condition);
                        rhs->insert(condition);

                        if(lhs->getCurrentStatus() and !lhs->isImpertinent())
                            condition->update(false, lhs->getCurrentStatus());
                        if(rhs->getCurrentStatus() and !rhs->isImpertinent())
                            condition->update(false, rhs->getCurrentStatus());
                        
                        return &*condition;
                    }
                    else if(op == Condition::DISJUNCTION)
                    {
                        #ifdef USE_CUSTOM_SMART_PTRS
                            shared_ptr<Condition> condition(new Condition());
                        #else
                            shared_ptr<Condition> condition = std::make_shared<Condition>(*new Condition());
                        #endif // USE_CUSTOM_SMART_PTRS

                        condition->setQuantity(1);
                        condition->setMode(Condition::DISJUNCTION);

                        if(lhs->isImpertinent())
                        {
                            condition->incCountImpertinents();
                            condition->addImpertinent(lhs);
                        }
                        if(rhs->isImpertinent())
                        {
                            condition->incCountImpertinents();
                            condition->addImpertinent(rhs);
                        }
                        // std::cout << condition->count_impertinents << std::endl;
                        lhs->insert(condition);
                        rhs->insert(condition);

                        if(lhs->getCurrentStatus() and !lhs->isImpertinent())
                            condition->update(false, lhs->getCurrentStatus());
                        if(rhs->getCurrentStatus() and !rhs->isImpertinent())
                            condition->update(false, rhs->getCurrentStatus());
                        
                        return &*condition;
                    }
                    else 
                    {
                        std::cout << "ERROR!" << std::endl;
                        exit(1);
                    }
                }
            }
        }

    } // namespace Core
    
}
#endif // !JUNOCPP_CONDITION_HPP