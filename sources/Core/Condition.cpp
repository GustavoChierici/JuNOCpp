#include "Condition.hpp"
#include "Premise.hpp"
#include "Rule.hpp"


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
         * @brief Analisa se a Condition foi aprovada ou não
         * (obs: essa sobrecarga é utilizada para renotificações)
         * 
         * @param renotify 
         */
        void Condition::update(const bool renotify)
        {
            if(count_approved == quantity)
                current_status = true;
            if(current_status != previous_status)
            {
                #ifdef SHOW_NOP_LOGGER
                    Utils::NOPLogger::Get().writeNotifying(name, this, current_status, renotify);
                    
                    Utils::NOPLogger::Get().incrementIdentation();
                #endif // SHOW_NOP_LOGGER
                previous_status = current_status;
                notify(renotify, current_status);

                #ifdef SHOW_NOP_LOGGER
                    Utils::NOPLogger::Get().decrementIdentation();
                #endif // SHOW_NOP_LOGGER
            }
            else if(renotify)
            {
                #ifdef SHOW_NOP_LOGGER
                    Utils::NOPLogger::Get().writeNotifying(name, this, current_status, renotify);
                    
                    Utils::NOPLogger::Get().incrementIdentation();
                #endif // SHOW_NOP_LOGGER
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
         * @brief Analisa se a Condition foi aprovada ou não
         * 
         * @param renotify 
         * @param status 
         */
        void Condition::update(const bool renotify, const bool status)
        {
            // if(status)
            // {
            //     this->count_approved++;

            //     if(this->count_approved == this->quantity)
            //     {
            //         this->current_status = true;
            //     }
            //     #ifdef SHOW_NOP_LOGGER
            //         Utils::NOPLogger::Get().writeIncrementCondition(name, this, count_approved, quantity);
            //     #endif // SHOW_NOP_LOGGER
            // }
            // else
            // {
            //     this->count_approved--;
            //     this->current_status = false;
            //     #ifdef SHOW_NOP_LOGGER
            //         Utils::NOPLogger::Get().writeDecrementCondition(name, this, count_approved, quantity);
            //     #endif // SHOW_NOP_LOGGER
            // }
            count_approved += (status * 2 - 1);

            current_status = count_approved >= quantity ? true : false;

            if(current_status != previous_status)
            {
                #ifdef SHOW_NOP_LOGGER
                    Utils::NOPLogger::Get().writeNotifying(name, this, current_status, renotify);
                    
                    Utils::NOPLogger::Get().incrementIdentation();
                #endif // SHOW_NOP_LOGGER
                previous_status = current_status;
                notify(renotify, current_status);

                #ifdef SHOW_NOP_LOGGER
                    Utils::NOPLogger::Get().decrementIdentation();
                #endif // SHOW_NOP_LOGGER
            }
            else if(renotify)
            {
                #ifdef SHOW_NOP_LOGGER
                    Utils::NOPLogger::Get().writeNotifying(name, this, current_status, renotify);
                    
                    Utils::NOPLogger::Get().incrementIdentation();
                #endif // SHOW_NOP_LOGGER=
                notify(renotify);

                #ifdef SHOW_NOP_LOGGER
                    Utils::NOPLogger::Get().decrementIdentation();
                #endif // SHOW_NOP_LOGGER
            }
            if(!impertinents.empty())
            {
                if(count_approved + count_impertinents == quantity)
                {
                    if(!is_impertinents_active)
                    {
                        #ifdef SHOW_NOP_LOGGER
                            Utils::NOPLogger::Get().writeActivatingImpertinents(name, this);

                            Utils::NOPLogger::Get().incrementIdentation();
                        #endif // SHOW_NOP_LOGGER
                        is_impertinents_active = true;
                        activateImpertinents();

                        #ifdef SHOW_NOP_LOGGER
                            Utils::NOPLogger::Get().decrementIdentation();
                        #endif // SHOW_NOP_LOGGER
                    }
                }
                else if(is_impertinents_active && count_approved + count_impertinents < quantity)
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
        }

        /**
         * Notifica as Premises impertinentes sobre sua ativação, para que então elas passem a ser notificadas pelos Attributes dos quais dependem
         * 
         */
        void Condition::activateImpertinents()
        {
            #ifdef FASTER_DATA_STRUCTURES
                for(auto impertinent = impertinents.first; impertinent; impertinent = impertinent->next)
                    impertinent->element->activate();
            #elif defined(USE_RANGED_FOR)
                for(auto impertinent : impertinents)
                    impertinent->activate();
            #else
                for(auto impertinent = impertinents.getFirst(); impertinent; impertinent = impertinent->next)
                    impertinent->element->activate();
            #endif // USE_FASTER_DATA_STRUCTURES
        }

        /**
         * Notifica as Premises impertinentes sobre sua desativação, para que parem de ser notificadas pelos Attributes dos quais dependem
         * 
         */
        void Condition::deactivateImpertinents()
        {
            #ifdef FASTER_DATA_STRUCTURES
                for(auto impertinent = impertinents.first; impertinent; impertinent = impertinent->next)
                    impertinent->element->deactivate();
            #elif defined(USE_RANGED_FOR)
                for(auto impertinent : impertinents)
                    impertinent->deactivate();
            #else
                for(auto impertinent = impertinents.getFirst(); impertinent; impertinent = impertinent->next)
                    impertinent->element->deactivate();
            #endif // USE_FASTER_DATA_STRUCTURES
        }

        /**
         * Define a quantidade de notificações true que a Condition precisa para ser aprovada
         * 
         * @param quant 
         */
        void Condition::setQuantity(const int quant)
        {
            quantity = quant;
        }

        /**
         * Cria e retorna uma Condition do tipo CONJUNCTION
         * 
         * @param b_condition 
         * @return Condition& 
         */
        Condition& Condition::operator &&(Condition& b_condition)
        {
            return *make_condition(this, Condition::LogicalOperator::CONJUNCTION, &b_condition);
        }

        /**
         * Cria e retorna uma Condition do tipo CONJUNCTION
         * 
         * @param b_condition 
         * @return Condition& 
         */
        Condition& Condition::operator &&(Condition&& b_condition)
        {
            return *make_condition(this, Condition::LogicalOperator::CONJUNCTION, &b_condition);
        }

        /**
         * Cria e retorna uma Condition do tipo DISJUNCTION
         * 
         * @param b_condition 
         * @return Condition& 
         */
        Condition& Condition::operator ||(Condition& b_condition)
        {
            return *make_condition(this, Condition::LogicalOperator::DISJUNCTION, &b_condition);
        }

        /**
         * Cria e retorna uma Condition do tipo DISJUNCTION
         * 
         * @param b_condition 
         * @return Condition& 
         */
        Condition& Condition::operator ||(Condition&& b_condition)
        {
            return *make_condition(this, Condition::LogicalOperator::DISJUNCTION, &b_condition);
        }
    } // namespace Core
} // namespace JuNOCpp