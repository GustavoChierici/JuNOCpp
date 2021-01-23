#include "./BetterAction.hpp"
#include "./BetterRule.hpp"

namespace JuNOCpp
{   
    /**
     * @brief Constutor
     * 
     */
    BetterAction::BetterAction(Utils::CustomString name) :
    Notifiable(name), 
    rule{nullptr}
    {
    }

    /**
     *@brief Destrutor
     * 
     */
    BetterAction::~BetterAction()
    {
    }

    /**
     *@brief Define a Rule da qual a Action pertence
     * 
     * @param b_rule 
     */
    void BetterAction::setBetterRule(BetterRule* b_rule)
    {
        this->rule = b_rule;
    }

    /**
     * Inicializa a cadeia de notificações secundária
     * 
     * @param renotify 
     */
    void BetterAction::update(const bool renotify)
    {
        notify();
    }

    /**
     * Notifica as Instigations (e Conditions de Rules dependentes) ligadas à Action 
     * 
     * @param renotify 
     */
    void BetterAction::notify(const bool renotify)
    {  
        #ifdef SHOW_NOP_LOGGER
            Utils::NOPLogger::Get().writeActionExecuting(name, this);

            Utils::NOPLogger::Get().incrementIdentation();
        #endif // SHOW_NOP_LOGGER

        #ifdef FASTER_DATA_STRUCTURES
            for(auto notifiable = notifiables.first; notifiable; notifiable = notifiable->next)
            {
                auto cond = dynamic_cast<BetterCondition*>(notifiable->element.get());
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
                auto cond = dynamic_cast<BetterCondition*>(notifiable.get());
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
                auto cond = dynamic_cast<BetterCondition*>(notifiable->element.get());
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
    void BetterAction::disapproveDependantRules()
    {
        // auto cond = this->dependant_rules.getFirst();

        // while(cond)
        // {
        //     cond->getInfo()->update(false, false);
        //     cond = cond->getNext();
        // }
    }
} // namespace JuNOCpp
