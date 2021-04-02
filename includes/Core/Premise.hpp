/**
 * @file Premise.hpp
 * @author Gustavo Brunholi Chierici (gustavobchierici@gmail.com)
 * @brief Header e implementação da classe de premissa do PON (Premise)
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef JUNOCPP_PREMISE_HPP
#define JUNOCPP_PREMISE_HPP
#include <iostream>
#include "Attribute.hpp"
#include "Condition.hpp"
#include "Impertinent.hpp"
#include "premise_traits.hpp"
namespace JuNOCpp
{
    namespace Core
    {
        template<typename LT, typename RT, typename CmpOpT>
        class Premise;
        template<typename LT, typename RT, typename CmpOpT>
        auto make_premise(LT lhs, CmpOpT comparison_operator, RT rhs, Utils::CustomString name = "UnnamedPremise");

        template<typename LT, typename RT, typename CmpOpT>
        class Premise: public Impertinent, public Notifier, public Notifiable
        {
        friend class Condition;
        private:
            LT lhs_value;
            RT rhs_value;
            bool status;
            bool previous_status;

        private:
            Premise(LT lhs, 
                    RT rhs,
                    CmpOpT _op,
                    Utils::CustomString name = "UnnamedPremise"
            );

        public:
            Premise() = delete;
            Premise(Premise& rhs) = delete;
            Premise(Premise&& rhs) = delete;
            ~Premise();
            
            friend auto make_premise<>(LT lhs, CmpOpT comparison_operator, RT rhs, Utils::CustomString name);

            const bool getCurrentStatus() const { return status; }

            void update(const bool renotify = false);

            void update(const bool renotify, const bool status) {}

            void makeImpertinent();
            Premise& impertinentThis()
            {
                this->makeImpertinent();
                return *this;
            }
            void activate() override;
            void deactivate() override;

            template <class RLT, typename RPrRT, typename RPrCmpOpT>
            Condition& operator &&(Premise<RLT, RPrRT, RPrCmpOpT>& b_premise);
            template <class RLT, typename RPrRT, typename RPrCmpOpT>
            Condition& operator &&(Premise<RLT, RPrRT, RPrCmpOpT>&& b_premise);
            template <class RLT, typename RPrRT, typename RPrCmpOpT>
            Condition& operator ||(Premise<RLT, RPrRT, RPrCmpOpT>& b_premise);
            template <class RLT, typename RPrRT, typename RPrCmpOpT>
            Condition& operator ||(Premise<RLT, RPrRT, RPrCmpOpT>&& b_premise);

            Condition& operator &&(Condition& b_condition);
            Condition& operator &&(Condition&& b_condition);
            Condition& operator ||(Condition& b_condition);
            Condition& operator ||(Condition&& b_condition);

            operator Condition&();
        };

        /**
         * @brief Construtor
         * 
         * @tparam LT 
         * @tparam RT 
         * @tparam CmpOpT 
         * @param lhs 
         * @param rhs_val 
         * @param _op 
         * @param name 
         */
        template <typename LT, typename RT, typename CmpOpT>
        Premise<LT, RT, CmpOpT>::Premise(
            LT lhs,
            RT rhs_val, CmpOpT _op, Utils::CustomString name
        ) : 
        Notifiable(name),
        lhs_value{lhs}, 
        rhs_value{rhs_val},
        status{false}, 
        previous_status{false}
        {
        }

        /**
         * @brief Destrutor
         * 
         * @tparam LT 
         * @tparam RT 
         * @tparam CmpOpT 
         */
        template <typename LT, typename RT, typename CmpOpT>
        Premise<LT, RT, CmpOpT>::~Premise()
        {
        }

        /**
         * @brief Atualiza o status da Premise após ela ser notificada por um Attribute
         * 
         * @tparam LT 
         * @tparam RT 
         * @tparam CmpOpT 
         * @param renotify 
         */
        template <typename LT, typename RT, typename CmpOpT>
        void Premise<LT, RT, CmpOpT>::update(const bool renotify)
        {
            if constexpr(std::is_same_v<CmpOpT, Utils::NOPTraits::not_equal_t>) {
                if constexpr(Utils::NOPTraits::is_attribute_v<LT>){
                    if constexpr(std::is_same_v<Utils::NOPTraits::is_attribute_t<LT>, RT>)
                    status = lhs_value->getCurrentStatus() != rhs_value;
                    else if constexpr(Utils::NOPTraits::is_attribute_of_v<RT, Utils::NOPTraits::is_attribute_t<LT>>)
                        status = lhs_value->getCurrentStatus() != rhs_value->getCurrentStatus();
                    else if constexpr(Utils::NOPTraits::is_tuple_v<RT>)
                        status = lhs_value->getCurrentStatus() != Utils::NOPTraits::eval(rhs_value);
                    else {
                        std::cout << "Invalid rhs_value type (RT)!" << std::endl;
                        exit(1);
                    }
                }
                else {
                    std::cout << "Invalid lhs_value type (LT)!" << std::endl;
                    exit(1);
                }
            } else if constexpr(std::is_same_v<CmpOpT, Utils::NOPTraits::equal_t>) {
                if constexpr(Utils::NOPTraits::is_attribute_v<LT>){
                    if constexpr(std::is_same_v<Utils::NOPTraits::is_attribute_t<LT>, RT>)
                    status = lhs_value->getCurrentStatus() == rhs_value;
                    else if constexpr(Utils::NOPTraits::is_attribute_of_v<RT, Utils::NOPTraits::is_attribute_t<LT>>)
                        status = lhs_value->getCurrentStatus() == rhs_value->getCurrentStatus();
                    else if constexpr(Utils::NOPTraits::is_tuple_v<RT>)
                        status = lhs_value->getCurrentStatus() == Utils::NOPTraits::eval(rhs_value);
                    else {
                        std::cout << "Invalid rhs_value type (RT)!" << std::endl;
                        exit(1);
                    }
                }
                else {
                    std::cout << "Invalid lhs_value type (LT)!" << std::endl;
                    exit(1);
                }
            } else if constexpr(std::is_same_v<CmpOpT, Utils::NOPTraits::greater_t>) {
                if constexpr(Utils::NOPTraits::is_attribute_v<LT>){
                    if constexpr(std::is_same_v<Utils::NOPTraits::is_attribute_t<LT>, RT>)
                    status = lhs_value->getCurrentStatus() > rhs_value;
                    else if constexpr(Utils::NOPTraits::is_attribute_of_v<RT, Utils::NOPTraits::is_attribute_t<LT>>)
                        status = lhs_value->getCurrentStatus() > rhs_value->getCurrentStatus();
                    else if constexpr(Utils::NOPTraits::is_tuple_v<RT>)
                        status = lhs_value->getCurrentStatus() > Utils::NOPTraits::eval(rhs_value);
                    else {
                        std::cout << "Invalid rhs_value type (RT)!" << std::endl;
                        exit(1);
                    }
                }
                else {
                    std::cout << "Invalid lhs_value type (LT)!" << std::endl;
                    exit(1);
                }
            } else if constexpr(std::is_same_v<CmpOpT, Utils::NOPTraits::greater_equal_t>) {
                if constexpr(Utils::NOPTraits::is_attribute_v<LT>){
                    if constexpr(std::is_same_v<Utils::NOPTraits::is_attribute_t<LT>, RT>)
                    status = lhs_value->getCurrentStatus() >= rhs_value;
                    else if constexpr(Utils::NOPTraits::is_attribute_of_v<RT, Utils::NOPTraits::is_attribute_t<LT>>)
                        status = lhs_value->getCurrentStatus() >= rhs_value->getCurrentStatus();
                    else if constexpr(Utils::NOPTraits::is_tuple_v<RT>)
                        status = lhs_value->getCurrentStatus() >= Utils::NOPTraits::eval(rhs_value);
                    else {
                        std::cout << "Invalid rhs_value type (RT)!" << std::endl;
                        exit(1);
                    }
                }
                else {
                    std::cout << "Invalid lhs_value type (LT)!" << std::endl;
                    exit(1);
                }
            } else if constexpr(std::is_same_v<CmpOpT, Utils::NOPTraits::less_t>) {
                if constexpr(Utils::NOPTraits::is_attribute_v<LT>){
                    if constexpr(std::is_same_v<Utils::NOPTraits::is_attribute_t<LT>, RT>)
                    status = lhs_value->getCurrentStatus() < rhs_value;
                    else if constexpr(Utils::NOPTraits::is_attribute_of_v<RT, Utils::NOPTraits::is_attribute_t<LT>>)
                        status = lhs_value->getCurrentStatus() < rhs_value->getCurrentStatus();
                    else if constexpr(Utils::NOPTraits::is_tuple_v<RT>)
                        status = lhs_value->getCurrentStatus() < Utils::NOPTraits::eval(rhs_value);
                    else {
                        std::cout << "Invalid rhs_value type (RT)!" << std::endl;
                        exit(1);
                    }
                }
                else {
                    std::cout << "Invalid lhs_value type (LT)!" << std::endl;
                    exit(1);
                }
            } else if constexpr(std::is_same_v<CmpOpT, Utils::NOPTraits::less_equal_t>) {
                if constexpr(Utils::NOPTraits::is_attribute_v<LT>){
                    if constexpr(std::is_same_v<Utils::NOPTraits::is_attribute_t<LT>, RT>)
                    status = lhs_value->getCurrentStatus() <= rhs_value;
                    else if constexpr(Utils::NOPTraits::is_attribute_of_v<RT, Utils::NOPTraits::is_attribute_t<LT>>)
                        status = lhs_value->getCurrentStatus() <= rhs_value->getCurrentStatus();
                    else if constexpr(Utils::NOPTraits::is_tuple_v<RT>)
                        status = lhs_value->getCurrentStatus() <= Utils::NOPTraits::eval(rhs_value);
                    else {
                        std::cout << "Invalid rhs_value type (RT)!" << std::endl;
                        exit(1);
                    }
                }
                else {
                    std::cout << "Invalid lhs_value type (LT)!" << std::endl;
                    exit(1);
                }
            } else {
                std::cout << "Invalid Comparison Operator Type (RT)!" << std::endl;
                exit(1);
            }

            if(status != previous_status)
            {
                #ifdef SHOW_NOP_LOGGER
                    Utils::NOPLogger::Get().writeNotifying(name, this, status, renotify);
                    
                    Utils::NOPLogger::Get().incrementIdentation();
                #endif // SHOW_NOP_LOGGER

                previous_status = status;
                notify(renotify, status);

                #ifdef SHOW_NOP_LOGGER
                    Utils::NOPLogger::Get().decrementIdentation();
                #endif // SHOW_NOP_LOGGER
            }
            else if(renotify)
            {
                #ifdef SHOW_NOP_LOGGER
                    Utils::NOPLogger::Get().writeNotifying(name, this, status, renotify);
                    
                    Utils::NOPLogger::Get().incrementIdentation();
                #endif // SHOW_NOP_LOGGER

                notify(renotify);

                #ifdef SHOW_NOP_LOGGER
                    Utils::NOPLogger::Get().decrementIdentation();
                #endif // SHOW_NOP_LOGGER
            }
        }

        /**
         * @brief Transforma a premissa em impertinente
         * 
         * @tparam LT 
         * @tparam RT 
         * @tparam CmpOpT 
         */
        template <typename LT, typename RT, typename CmpOpT>
        void Premise<LT, RT, CmpOpT>::makeImpertinent()
        { 
            impertinent = true; 

            if constexpr(Utils::NOPTraits::is_attribute_v<LT>)
            {
                lhs_value->addImpertinent(shared_from_this());
                lhs_value->remove(shared_from_this());
            }
            else if constexpr(Utils::NOPTraits::is_tuple_v<LT>)
            {
                Utils::NOPTraits::addImpertinent(lhs_value, shared_from_this());
                Utils::NOPTraits::removePremise(lhs_value, shared_from_this());
            }

            if constexpr(Utils::NOPTraits::is_attribute_v<RT>)
            {
                rhs_value->addImpertinent(shared_from_this());
                rhs_value->remove(shared_from_this());
            }
            else if constexpr(Utils::NOPTraits::is_tuple_v<RT>)
            {
                Utils::NOPTraits::addImpertinent(rhs_value, shared_from_this());
                Utils::NOPTraits::removePremise(rhs_value, shared_from_this());
            }

        }

        template <typename LT, typename RT, typename CmpOpT>
        void Premise<LT, RT, CmpOpT>::activate()
        {
            #ifdef SHOW_NOP_LOGGER
                Utils::NOPLogger::Get().writeImpertinentActivated(name, this);

                Utils::NOPLogger::Get().incrementIdentation(); 
            #endif // SHOW_NOP_LOGGER

            if constexpr(Utils::NOPTraits::is_attribute_v<LT>)
                lhs_value->insert(shared_from_this());
            else if constexpr(Utils::NOPTraits::is_tuple_v<LT>)
                Utils::NOPTraits::insertPremise(lhs_value, shared_from_this());

            if constexpr(Utils::NOPTraits::is_attribute_v<RT>)
                rhs_value->insert(shared_from_this());
            else if constexpr(Utils::NOPTraits::is_tuple_v<RT>)
                Utils::NOPTraits::insertPremise(rhs_value, shared_from_this());

            update();

            #ifdef SHOW_NOP_LOGGER
                Utils::NOPLogger::Get().decrementIdentation();
            #endif // SHOW_NOP_LOGGER 
        }

        template <typename LT, typename RT, typename CmpOpT>
        void Premise<LT, RT, CmpOpT>::deactivate()
        {
            #ifdef SHOW_NOP_LOGGER
                Utils::NOPLogger::Get().writeImpertinentDeactivated(name, this);

                Utils::NOPLogger::Get().incrementIdentation(); 
            #endif // SHOW_NOP_LOGGER

            lhs_value->remove(shared_from_this());
            if constexpr(Utils::NOPTraits::is_attribute_of_v<RT, LT>)
                rhs_value->remove(shared_from_this());
            else if constexpr(Utils::NOPTraits::is_tuple_v<RT>)
                Utils::NOPTraits::removePremise(rhs_value, shared_from_this());

            if(status)
            {
                status = false;
                previous_status = false;
                notify(false, false);
            }

            #ifdef SHOW_NOP_LOGGER
                Utils::NOPLogger::Get().decrementIdentation();
            #endif // SHOW_NOP_LOGGER 
        }

        /**
         * Cria e retorna uma Condition do tipo CONJUNCTION
         * 
         * @tparam LT 
         * @tparam OT 
         * @param b_premise 
         * @return Condition& 
         */
        template <typename LT, typename RT, typename CmpOpT>
        template <class RLT, typename RPrRT, typename RPrCmpOpT>
        Condition& Premise<LT, RT, CmpOpT>::operator &&(Premise<RLT, RPrRT, RPrCmpOpT>& b_premise)
        {
            // #ifdef USE_CUSTOM_SMART_PTRS
            //     shared_ptr<Condition> condition(new Condition());
            // #else
            //     shared_ptr<Condition> condition = std::make_shared<Condition>(*new Condition());
            // #endif // USE_CUSTOM_SMART_PTRS

            // condition->setQuantity(2);
            // condition->setMode(Condition::CONJUNCTION);

            // if(this->isImpertinent())
            // {
            //     condition->incCountImpertinents();
            //     condition->addImpertinent(this);
            // }
            // if(b_premise.isImpertinent())
            // {
            //     condition->incCountImpertinents();
            //     condition->addImpertinent(&b_premise);
            // }
            // // std::cout << condition->count_impertinents << std::endl;
            // this->insert(condition);
            // b_premise.insert(condition);

            // if(this->status and !this->impertinent)
            //     condition->update(false, this->status);
            // if(b_premise.getCurrentStatus() and !b_premise.isImpertinent())
            //     condition->update(false, b_premise.getCurrentStatus());
            //return *condition;
            return *make_condition(this, Condition::LogicalOperator::CONJUNCTION, &b_premise);
        }

        /**
         * Cria e retorna uma Condition do tipo CONJUNCTION
         * 
         * @tparam LT 
         * @tparam OT 
         * @param b_premise 
         * @return Condition& 
         */
        template <typename LT, typename RT, typename CmpOpT>
        template <class RLT, typename RPrRT, typename RPrCmpOpT>
        Condition& Premise<LT, RT, CmpOpT>::operator &&(Premise<RLT, RPrRT, RPrCmpOpT>&& b_premise)
        {
            // #ifdef USE_CUSTOM_SMART_PTRS
            //     shared_ptr<Condition> condition(new Condition());
            // #else
            //     shared_ptr<Condition> condition = std::make_shared<Condition>(*new Condition());
            // #endif // USE_CUSTOM_SMART_PTRS
            // condition->setQuantity(2);
            // condition->setMode(Condition::CONJUNCTION);

            // this->insert(condition);
            // b_premise.insert(condition);

            // if(this->status and !this->impertinent)
            //     condition->update(false, this->status);
            // if(b_premise.getCurrentStatus() and !b_premise.isImpertinent())
            //     condition->update(false, b_premise.getCurrentStatus());
            
            // return *condition;

             return *make_condition(this, Condition::LogicalOperator::CONJUNCTION, &b_premise);
        }

        /**
         * Cria e retorna uma Condition do tipo DISJUNCTION
         * 
         * @tparam LT 
         * @tparam OT 
         * @param b_premise 
         * @return Condition& 
         */
        template <typename LT, typename RT, typename CmpOpT>
        template <class RLT, typename RPrRT, typename RPrCmpOpT>
        Condition& Premise<LT, RT, CmpOpT>::operator ||(Premise<RLT, RPrRT, RPrCmpOpT>& b_premise)
        {
            // #ifdef USE_CUSTOM_SMART_PTRS
            //     shared_ptr<Condition> condition(new Condition());
            // #else
            //     shared_ptr<Condition> condition = std::make_shared<Condition>(*new Condition());
            // #endif // USE_CUSTOM_SMART_PTRS
            // condition->setQuantity(1);
            // condition->setMode(Condition::DISJUNCTION);

            // this->insert(condition);
            // b_premise.insert(condition);

            // if(this->status and !this->impertinent)
            //     condition->update(false, this->status);
            // if(b_premise.getCurrentStatus() and !b_premise.isImpertinent())
            //     condition->update(false, b_premise.getCurrentStatus());
            
            // return *condition;
             return *make_condition(this, Condition::LogicalOperator::DISJUNCTION, &b_premise);
        }

        /**
         * Cria e retorna uma Condition do tipo DISJUNCTION
         * 
         * @tparam LT 
         * @tparam OT 
         * @param b_premise 
         * @return Condition& 
         */
        template <typename LT, typename RT, typename CmpOpT>
        template <class RLT, typename RPrRT, typename RPrCmpOpT>
        Condition& Premise<LT, RT, CmpOpT>::operator ||(Premise<RLT, RPrRT, RPrCmpOpT>&& b_premise)
        {
            // #ifdef USE_CUSTOM_SMART_PTRS
            //     shared_ptr<Condition> condition(new Condition());
            // #else
            //     shared_ptr<Condition> condition = std::make_shared<Condition>(*new Condition());
            // #endif // USE_CUSTOM_SMART_PTRS
            // condition->setQuantity(1);
            // condition->setMode(Condition::DISJUNCTION);

            // this->insert(condition);
            // b_premise.insert(condition);

            // if(this->status and !this->impertinent)
            //     condition->update(false, this->status);
            // if(b_premise.getCurrentStatus() and !b_premise.isImpertinent())
            //     condition->update(false, b_premise.getCurrentStatus());
            
            // return *condition;

             return *make_condition(this, Condition::LogicalOperator::DISJUNCTION, &b_premise);
        }

        /**
         * Cria e retorna uma Condition do tipo CONJUNCTION
         * 
         * @tparam LT 
         * @param b_condition
         * @return Condition& 
         */
        template <typename LT, typename RT, typename CmpOpT>
        Condition& Premise<LT, RT, CmpOpT>::operator &&(Condition& b_condition)
        {
            // if((b_condition.getMode() == Condition::CONJUNCTION or b_condition.getMode() == Condition::SINGLE) and !b_condition.isPersistant())
            // {
            //     this->insert(b_condition.shared_from_this());
            //     b_condition.incQuantity();

            //     if(this->status and !this->impertinent)
            //         b_condition.update(false, this->status);
                
            //     return b_condition;
            // }
            // else
            // {
            //     #ifdef USE_CUSTOM_SMART_PTRS
            //         shared_ptr<Condition> condition(new Condition());
            //     #else
            //         shared_ptr<Condition> condition = std::make_shared<Condition>(*new Condition());
            //     #endif // USE_CUSTOM_SMART_PTRS
            //     condition->setQuantity(2);
            //     condition->setMode(Condition::CONJUNCTION);

            //     this->insert(condition);
            //     b_condition.insert(condition);

            //     if(this->status and !this->impertinent)
            //         condition->update(false, this->status);
            //     if(b_condition.getCurrentStatus())
            //         condition->update(false, b_condition.getCurrentStatus());
                
                
            //     return *condition;
            // }
            return *make_condition(this, Condition::LogicalOperator::CONJUNCTION, &b_condition);
        }

        /**
         * Cria e retorna uma Condition do tipo CONJUNCTION
         * 
         * @tparam LT 
         * @param b_condition 
         * @return Condition& 
         */
        template <typename LT, typename RT, typename CmpOpT>
        Condition& Premise<LT, RT, CmpOpT>::operator &&(Condition&& b_condition)
        {
            // if((b_condition.mode == Condition::CONJUNCTION or b_condition.mode == Condition::SINGLE) and !b_condition.isPersistant())
            // {
            //     this->insert(b_condition.shared_from_this());
            //     b_condition.incQuantity();

            //     if(this->status and !this->impertinent)
            //         b_condition.update(false, this->status);
                
            //     return b_condition;
            // }
            // else
            // {
            //     #ifdef USE_CUSTOM_SMART_PTRS
            //         shared_ptr<Condition> condition(new Condition());
            //     #else
            //         shared_ptr<Condition> condition = std::make_shared<Condition>(*new Condition());
            //     #endif // USE_CUSTOM_SMART_PTRS
            //     condition->setQuantity(2);
            //     condition->setMode(Condition::CONJUNCTION);

            //     this->insert(condition);
            //     b_condition.insert(condition);

            //     if(this->status and !this->impertinent)
            //         condition->update(false, this->status);
            //     if(b_condition.getCurrentStatus())
            //         condition->update(false, b_condition.getCurrentStatus());
                
            //     return *condition;
            // }
            return *make_condition(this, Condition::LogicalOperator::CONJUNCTION, &b_condition);
        }

        /**
         * Cria e retorna uma Condition do tipo DISJUNCTION
         * 
         * @tparam LT 
         * @param b_condition 
         * @return Condition& 
         */
        template <typename LT, typename RT, typename CmpOpT>
        Condition& Premise<LT, RT, CmpOpT>::operator ||(Condition& b_condition)
        {
            // if ((b_condition.getMode() == Condition::DISJUNCTION or b_condition.getMode() == Condition::SINGLE) and !b_condition.isPersistant())
            // {
            //     this->insert(b_condition.shared_from_this());

            //     if(this->status and !this->impertinent)
            //         b_condition.update(false, this->status);

            //     return b_condition;
            // }
            // else
            // {
            //     #ifdef USE_CUSTOM_SMART_PTRS
            //         shared_ptr<Condition> condition(new Condition());
            //     #else
            //         shared_ptr<Condition> condition = std::make_shared<Condition>(*new Condition());
            //     #endif // USE_CUSTOM_SMART_PTRS
            //     condition->setQuantity(1);
            //     condition->setMode(Condition::DISJUNCTION);

            //     this->insert(condition);
            //     b_condition.insert(condition);

            //     if(this->status and !this->impertinent)
            //         condition->update(false, this->status);
            //     if(b_condition.getCurrentStatus())
            //         condition->update(false, b_condition.getCurrentStatus());
                
            //     return *condition;
            // }
            return *make_condition(this, Condition::LogicalOperator::DISJUNCTION, &b_condition);
        }

        /**
         * Cria e retorna uma Condition do tipo DISJUNCTION
         * 
         * @tparam LT  
         * @param b_condition 
         * @return Condition& 
         */
        template <typename LT, typename RT, typename CmpOpT>
        Condition& Premise<LT, RT, CmpOpT>::operator ||(Condition&& b_condition)
        {
            // if ((b_condition.mode == Condition::DISJUNCTION or b_condition.mode == Condition::SINGLE) and !b_condition.isPersistant())
            // {
            //     this->insert(b_condition.shared_from_this());

            //     if(this->status and !this->impertinent)
            //         b_condition.update(false, this->status);

            //     return b_condition;
            // }
            // else
            // {
            //     #ifdef USE_CUSTOM_SMART_PTRS
            //         shared_ptr<Condition> condition(new Condition());
            //     #else
            //         shared_ptr<Condition> condition = std::make_shared<Condition>(*new Condition());
            //     #endif // USE_CUSTOM_SMART_PTRS
            //     condition->setQuantity(1);
            //     condition->setMode(Condition::DISJUNCTION);

            //     this->insert(condition);
            //     b_condition.insert(condition);

            //     if(this->status and !this->impertinent)
            //         condition->update(false, this->status);
            //     if(b_condition.getCurrentStatus())
            //         condition->update(false, b_condition.getCurrentStatus());
                
            //     return *condition;
            // }

            return *make_condition(this, Condition::LogicalOperator::DISJUNCTION, &b_condition);
        }

        /**
         * "Converte" a Premise numa Condition do tipo SINGLE
         * 
         * @tparam LT 
         * @return Condition& 
         */
        template <typename LT, typename RT, typename CmpOpT>
        Premise<LT, RT, CmpOpT>::operator Condition&()
        {
            #ifdef USE_CUSTOM_SMART_PTRS
                shared_ptr<Condition> condition(new Condition());
            #else
                shared_ptr<Condition> condition = std::make_shared<Condition>(*new Condition());
            #endif // USE_CUSTOM_SMART_PTRS
            condition->setQuantity(1);
            condition->setMode(Condition::SINGLE);

            this->insert(condition);

            if(this->status and !this->impertinent)
                condition->update(false, this->status);
            
            return *condition;
        }


        template<typename LT, typename RT, typename CmpOpT>
        auto make_premise(LT lhs, CmpOpT comparison_operator, RT rhs, Utils::CustomString name)
        {
            #ifdef USE_CUSTOM_SMART_PTRS
                shared_ptr<Premise<LT, RT, CmpOpT>> premise
                    (new Premise<LT, RT, CmpOpT>
                        (lhs, rhs, comparison_operator, name));
            #else
                shared_ptr<Premise<LT, RT, CmpOpT>> premise = 
                    std::make_shared<Premise<LT, RT, CmpOpT>>
                        (*new Premise<LT, RT, CmpOpT>(lhs, rhs, comparison_operator, name));
            #endif // USE_CUSTOM_SMART_PTRS

            if constexpr(Utils::NOPTraits::is_attribute_v<LT>)
                lhs->insert(premise);
            if constexpr(Utils::NOPTraits::is_attribute_v<RT>)
                rhs->insert(premise);
            else if constexpr(Utils::NOPTraits::is_tuple_v<RT>)
                Utils::NOPTraits::insertPremise(rhs, premise);

            premise->update();

            return premise;
        }
    } // namespace Core
}

#endif // !JUNOCPP_PREMISE_HPP