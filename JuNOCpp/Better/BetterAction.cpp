#include "./BetterAction.hpp"
#include "./BetterRule.hpp"

namespace JuNOCpp
{   
    /**
     * Constutor
     * 
     */
    BetterAction::BetterAction() : rule{nullptr}
    {
    }

    /**
     * Destrutor
     * 
     */
    BetterAction::~BetterAction()
    {
    }

    /**
     * Define a Rule da qual a Action pertence
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
        // for(auto notf : notfs)
        // {
        //     auto cond = dynamic_cast<BetterCondition*>(notf.get());
        //     if(cond)
        //     {
        //         cond->update(false, true);
        //         cond->update(false, false);
        //     }    
        //     else
        //         notf->update(renotify);
        // }

        auto aux = this->notifiables.getFirst();

        while(aux)
        {
            auto cond = dynamic_cast<BetterCondition*>(aux->getInfo().get());
            if(cond)
            {
                cond->update(false, true);
                cond->update(false, false);
            }    
            else
                aux->getInfo()->update(renotify);
            
            aux = aux->getNext();
        }
    }

    /**
     * Desaprova as Conditions das Rules dependentes
     * 
     */
    void BetterAction::disapproveDependantRules()
    {
        auto cond = this->dependant_rules.getFirst();

        while(cond)
        {
            cond->getInfo()->update(false, false);
            cond = cond->getNext();
        }
    }
} // namespace JuNOCpp
