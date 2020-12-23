#include "./BetterAction.hpp"
#include "./BetterRule.hpp"

namespace JuNOCpp
{   
    BetterAction::BetterAction() : rule{nullptr}
    {
    }

    BetterAction::~BetterAction()
    {
    }

    void BetterAction::setBetterRule(BetterRule* b_rule)
    {
        this->rule = b_rule;
    }

    void BetterAction::update(const bool renotify)
    {
        notify();
    }

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
