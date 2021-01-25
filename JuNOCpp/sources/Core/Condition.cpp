#include "../../includes/Core/Condition.hpp"
#include "../../includes/Core/Premise.hpp"
#include "../../includes/Core/Rule.hpp"


namespace JuNOCpp
{
    namespace Core
    {
        /**
         * Construtor
         * 
         */
        Condition::Condition(Utils::CustomString name) :
            Notifiable(name),
            quantity{0},
            count_approved{0},
            persistant{false},
            count_impertinents{0},
            previous_status{false},
            current_status{false}
        {  
        }

        /**
         * Destrutor
         * 
         */
        Condition::~Condition()
        {
        }

        /**
         * Sobrecarga do update inútil para uma Condition
         * 
         * @param renotify 
         */
        void Condition::update(const bool renotify)
        {
        }

        /**
         * Analisa se a Condition foi aprovada ou não
         * 
         * @param renotify 
         * @param status 
         */
        void Condition::update(const bool renotify, const bool status)
        {
            if(status)
            {
                this->count_approved++;

                if(this->count_approved == this->quantity)
                {
                    this->current_status = true;
                }
                #ifdef SHOW_NOP_LOGGER
                    Utils::NOPLogger::Get().writeIncrementCondition(name, this, count_approved, quantity);
                #endif // SHOW_NOP_LOGGER
            }
            else
            {
                this->count_approved--;
                this->current_status = false;
                #ifdef SHOW_NOP_LOGGER
                    Utils::NOPLogger::Get().writeDecrementCondition(name, this, count_approved, quantity);
                #endif // SHOW_NOP_LOGGER
            }
            if(this->current_status != this->previous_status)
            {
                #ifdef SHOW_NOP_LOGGER
                    Utils::NOPLogger::Get().writeNotifying(name, this, current_status, renotify);
                    
                    Utils::NOPLogger::Get().incrementIdentation();
                #endif // SHOW_NOP_LOGGER
                this->previous_status = this->current_status;
                notify(renotify);

                #ifdef SHOW_NOP_LOGGER
                    Utils::NOPLogger::Get().decrementIdentation();
                #endif // SHOW_NOP_LOGGER
            }
            if(this->count_approved + this->count_impertinents == this->quantity and !this->impertinents.empty())
            {
                if(!is_impertinents_active)
                {
                    #ifdef SHOW_NOP_LOGGER
                        Utils::NOPLogger::Get().writeActivatingImpertinents(name, this);

                        Utils::NOPLogger::Get().incrementIdentation();
                    #endif // SHOW_NOP_LOGGER
                    this->is_impertinents_active = true;
                    activateImpertinents();

                    #ifdef SHOW_NOP_LOGGER
                        Utils::NOPLogger::Get().decrementIdentation();
                    #endif // SHOW_NOP_LOGGER
                }
            }
            else if(is_impertinents_active)
            {
                #ifdef SHOW_NOP_LOGGER
                    Utils::NOPLogger::Get().writeDeactivatingImpertinents(name, this);

                    Utils::NOPLogger::Get().incrementIdentation();
                #endif // SHOW_NOP_LOGGER

                is_impertinents_active = false;
                deactivateImpertinents();

                #ifdef SHOW_NOP_LOGGER
                    Utils::NOPLogger::Get().decrementIdentation();
                #endif // SHOW_NOP_LOGGER
            }
        }

        /**
         * Notifica as demais Conditions e Rules que dependem da Condition
         * 
         * @param renotify 
         */
        void Condition::notify(const bool renotify)
        {
            // auto aux = this->notifiables.getFirst();

            // while(aux)
            // {
            //     auto cond = dynamic_cast<Condition*>(aux->getInfo().get());
            //     if(cond)
            //         cond->update(renotify, this->current_status);
            //     else if(this->current_status)
            //         aux->getInfo()->update(renotify);

            //     aux = aux->getNext();
            // }

            #ifdef FASTER_DATA_STRUCTURES
                for(auto notifiable = notifiables.first; notifiable; notifiable = notifiable->next)
                {
                    #ifdef SHOW_NOP_LOGGER
                        Utils::NOPLogger::Get().writeNotification(notifiable->element->getName(), notifiable->element.get());

                        Utils::NOPLogger::Get().incrementIdentation();
                    #endif // SHOW_NOP_LOGGER

                    auto cond = dynamic_cast<Condition*>(notifiable->element.get());
                    if(cond)
                        cond->update(renotify, this->current_status);
                    else if(this->current_status)
                        notifiable->element->update(renotify);

                    #ifdef SHOW_NOP_LOGGER
                        Utils::NOPLogger::Get().decrementIdentation();
                    #endif // SHOW_NOP_LOGGER
                }
            #elif defined(USE_RANGED_FOR)
                for(auto notifiable : notifiables)
                {
                    #ifdef SHOW_NOP_LOGGER
                        Utils::NOPLogger::Get().writeNotification(notifiable->name, notifiable.get());

                        Utils::NOPLogger::Get().incrementIdentation();
                    #endif // SHOW_NOP_LOGGER

                    auto cond = dynamic_cast<Condition*>(notifiable.get());
                    if(cond)
                        cond->update(renotify, this->current_status);
                    else if(this->current_status)
                        notifiable->update(renotify);
                    
                    #ifdef SHOW_NOP_LOGGER
                        Utils::NOPLogger::Get().decrementIdentation();
                    #endif // SHOW_NOP_LOGGER

                }
            #else
                for(auto notifiable = notifiables.getFirst(); notifiable; notifiable = notifiable->next)
                {
                    #ifdef SHOW_NOP_LOGGER
                        Utils::NOPLogger::Get().writeNotification(notifiable->element->name, notifiable->element.get());

                        Utils::NOPLogger::Get().incrementIdentation();
                    #endif // SHOW_NOP_LOGGER

                    auto cond = dynamic_cast<Condition*>(notifiable->element.get());
                    if(cond)
                        cond->update(renotify, this->current_status);
                    else if(this->current_status)
                        notifiable->element->update(renotify);

                    #ifdef SHOW_NOP_LOGGER
                        Utils::NOPLogger::Get().decrementIdentation();
                    #endif // SHOW_NOP_LOGGER
                }
            #endif // FASTER_DATA_STRUCTURES    
        }

        /**
         * Notifica as Premises impertinentes sobre sua ativação, para que então elas passem a ser notificadas pelos Attributes dos quais dependem
         * 
         */
        void Condition::activateImpertinents()
        {
            // auto aux = this->impertinents.getFirst();

            // while(aux)
            // {
            //     aux->getInfo()->activate();

            //     aux = aux->getNext();
            // }

            for(auto impertinent : impertinents)
                impertinent->activate();
        }

        /**
         * Notifica as Premises impertinentes sobre sua desativação, para que parem de ser notificadas pelos Attributes dos quais dependem
         * 
         */
        void Condition::deactivateImpertinents()
        {
            // auto aux = this->impertinents.getFirst();

            // while(aux)
            // {
            //     aux->getInfo()->deactivate();

            //     aux = aux->getNext();
            // }

            for(auto impertinent : impertinents)
                impertinent->deactivate();
        }

        /**
         * Define a quantidade de notificações true que a Condition precisa para ser aprovada
         * 
         * @param quant 
         */
        void Condition::setQuantity(const int quant)
        {
            this->quantity = quant;
        }

        /**
         * Cria e retorna uma Condition do tipo CONJUNCTION
         * 
         * @param b_condition 
         * @return Condition& 
         */
        Condition& Condition::operator &&(Condition& b_condition)
        {
            if((b_condition.mode == Condition::CONJUNCTION or b_condition.mode == Condition::SINGLE)
            and (this->mode == Condition::CONJUNCTION or this->mode == Condition::SINGLE) 
            and !b_condition.persistant and !this->persistant)
            {
                b_condition.insert(this->shared_from_this());
                this->setQuantity(this->quantity + 1);

                return *this;
            }
            else
            {
                shared_ptr<Condition> condition(new Condition());

                // Condition aux;

                // shared_ptr<Condition> condition = std::make_shared<Condition>(aux);
                condition->setQuantity(2);
                condition->mode = Condition::CONJUNCTION;

                this->insert(condition);
                b_condition.insert(condition);
                
                return *condition;
            }
        }

        /**
         * Cria e retorna uma Condition do tipo CONJUNCTION
         * 
         * @param b_condition 
         * @return Condition& 
         */
        Condition& Condition::operator &&(Condition&& b_condition)
        {
            if((b_condition.mode == Condition::CONJUNCTION or b_condition.mode == Condition::SINGLE)
            and (this->mode == Condition::CONJUNCTION or this->mode == Condition::SINGLE) 
            and !b_condition.persistant and !this->persistant)
            {
                b_condition.insert(this->shared_from_this());
                this->setQuantity(this->quantity + 1);

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
                b_condition.insert(condition);
                
                return *condition;
            }
        }

        /**
         * Cria e retorna uma Condition do tipo DISJUNCTION
         * 
         * @param b_condition 
         * @return Condition& 
         */
        Condition& Condition::operator ||(Condition& b_condition)
        {
            if((b_condition.mode == Condition::DISJUNCTION or b_condition.mode == Condition::SINGLE)
            and (this->mode == Condition::DISJUNCTION or this->mode == Condition::SINGLE) 
            and !b_condition.persistant and !this->persistant)
            {
                b_condition.insert(this->shared_from_this());

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
                b_condition.insert(condition);
                
                return *condition;
            }
        }

        /**
         * Cria e retorna uma Condition do tipo DISJUNCTION
         * 
         * @param b_condition 
         * @return Condition& 
         */
        Condition& Condition::operator ||(Condition&& b_condition)
        {
            if((b_condition.mode == Condition::DISJUNCTION or b_condition.mode == Condition::SINGLE)
            and (this->mode == Condition::DISJUNCTION or this->mode == Condition::SINGLE) 
            and !b_condition.persistant and !this->persistant)
            {
                b_condition.insert(this->shared_from_this());

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
                b_condition.insert(condition);
                
                return *condition;
            }
        }
    } // namespace Core
} // namespace JuNOCpp