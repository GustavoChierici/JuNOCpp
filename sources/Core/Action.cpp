#include "../../includes/Core/Action.hpp"
#include "../../includes/Core/Rule.hpp"

namespace JuNOCpp
{   
    namespace Core
    {
        /**
         * @brief Constutor
         * 
         */
        Action::Action(Utils::CustomString name) :
        Notifiable(name), 
        rule{nullptr}
        {
        }

        /**
         *@brief Destrutor
        * 
        */
        Action::~Action()
        {
        }

        /**
         *@brief Define a Rule da qual a Action pertence
        * 
        * @param b_rule 
        */
        void Action::setRule(Rule* b_rule)
        {
            this->rule = b_rule;
        }

        /**
         * Inicializa a cadeia de notificações secundária
         * 
         * @param renotify 
         */
        void Action::update(const bool renotify)
        {
            notify();
        }

        /**
         * Notifica as Instigations (e Conditions de Rules dependentes) ligadas à Action 
         * 
         * @param renotify 
         */
        void Action::notify(const bool renotify)
        {  
            #ifdef SHOW_NOP_LOGGER
                Utils::NOPLogger::Get().writeActionExecuting(name, this);

                Utils::NOPLogger::Get().incrementIdentation();
            #endif // SHOW_NOP_LOGGER

            #ifdef FASTER_DATA_STRUCTURES
                for(auto notifiable = notifiables.first; notifiable; notifiable = notifiable->next)
                {
                    auto cond = dynamic_cast<Condition*>(notifiable->element.get());
                    if(cond)
                    {
                        cond->update(false, true);
                        cond->update(false, false);
                    }
                    else
                        notifiable->element->update(renotify);
                }
            #elif defined(USE_RANGED_FOR)
                for(auto notifiable : notifiables)
                {
                    auto cond = dynamic_cast<Condition*>(notifiable.get());
                    if(cond)
                    {
                        cond->update(false, true);
                        cond->update(false, false);
                    }    
                    else
                        notifiable->update(renotify);
                }
            #else
                for(auto notifiable = notifiables.getFirst(); notifiable; notifiable = notifiable->next)
                {
                    auto cond = dynamic_cast<Condition*>(notifiable->element.get());
                    if(cond)
                    {
                        cond->update(false, true);
                        cond->update(false, false);
                    }
                    else
                        notifiable->element->update(renotify);
                }
            #endif // FASTER_DATA_STRUCTURES 

            #ifdef SHOW_NOP_LOGGER
                Utils::NOPLogger::Get().decrementIdentation();
            #endif // SHOW_NOP_LOGGER
        }

        /**
         * Desaprova as Conditions das Rules dependentes
         * 
         */
        void Action::disapproveDependantRules()
        {
            // auto cond = this->dependant_rules.getFirst();

            // while(cond)
            // {
            //     cond->getInfo()->update(false, false);
            //     cond = cond->getNext();
            // }
        }
    } // namespace Core
    
} // namespace JuNOCpp
