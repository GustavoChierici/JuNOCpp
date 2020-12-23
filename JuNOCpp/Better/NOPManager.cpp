#include "./NOPManager.hpp"
#include "./BetterCondition.hpp"
#include "./BetterAttribute.hpp"
#include "./BetterPremise.hpp"
#include "./BetterRule.hpp"
#include "./BetterAction.hpp"

namespace JuNOCpp
{
    List<std::shared_ptr<BetterRule>> NOPManager::rule_list;
    std::stack<std::shared_ptr<BetterRule>> NOPManager::rule_stack;

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
       if(!rule_stack.empty())
        {
            std::shared_ptr<BetterRule> master_rule = rule_stack.top();
            std::shared_ptr<BetterRule> dependant_rule = std::make_shared<BetterRule>(*new BetterRule());
            std::shared_ptr<BetterAction> dependant_rule_action = std::make_shared<BetterAction>(*new BetterAction());

            std::shared_ptr<BetterCondition> resultant_condition = std::make_shared<BetterCondition>(*new BetterCondition());
            resultant_condition->setQuantity(2);
            b_cond.insert(resultant_condition);
            master_rule->action->insert(resultant_condition);

            resultant_condition->insert(dependant_rule);
            dependant_rule->condition = resultant_condition.get();
            dependant_rule->action = dependant_rule_action.get();
            dependant_rule->insert(dependant_rule_action);
            dependant_rule_action->setBetterRule(dependant_rule.get());
            dependant_rule->condition->persistant = true;

            rule_stack.push(dependant_rule);
        }
        else
        {
            BetterRule rule;
            std::shared_ptr<BetterRule> shared_rule = std::make_shared<BetterRule>(rule);
            b_cond.insert(shared_rule);
            shared_rule->condition = &b_cond;

            BetterAction action;
            std::shared_ptr<BetterAction> shared_action = std::make_shared<BetterAction>(action);
            shared_rule->action = shared_action.get();
            shared_action->setBetterRule(shared_rule.get());
            
            shared_rule->insert(shared_action);
            shared_rule->condition->persistant = true;

            rule_list.insertInfo(shared_rule);
            rule_stack.push(shared_rule);
        }        
    }
    
    void NOPManager::CreateRule(BetterCondition& b_cond)
    {
        if(!rule_stack.empty())
        {
            std::shared_ptr<BetterRule> master_rule = rule_stack.top();
            std::shared_ptr<BetterRule> dependant_rule = std::make_shared<BetterRule>(*new BetterRule());
            std::shared_ptr<BetterAction> dependant_rule_action = std::make_shared<BetterAction>(*new BetterAction());

            std::shared_ptr<BetterCondition> resultant_condition = std::make_shared<BetterCondition>(*new BetterCondition());
            resultant_condition->setQuantity(2);
            b_cond.insert(resultant_condition);
            master_rule->action->insert(resultant_condition);

            resultant_condition->insert(dependant_rule);
            dependant_rule->condition = resultant_condition.get();
            dependant_rule->action = dependant_rule_action.get();
            dependant_rule->insert(dependant_rule_action);
            dependant_rule_action->setBetterRule(dependant_rule.get());
            dependant_rule->condition->persistant = true;

            master_rule->action->dependant_rules.insertInfo(resultant_condition.get());

            rule_stack.push(dependant_rule);
        }
        else
        {
            BetterRule rule;
            std::shared_ptr<BetterRule> shared_rule = std::make_shared<BetterRule>(rule);
            b_cond.insert(shared_rule);
            shared_rule->condition = &b_cond;

            BetterAction action;
            std::shared_ptr<BetterAction> shared_action = std::make_shared<BetterAction>(action);
            shared_rule->action = shared_action.get();
            shared_action->setBetterRule(shared_rule.get());
            
            shared_rule->insert(shared_action);
            shared_rule->condition->persistant = true;

            rule_list.insertInfo(shared_rule);
            rule_stack.push(shared_rule);
        }        
    }

    BetterRule& NOPManager::CreateRule(BetterCondition& b_cond, CustomString name)
    {
        if(!rule_stack.empty())
        {
            std::shared_ptr<BetterRule> master_rule = rule_stack.top();
            std::shared_ptr<BetterRule> dependant_rule = std::make_shared<BetterRule>(*new BetterRule());
            std::shared_ptr<BetterAction> dependant_rule_action = std::make_shared<BetterAction>(*new BetterAction());

            std::shared_ptr<BetterCondition> resultant_condition = std::make_shared<BetterCondition>(*new BetterCondition());
            resultant_condition->setQuantity(2);
            b_cond.insert(resultant_condition);
            master_rule->action->insert(resultant_condition);

            resultant_condition->insert(dependant_rule);
            dependant_rule->condition = resultant_condition.get();
            dependant_rule->action = dependant_rule_action.get();
            dependant_rule->insert(dependant_rule_action);
            dependant_rule_action->setBetterRule(dependant_rule.get());
            dependant_rule->condition->persistant = true;

            master_rule->action->dependant_rules.insertInfo(resultant_condition.get());

            rule_stack.push(dependant_rule);
            dependant_rule->name = name;
            
            return *dependant_rule;
        }
        else
        {
            BetterRule rule;
            std::shared_ptr<BetterRule> shared_rule = std::make_shared<BetterRule>(rule);
            b_cond.insert(shared_rule);
            shared_rule->condition = &b_cond;
            shared_rule->condition->persistant = true;

            BetterAction action;
            std::shared_ptr<BetterAction> shared_action = std::make_shared<BetterAction>(action);
            shared_rule->action = shared_action.get();
            shared_action->setBetterRule(shared_rule.get());
            
            shared_rule->insert(shared_action);

            rule_list.insertInfo(shared_rule);
            rule_stack.push(shared_rule);
            shared_rule->name = name;

            return *shared_rule;
        }        
    }

    void NOPManager::EndRule()
    {
        rule_stack.pop();
    }

    void NOPManager::CreateInstigation(std::function<void()> func)
    {
        BetterInstigation aux;

        std::shared_ptr<std::function<void()>> shared_method = std::make_shared<std::function<void()>>(func);
        std::shared_ptr<BetterInstigation> shared_instigation = std::make_shared<BetterInstigation>(aux);

        rule_stack.top()->action->insert(shared_instigation);

        shared_instigation->setMt(*shared_method);
    }
}