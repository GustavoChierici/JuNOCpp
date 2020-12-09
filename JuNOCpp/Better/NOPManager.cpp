#include "./NOPManager.hpp"
#include "./BetterCondition.hpp"
#include "./BetterAttribute.hpp"
#include "./BetterPremise.hpp"
#include "./BetterRule.hpp"
#include "./BetterAction.hpp"
#include "./BetterMethod.hpp"

namespace JuNOCpp
{
    List<std::shared_ptr<BetterRule>> NOPManager::rule_list;

    BetterRule* NOPManager::current_rule = nullptr;

    NOPManager::NOPManager()
    {
    }

    NOPManager& NOPManager::Get()
    {
        static NOPManager instance; 
        return instance;
    }

    void NOPManager::CreateRule(BetterCondition&& b_cond)
    {
        BetterRule rule;
        std::shared_ptr<BetterRule> shared_rule = std::make_shared<BetterRule>(rule);
        b_cond.insert(shared_rule);
        shared_rule->cond = &b_cond;

        BetterAction action;
        std::shared_ptr<BetterAction> shared_action = std::make_shared<BetterAction>(action);
        shared_rule->action = shared_action.get();
        shared_action->setBetterRule(shared_rule.get());
        
        rule_list.insertInfo(&shared_rule);

        current_rule = rule_list.getCurrent()->getInfo()->get();

        if(rule_list.getCurrent()->getNext() != nullptr)
            current_rule = rule_list.getCurrent()->getNext()->getInfo()->get();
    }
    
    void NOPManager::CreateRule(BetterCondition& b_cond)
    {
        BetterRule rule;
        std::shared_ptr<BetterRule> shared_rule = std::make_shared<BetterRule>(rule);
        b_cond.insert(shared_rule);
        shared_rule->cond = &b_cond;

        BetterAction action;
        std::shared_ptr<BetterAction> shared_action = std::make_shared<BetterAction>(action);
        shared_rule->action = shared_action.get();
        shared_action->setBetterRule(shared_rule.get());
        
        shared_rule->insert(shared_action);

        rule_list.insertInfo(&shared_rule);

        current_rule = rule_list.getCurrent()->getInfo()->get();

        if(rule_list.getCurrent()->getNext() != nullptr)
            current_rule = rule_list.getCurrent()->getNext()->getInfo()->get();
    }

    void NOPManager::CreateInstigation(std::function<void()> func)
    {
        BetterInstigation aux;

        std::shared_ptr<std::function<void()>> shared_method = std::make_shared<std::function<void()>>(func);
        std::shared_ptr<BetterInstigation> shared_instigation = std::make_shared<BetterInstigation>(aux);

        current_rule->action->insert(shared_instigation);

        shared_instigation->setMt(*shared_method);
    }
}