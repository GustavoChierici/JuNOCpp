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
        template<class PrT, typename RT, typename CmpOpT>
        class Premise: public Impertinent, public Notifier, public Notifiable
        {
        friend class Condition;
        private:
            Attribute<PrT>* attr1;
            RT rhs_value;
            bool status;
            bool previous_status;

        public:
            Premise();
            Premise(Attribute<PrT>* at1, 
                    RT rhs,
                    CmpOpT _op,
                    Utils::CustomString name = "UnnamedPremise"
            );
            ~Premise();

            void setAttribute(Attribute<PrT>* b_attr1, RT rhs_val)
            {
                attr1 = b_attr1;
                rhs_value = rhs_val;
            }

            void referenceCondition(Condition* b_cond);

            void update(const bool renotify = false);

            void update(const bool renotify, const bool status) {}

            void makeImpertinent();
            void activate() override;
            void deactivate() override;

            template <class RPrT, typename RPrRT, typename RPrCmpOpT>
            Condition& operator &&(Premise<RPrT, RPrRT, RPrCmpOpT>& b_premise);
            template <class RPrT, typename RPrRT, typename RPrCmpOpT>
            Condition& operator &&(Premise<RPrT, RPrRT, RPrCmpOpT>&& b_premise);
            template <class RPrT, typename RPrRT, typename RPrCmpOpT>
            Condition& operator ||(Premise<RPrT, RPrRT, RPrCmpOpT>& b_premise);
            template <class RPrT, typename RPrRT, typename RPrCmpOpT>
            Condition& operator ||(Premise<RPrT, RPrRT, RPrCmpOpT>&& b_premise);

            Condition& operator &&(Condition& b_condition);
            Condition& operator &&(Condition&& b_condition);
            Condition& operator ||(Condition& b_condition);
            Condition& operator ||(Condition&& b_condition);

            operator Condition&();
        };

        /**
         * Construtor
         * 
         * @tparam PrT 
         */
        template <class PrT, typename RT, typename CmpOpT>
        Premise<PrT, RT, CmpOpT>::Premise() : 
        Notifiable("UnnamedPremise"),
        attr1{nullptr},
        status{false}, 
        previous_status{false}
        {
        }

        /**
         * @brief Construtor
         * 
         * @tparam PrT 
         * @tparam RT 
         * @tparam CmpOpT 
         * @param at1 
         * @param rhs_val 
         * @param _op 
         * @param name 
         */
        template <class PrT, typename RT, typename CmpOpT>
        Premise<PrT, RT, CmpOpT>::Premise(
            Attribute<PrT>* at1,
            RT rhs_val, CmpOpT _op, Utils::CustomString name
        ) : 
        Notifiable(name),
        attr1{at1}, 
        rhs_value{rhs_val},
        status{false}, 
        previous_status{false}
        {
        }

        /**
         * @brief Destrutor
         * 
         * @tparam PrT 
         * @tparam RT 
         * @tparam CmpOpT 
         */
        template <class PrT, typename RT, typename CmpOpT>
        Premise<PrT, RT, CmpOpT>::~Premise()
        {
        }

        /**
         * @brief Faz a ligação entre a Premise e a Condition que depende dela
         * 
         * @tparam PrT 
         * @tparam RT 
         * @tparam CmpOpT 
         * @param b_condition 
         */
        template <class PrT, typename RT, typename CmpOpT>
        void Premise<PrT, RT, CmpOpT>::referenceCondition(Condition* b_condition)
        {
            this->conditions.insertInfo(*b_condition);
        }

        /**
         * @brief Atualiza o status da Premise após ela ser notificada por um Attribute
         * 
         * @tparam PrT 
         * @tparam RT 
         * @tparam CmpOpT 
         * @param renotify 
         */
        template <class PrT, typename RT, typename CmpOpT>
        void Premise<PrT, RT, CmpOpT>::update(const bool renotify)
        {
            if constexpr(std::is_same_v<CmpOpT, Utils::NOPTraits::not_equal_t>) {
                if constexpr(std::is_same_v<Attribute<PrT>, Attribute<RT>>)
                    status = attr1->getCurrentStatus() != rhs_value;
                else if constexpr(std::is_same_v<Attribute<PrT>*, RT>)
                    status = attr1->getCurrentStatus() != rhs_value->getCurrentStatus();
                else if constexpr(Utils::NOPTraits::is_tuple_v<RT>)
                    status = attr1->getCurrentStatus() != Utils::NOPTraits::eval(rhs_value);
                else
                {
                    std::cout << "Invalid rhs_value type (RT)!" << std::endl;
                    exit(1);
                }
            } else if constexpr(std::is_same_v<CmpOpT, Utils::NOPTraits::equal_t>) {
                if constexpr(std::is_same_v<Attribute<PrT>, Attribute<RT>>)
                    status = attr1->getCurrentStatus() == rhs_value;
                else if constexpr(std::is_same_v<Attribute<PrT>*, RT>)
                    status = attr1->getCurrentStatus() == rhs_value->getCurrentStatus();
                else if constexpr(Utils::NOPTraits::is_tuple_v<RT>)
                    status = attr1->getCurrentStatus() == Utils::NOPTraits::eval(rhs_value);
                else
                {
                    std::cout << "Invalid rhs_value type (RT)!" << std::endl;
                    exit(1);
                }
            } else if constexpr(std::is_same_v<CmpOpT, Utils::NOPTraits::greater_t>) {
                if constexpr(std::is_same_v<Attribute<PrT>, Attribute<RT>>)
                    status = attr1->getCurrentStatus() > rhs_value;
                else if constexpr(std::is_same_v<Attribute<PrT>*, RT>)
                    status = attr1->getCurrentStatus() > rhs_value->getCurrentStatus();
                else if constexpr(Utils::NOPTraits::is_tuple_v<RT>)
                    status = attr1->getCurrentStatus() > Utils::NOPTraits::eval(rhs_value);
                else
                {
                    std::cout << "Invalid rhs_value type (RT)!" << std::endl;
                    exit(1);
                }
            } else if constexpr(std::is_same_v<CmpOpT, Utils::NOPTraits::greater_equal_t>) {
                if constexpr(std::is_same_v<Attribute<PrT>, Attribute<RT>>)
                    status = attr1->getCurrentStatus() >= rhs_value;
                else if constexpr(std::is_same_v<Attribute<PrT>*, RT>)
                    status = attr1->getCurrentStatus() >= rhs_value->getCurrentStatus();
                else if constexpr(Utils::NOPTraits::is_tuple_v<RT>)
                    status = attr1->getCurrentStatus() >= Utils::NOPTraits::eval(rhs_value);
                else
                {
                    std::cout << "Invalid rhs_value type (RT)!" << std::endl;
                    exit(1);
                }
            } else if constexpr(std::is_same_v<CmpOpT, Utils::NOPTraits::less_t>) {
                if constexpr(std::is_same_v<Attribute<PrT>, Attribute<RT>>)
                    status = attr1->getCurrentStatus() < rhs_value;
                else if constexpr(std::is_same_v<Attribute<PrT>*, RT>)
                    status = attr1->getCurrentStatus() < rhs_value->getCurrentStatus();
                else if constexpr(Utils::NOPTraits::is_tuple_v<RT>)
                    status = attr1->getCurrentStatus() < Utils::NOPTraits::eval(rhs_value);
                else
                {
                    std::cout << "Invalid rhs_value type (RT)!" << std::endl;
                    exit(1);
                }
            } else if constexpr(std::is_same_v<CmpOpT, Utils::NOPTraits::less_equal_t>) {
                if constexpr(std::is_same_v<Attribute<PrT>, Attribute<RT>>)
                    status = attr1->getCurrentStatus() <= rhs_value;
                else if constexpr(std::is_same_v<Attribute<PrT>*, RT>)
                    status = attr1->getCurrentStatus() <= rhs_value->getCurrentStatus();
                else if constexpr(Utils::NOPTraits::is_tuple_v<RT>)
                    status = attr1->getCurrentStatus() <= Utils::NOPTraits::eval(rhs_value);
                else
                {
                    std::cout << "Invalid rhs_value type (RT)!" << std::endl;
                    exit(1);
                }
            } else {
                std::cout << "Invalid Comparison Operator Type (RT)!" << std::endl;
                exit(1);
            }

            if(renotify || this->status != this->previous_status)
            {
                #ifdef SHOW_NOP_LOGGER
                    Utils::NOPLogger::Get().writeNotifying(name, this, status, renotify);
                    
                    Utils::NOPLogger::Get().incrementIdentation();
                #endif // SHOW_NOP_LOGGER

                this->previous_status = this->status;
                this->notify(renotify, this->status);

                #ifdef SHOW_NOP_LOGGER
                    Utils::NOPLogger::Get().decrementIdentation();
                #endif // SHOW_NOP_LOGGER
            }
        }

        /**
         * @brief Transforma a premissa em impertinente
         * 
         * @tparam PrT 
         * @tparam RT 
         * @tparam CmpOpT 
         */
        template <class PrT, typename RT, typename CmpOpT>
        void Premise<PrT, RT, CmpOpT>::makeImpertinent()
        { 
            impertinent = true; 

            attr1->addImpertinent(shared_from_this());
            attr1->remove(shared_from_this());

            if constexpr(Utils::NOPTraits::is_attribute_of_v<RT, PrT>)
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

        template <class PrT, typename RT, typename CmpOpT>
        void Premise<PrT, RT, CmpOpT>::activate()
        {
            #ifdef SHOW_NOP_LOGGER
                Utils::NOPLogger::Get().writeImpertinentActivated(name, this);

                Utils::NOPLogger::Get().incrementIdentation(); 
            #endif // SHOW_NOP_LOGGER

            attr1->insert(shared_from_this());
            if constexpr(Utils::NOPTraits::is_attribute_of_v<RT, PrT>)
                rhs_value->insert(shared_from_this());
            else if constexpr(Utils::NOPTraits::is_tuple_v<RT>)
                Utils::NOPTraits::insertPremise(rhs_value, shared_from_this());

            update();

            #ifdef SHOW_NOP_LOGGER
                Utils::NOPLogger::Get().decrementIdentation();
            #endif // SHOW_NOP_LOGGER 
        }

        template <class PrT, typename RT, typename CmpOpT>
        void Premise<PrT, RT, CmpOpT>::deactivate()
        {
            #ifdef SHOW_NOP_LOGGER
                Utils::NOPLogger::Get().writeImpertinentDeactivated(name, this);

                Utils::NOPLogger::Get().incrementIdentation(); 
            #endif // SHOW_NOP_LOGGER

            attr1->remove(shared_from_this());
            if constexpr(Utils::NOPTraits::is_attribute_of_v<RT, PrT>)
                rhs_value->remove(shared_from_this());
            else if constexpr(Utils::NOPTraits::is_tuple_v<RT>)
                Utils::NOPTraits::removePremise(rhs_value, shared_from_this());

            if(status)
            {
                status = false;
                notify(false, false);
            }

            #ifdef SHOW_NOP_LOGGER
                Utils::NOPLogger::Get().decrementIdentation();
            #endif // SHOW_NOP_LOGGER 
        }

        /**
         * Cria e retorna uma Condition do tipo CONJUNCTION
         * 
         * @tparam PrT 
         * @tparam OT 
         * @param b_premise 
         * @return Condition& 
         */
        template <class PrT, typename RT, typename CmpOpT>
        template <class RPrT, typename RPrRT, typename RPrCmpOpT>
        Condition& Premise<PrT, RT, CmpOpT>::operator &&(Premise<RPrT, RPrRT, RPrCmpOpT>& b_premise)
        {
            #ifdef USE_CUSTOM_SMART_PTRS
                shared_ptr<Condition> condition(new Condition());
            #else
                shared_ptr<Condition> condition = std::make_shared<Condition>(*new Condition());
            #endif // USE_CUSTOM_SMART_PTRS

            condition->setQuantity(2);
            condition->setMode(Condition::CONJUNCTION);

            if(this->isImpertinent())
            {
                condition->incCountImpertinents();
                condition->addImpertinent(this);
            }
            if(b_premise.isImpertinent())
            {
                condition->incCountImpertinents();
                condition->addImpertinent(&b_premise);
            }
            // std::cout << condition->count_impertinents << std::endl;
            this->insert(condition);
            b_premise.insert(condition);

            if(this->status and !this->impertinent)
                condition->update(false, this->status);
            if(b_premise.status and !b_premise.impertinent)
                condition->update(false, b_premise.status);
            
            return *condition;
        }

        /**
         * Cria e retorna uma Condition do tipo CONJUNCTION
         * 
         * @tparam PrT 
         * @tparam OT 
         * @param b_premise 
         * @return Condition& 
         */
        template <class PrT, typename RT, typename CmpOpT>
        template <class RPrT, typename RPrRT, typename RPrCmpOpT>
        Condition& Premise<PrT, RT, CmpOpT>::operator &&(Premise<RPrT, RPrRT, RPrCmpOpT>&& b_premise)
        {
            #ifdef USE_CUSTOM_SMART_PTRS
                shared_ptr<Condition> condition(new Condition());
            #else
                shared_ptr<Condition> condition = std::make_shared<Condition>(*new Condition());
            #endif // USE_CUSTOM_SMART_PTRS
            condition->setQuantity(2);
            condition->setMode(Condition::CONJUNCTION);

            this->insert(condition);
            b_premise.insert(condition);

            if(this->status and !this->impertinent)
                condition->update(false, this->status);
            if(b_premise.status and !b_premise.impertinent)
                condition->update(false, b_premise.status);
            
            return *condition;
        }

        /**
         * Cria e retorna uma Condition do tipo DISJUNCTION
         * 
         * @tparam PrT 
         * @tparam OT 
         * @param b_premise 
         * @return Condition& 
         */
        template <class PrT, typename RT, typename CmpOpT>
        template <class RPrT, typename RPrRT, typename RPrCmpOpT>
        Condition& Premise<PrT, RT, CmpOpT>::operator ||(Premise<RPrT, RPrRT, RPrCmpOpT>& b_premise)
        {
            #ifdef USE_CUSTOM_SMART_PTRS
                shared_ptr<Condition> condition(new Condition());
            #else
                shared_ptr<Condition> condition = std::make_shared<Condition>(*new Condition());
            #endif // USE_CUSTOM_SMART_PTRS
            condition->setQuantity(1);
            condition->setMode(Condition::DISJUNCTION);

            this->insert(condition);
            b_premise.insert(condition);

            if(this->status and !this->impertinent)
                condition->update(false, this->status);
            if(b_premise.status and !b_premise.impertinent)
                condition->update(false, b_premise.status);
            
            return *condition;
        }

        /**
         * Cria e retorna uma Condition do tipo DISJUNCTION
         * 
         * @tparam PrT 
         * @tparam OT 
         * @param b_premise 
         * @return Condition& 
         */
        template <class PrT, typename RT, typename CmpOpT>
        template <class RPrT, typename RPrRT, typename RPrCmpOpT>
        Condition& Premise<PrT, RT, CmpOpT>::operator ||(Premise<RPrT, RPrRT, RPrCmpOpT>&& b_premise)
        {
            #ifdef USE_CUSTOM_SMART_PTRS
                shared_ptr<Condition> condition(new Condition());
            #else
                shared_ptr<Condition> condition = std::make_shared<Condition>(*new Condition());
            #endif // USE_CUSTOM_SMART_PTRS
            condition->setQuantity(1);
            condition->setMode(Condition::DISJUNCTION);

            this->insert(condition);
            b_premise.insert(condition);

            if(this->status and !this->impertinent)
                condition->update(false, this->status);
            if(b_premise.status and !b_premise.impertinent)
                condition->update(false, b_premise.status);
            
            return *condition;
        }

        /**
         * Cria e retorna uma Condition do tipo CONJUNCTION
         * 
         * @tparam PrT 
         * @param b_condition
         * @return Condition& 
         */
        template <class PrT, typename RT, typename CmpOpT>
        Condition& Premise<PrT, RT, CmpOpT>::operator &&(Condition& b_condition)
        {
            if((b_condition.getMode() == Condition::CONJUNCTION or b_condition.getMode() == Condition::SINGLE) and !b_condition.isPersistant())
            {
                this->insert(b_condition.shared_from_this());
                b_condition.incQuantity();

                if(this->status and !this->impertinent)
                    b_condition.update(false, this->status);
                
                return b_condition;
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

                this->insert(condition);
                b_condition.insert(condition);

                if(this->status and !this->impertinent)
                    condition->update(false, this->status);
                if(b_condition.current_status)
                    condition->update(false, b_condition.current_status);
                
                
                return *condition;
            }
        }

        /**
         * Cria e retorna uma Condition do tipo CONJUNCTION
         * 
         * @tparam PrT 
         * @param b_condition 
         * @return Condition& 
         */
        template <class PrT, typename RT, typename CmpOpT>
        Condition& Premise<PrT, RT, CmpOpT>::operator &&(Condition&& b_condition)
        {
            if((b_condition.mode == Condition::CONJUNCTION or b_condition.mode == Condition::SINGLE) and !b_condition.isPersistant())
            {
                this->insert(b_condition.shared_from_this());
                b_condition.incQuantity();

                if(this->status and !this->impertinent)
                    b_condition.update(false, this->status);
                
                return b_condition;
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

                this->insert(condition);
                b_condition.insert(condition);

                if(this->status and !this->impertinent)
                    condition->update(false, this->status);
                if(b_condition.current_status)
                    condition->update(false, b_condition.current_status);
                
                return *condition;
            }
        }

        /**
         * Cria e retorna uma Condition do tipo DISJUNCTION
         * 
         * @tparam PrT 
         * @param b_condition 
         * @return Condition& 
         */
        template <class PrT, typename RT, typename CmpOpT>
        Condition& Premise<PrT, RT, CmpOpT>::operator ||(Condition& b_condition)
        {
            if ((b_condition.getMode() == Condition::DISJUNCTION or b_condition.getMode() == Condition::SINGLE) and !b_condition.isPersistant())
            {
                this->insert(b_condition.shared_from_this());

                if(this->status and !this->impertinent)
                    b_condition.update(false, this->status);

                return b_condition;
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

                this->insert(condition);
                b_condition.insert(condition);

                if(this->status and !this->impertinent)
                    condition->update(false, this->status);
                if(b_condition.current_status)
                    condition->update(false, b_condition.current_status);
                
                return *condition;
            }
        }

        /**
         * Cria e retorna uma Condition do tipo DISJUNCTION
         * 
         * @tparam PrT  
         * @param b_condition 
         * @return Condition& 
         */
        template <class PrT, typename RT, typename CmpOpT>
        Condition& Premise<PrT, RT, CmpOpT>::operator ||(Condition&& b_condition)
        {
            if ((b_condition.mode == Condition::DISJUNCTION or b_condition.mode == Condition::SINGLE) and !b_condition.isPersistant())
            {
                this->insert(b_condition.shared_from_this());

                if(this->status and !this->impertinent)
                    b_condition.update(false, this->status);

                return b_condition;
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

                this->insert(condition);
                b_condition.insert(condition);

                if(this->status and !this->impertinent)
                    condition->update(false, this->status);
                if(b_condition.current_status)
                    condition->update(false, b_condition.current_status);
                
                return *condition;
            }
        }

        /**
         * "Converte" a Premise numa Condition do tipo SINGLE
         * 
         * @tparam PrT 
         * @return JuNOCpp::Condition& 
         */
        template <class PrT, typename RT, typename CmpOpT>
        Premise<PrT, RT, CmpOpT>::operator JuNOCpp::Core::Condition&()
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
    } // namespace Core
}

#endif // !JUNOCPP_PREMISE_HPP