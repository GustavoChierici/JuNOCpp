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
        template<typename LT, typename RT, Comparison cmp_operator>
        class Premise;
        template<Comparison cmp_operator, typename LT, typename RT>
        auto make_premise(LT lhs, RT rhs, Utils::CustomString name);

        template<typename LT, typename RT, Comparison cmp_operator>
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
                    Utils::CustomString name = "UnnamedPremise"
            );

        public:
            Premise() = delete;
            Premise(Premise& rhs) = delete;
            Premise(Premise&& rhs) = delete;
            ~Premise();
            
            friend auto make_premise<cmp_operator>(LT lhs, RT rhs, Utils::CustomString name);

            const bool getCurrentStatus() const { return status; }

            void update(const bool renotify = false) override;

            void update(const bool renotify, const bool status) override {}

            void makeImpertinent() override;
            Premise& impertinentThis()
            {
                this->makeImpertinent();
                return *this;
            }
            void activate() override;
            void deactivate() override;

            template <class RLT, typename RPrRT, Comparison rPr_cmp_op>
            Condition& operator &&(Premise<RLT, RPrRT, rPr_cmp_op>& b_premise);
            template <class RLT, typename RPrRT, Comparison rPr_cmp_op>
            Condition& operator &&(Premise<RLT, RPrRT, rPr_cmp_op>&& b_premise);
            template <class RLT, typename RPrRT, Comparison rPr_cmp_op>
            Condition& operator ||(Premise<RLT, RPrRT, rPr_cmp_op>& b_premise);
            template <class RLT, typename RPrRT, Comparison rPr_cmp_op>
            Condition& operator ||(Premise<RLT, RPrRT, rPr_cmp_op>&& b_premise);

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
         * @tparam cmp_operator 
         * @param lhs 
         * @param rhs_val 
         * @param _op 
         * @param name 
         */
        template <typename LT, typename RT, Comparison cmp_operator>
        Premise<LT, RT, cmp_operator>::Premise(
            LT lhs,
            RT rhs_val, Utils::CustomString name
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
         * @tparam cmp_operator 
         */
        template <typename LT, typename RT, Comparison cmp_operator>
        Premise<LT, RT, cmp_operator>::~Premise()
        {
        }

        /**
         * @brief Atualiza o status da Premise após ela ser notificada por um Attribute
         * 
         * @tparam LT 
         * @tparam RT 
         * @tparam cmp_operator 
         * @param renotify 
         */
        template <typename LT, typename RT, Comparison cmp_operator>
        void Premise<LT, RT, cmp_operator>::update(const bool renotify)
        {
            if constexpr(cmp_operator == Comparison::NOT_EQUAL) {
                if constexpr(Utils::NOPTraits::is_attribute_v<LT>){
                    if constexpr(std::is_same_v<Utils::NOPTraits::is_attribute_t<LT>, RT>)
                    status = lhs_value->getValue() != rhs_value;
                    else if constexpr(Utils::NOPTraits::is_attribute_of_v<RT, Utils::NOPTraits::is_attribute_t<LT>>)
                        status = lhs_value->getValue() != rhs_value->getValue();
                    else if constexpr(Utils::NOPTraits::is_tuple_v<RT>)
                        status = lhs_value->getValue() != Utils::NOPTraits::eval(rhs_value);
                    else {
                        std::cout << "Invalid rhs_value type (RT)!" << std::endl;
                        exit(1);
                    }
                }
                else {
                    std::cout << "Invalid lhs_value type (LT)!" << std::endl;
                    exit(1);
                }
            } else if constexpr(cmp_operator == Comparison::EQUAL) {
                if constexpr(Utils::NOPTraits::is_attribute_v<LT>){
                    if constexpr(std::is_same_v<Utils::NOPTraits::is_attribute_t<LT>, RT>)
                    status = lhs_value->getValue() == rhs_value;
                    else if constexpr(Utils::NOPTraits::is_attribute_of_v<RT, Utils::NOPTraits::is_attribute_t<LT>>)
                        status = lhs_value->getValue() == rhs_value->getValue();
                    else if constexpr(Utils::NOPTraits::is_tuple_v<RT>)
                        status = lhs_value->getValue() == Utils::NOPTraits::eval(rhs_value);
                    else {
                        std::cout << "Invalid rhs_value type (RT)!" << std::endl;
                        exit(1);
                    }
                }
                else {
                    std::cout << "Invalid lhs_value type (LT)!" << std::endl;
                    exit(1);
                }
            } else if constexpr(cmp_operator == Comparison::GREATER) {
                if constexpr(Utils::NOPTraits::is_attribute_v<LT>){
                    if constexpr(std::is_same_v<Utils::NOPTraits::is_attribute_t<LT>, RT>)
                    status = lhs_value->getValue() > rhs_value;
                    else if constexpr(Utils::NOPTraits::is_attribute_of_v<RT, Utils::NOPTraits::is_attribute_t<LT>>)
                        status = lhs_value->getValue() > rhs_value->getValue();
                    else if constexpr(Utils::NOPTraits::is_tuple_v<RT>)
                        status = lhs_value->getValue() > Utils::NOPTraits::eval(rhs_value);
                    else {
                        std::cout << "Invalid rhs_value type (RT)!" << std::endl;
                        exit(1);
                    }
                }
                else {
                    std::cout << "Invalid lhs_value type (LT)!" << std::endl;
                    exit(1);
                }
            } else if constexpr(cmp_operator == Comparison::GREATER_EQUAL) {
                if constexpr(Utils::NOPTraits::is_attribute_v<LT>){
                    if constexpr(std::is_same_v<Utils::NOPTraits::is_attribute_t<LT>, RT>)
                    status = lhs_value->getValue() >= rhs_value;
                    else if constexpr(Utils::NOPTraits::is_attribute_of_v<RT, Utils::NOPTraits::is_attribute_t<LT>>)
                        status = lhs_value->getValue() >= rhs_value->getValue();
                    else if constexpr(Utils::NOPTraits::is_tuple_v<RT>)
                        status = lhs_value->getValue() >= Utils::NOPTraits::eval(rhs_value);
                    else {
                        std::cout << "Invalid rhs_value type (RT)!" << std::endl;
                        exit(1);
                    }
                }
                else {
                    std::cout << "Invalid lhs_value type (LT)!" << std::endl;
                    exit(1);
                }
            } else if constexpr(cmp_operator == Comparison::LESS) {
                if constexpr(Utils::NOPTraits::is_attribute_v<LT>){
                    if constexpr(std::is_same_v<Utils::NOPTraits::is_attribute_t<LT>, RT>)
                    status = lhs_value->getValue() < rhs_value;
                    else if constexpr(Utils::NOPTraits::is_attribute_of_v<RT, Utils::NOPTraits::is_attribute_t<LT>>)
                        status = lhs_value->getValue() < rhs_value->getValue();
                    else if constexpr(Utils::NOPTraits::is_tuple_v<RT>)
                        status = lhs_value->getValue() < Utils::NOPTraits::eval(rhs_value);
                    else {
                        std::cout << "Invalid rhs_value type (RT)!" << std::endl;
                        exit(1);
                    }
                }
                else {
                    std::cout << "Invalid lhs_value type (LT)!" << std::endl;
                    exit(1);
                }
            } else if constexpr(cmp_operator == Comparison::LESS_EQUAL) {
                if constexpr(Utils::NOPTraits::is_attribute_v<LT>){
                    if constexpr(std::is_same_v<Utils::NOPTraits::is_attribute_t<LT>, RT>)
                    status = lhs_value->getValue() <= rhs_value;
                    else if constexpr(Utils::NOPTraits::is_attribute_of_v<RT, Utils::NOPTraits::is_attribute_t<LT>>)
                        status = lhs_value->getValue() <= rhs_value->getValue();
                    else if constexpr(Utils::NOPTraits::is_tuple_v<RT>)
                        status = lhs_value->getValue() <= Utils::NOPTraits::eval(rhs_value);
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
         * @tparam cmp_operator 
         */
        template <typename LT, typename RT, Comparison cmp_operator>
        void Premise<LT, RT, cmp_operator>::makeImpertinent()
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

        template <typename LT, typename RT, Comparison cmp_operator>
        void Premise<LT, RT, cmp_operator>::activate()
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

        template <typename LT, typename RT, Comparison cmp_operator>
        void Premise<LT, RT, cmp_operator>::deactivate()
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
        template <typename LT, typename RT, Comparison cmp_operator>
        template <class RLT, typename RPrRT, Comparison rPr_cmp_op>
        Condition& Premise<LT, RT, cmp_operator>::operator &&(Premise<RLT, RPrRT, rPr_cmp_op>& b_premise)
        {
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
        template <typename LT, typename RT, Comparison cmp_operator>
        template <class RLT, typename RPrRT, Comparison rPr_cmp_op>
        Condition& Premise<LT, RT, cmp_operator>::operator &&(Premise<RLT, RPrRT, rPr_cmp_op>&& b_premise)
        {
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
        template <typename LT, typename RT, Comparison cmp_operator>
        template <class RLT, typename RPrRT, Comparison rPr_cmp_op>
        Condition& Premise<LT, RT, cmp_operator>::operator ||(Premise<RLT, RPrRT, rPr_cmp_op>& b_premise)
        {
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
        template <typename LT, typename RT, Comparison cmp_operator>
        template <class RLT, typename RPrRT, Comparison rPr_cmp_op>
        Condition& Premise<LT, RT, cmp_operator>::operator ||(Premise<RLT, RPrRT, rPr_cmp_op>&& b_premise)
        {
            return *make_condition(this, Condition::LogicalOperator::DISJUNCTION, &b_premise);
        }

        /**
         * Cria e retorna uma Condition do tipo CONJUNCTION
         * 
         * @tparam LT 
         * @param b_condition
         * @return Condition& 
         */
        template <typename LT, typename RT, Comparison cmp_operator>
        Condition& Premise<LT, RT, cmp_operator>::operator &&(Condition& b_condition)
        {
            return *make_condition(this, Condition::LogicalOperator::CONJUNCTION, &b_condition);
        }

        /**
         * Cria e retorna uma Condition do tipo CONJUNCTION
         * 
         * @tparam LT 
         * @param b_condition 
         * @return Condition& 
         */
        template <typename LT, typename RT, Comparison cmp_operator>
        Condition& Premise<LT, RT, cmp_operator>::operator &&(Condition&& b_condition)
        {
            return *make_condition(this, Condition::LogicalOperator::CONJUNCTION, &b_condition);
        }

        /**
         * Cria e retorna uma Condition do tipo DISJUNCTION
         * 
         * @tparam LT 
         * @param b_condition 
         * @return Condition& 
         */
        template <typename LT, typename RT, Comparison cmp_operator>
        Condition& Premise<LT, RT, cmp_operator>::operator ||(Condition& b_condition)
        {
            return *make_condition(this, Condition::LogicalOperator::DISJUNCTION, &b_condition);
        }

        /**
         * Cria e retorna uma Condition do tipo DISJUNCTION
         * 
         * @tparam LT  
         * @param b_condition 
         * @return Condition& 
         */
        template <typename LT, typename RT, Comparison cmp_operator>
        Condition& Premise<LT, RT, cmp_operator>::operator ||(Condition&& b_condition)
        {
            return *make_condition(this, Condition::LogicalOperator::DISJUNCTION, &b_condition);
        }

        /**
         * "Converte" a Premise numa Condition do tipo SINGLE
         * 
         * @tparam LT 
         * @return Condition& 
         */
        template <typename LT, typename RT, Comparison cmp_operator>
        Premise<LT, RT, cmp_operator>::operator Condition&()
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


        template<Comparison cmp_operator, typename LT, typename RT>
        auto make_premise(LT lhs, RT rhs, Utils::CustomString name)
        {
            #ifdef USE_CUSTOM_SMART_PTRS
                shared_ptr<Premise<LT, RT, cmp_operator>> premise
                    (new Premise<LT, RT, cmp_operator>
                        (lhs, rhs, name));
            #else
                shared_ptr<Premise<LT, RT, cmp_operator>> premise = 
                    std::make_shared<Premise<LT, RT, cmp_operator>>
                        (*new Premise<LT, RT, cmp_operator>(lhs, rhs, name));
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