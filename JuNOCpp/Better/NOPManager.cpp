#include "./NOPManager.hpp"
#include "./BetterCondition.hpp"
#include "./BetterAttribute.hpp"
#include "./BetterPremise.hpp"
#include "./BetterRule.hpp"
#include "./BetterAction.hpp"

namespace JuNOCpp
{
    List<shared_ptr<BetterRule>> NOPManager::rule_list;
    std::stack<shared_ptr<BetterRule>> NOPManager::rule_stack;
    BetterRule* NOPManager::current_rule = nullptr;

    /**
     * Construtor
     * 
     */
    NOPManager::NOPManager()
    {
    }

    /**
     * Acesso à instância do Singleton NOPManager
     * 
     * @return NOPManager& 
     */
    NOPManager& NOPManager::Get()
    {
        static NOPManager instance; 
        return instance;
    }

    /**
     * Cria uma Rule
     * 
     * @param b_cond 
     */
    void NOPManager::CreateRule(BetterCondition&& b_cond)
    {
       if(!rule_stack.empty())
        {
            shared_ptr<BetterRule> master_rule = rule_stack.top();

            #ifdef USE_CUSTOM_SMART_PTRS
                shared_ptr<BetterRule> dependant_rule(new BetterRule());
                shared_ptr<BetterAction> dependant_rule_action(new BetterAction());
                shared_ptr<BetterCondition> resultant_condition(new BetterCondition());
            #else
                shared_ptr<BetterRule> dependant_rule = std::make_shared<BetterRule>(*new BetterRule());
                shared_ptr<BetterAction> dependant_rule_action = std::make_shared<BetterAction>(*new BetterAction());
                shared_ptr<BetterCondition> resultant_condition = std::make_shared<BetterCondition>(*new BetterCondition());
            #endif // USE_CUSTOM_SMART_PTRS

            resultant_condition->setQuantity(2);
            b_cond.insert(resultant_condition);
            master_rule->action->insert(resultant_condition);

            resultant_condition->insert(dependant_rule);
            dependant_rule->condition = resultant_condition.get();
            dependant_rule->action = dependant_rule_action.get();
            dependant_rule->insert(dependant_rule_action);
            dependant_rule_action->setBetterRule(dependant_rule.get());
            dependant_rule->condition->makePersistant();

            rule_stack.push(dependant_rule);

            // shared_ptr<BetterRule> master_rule = rule_stack.top();
            // shared_ptr<BetterRule> dependant_rule = std::make_shared<BetterRule>(*new BetterRule());
            // shared_ptr<BetterAction> dependant_rule_action = std::make_shared<BetterAction>(*new BetterAction());

            // shared_ptr<BetterCondition> resultant_condition = std::make_shared<BetterCondition>(*new BetterCondition());
            // resultant_condition->setQuantity(2);
            // b_cond.insert(resultant_condition);
            // master_rule->action->insert(resultant_condition);

            // resultant_condition->insert(dependant_rule);
            // dependant_rule->condition = resultant_condition.get();
            // dependant_rule->action = dependant_rule_action.get();
            // dependant_rule->insert(dependant_rule_action);
            // dependant_rule_action->setBetterRule(dependant_rule.get());
            // dependant_rule->condition->makePersistant();

            // rule_stack.push(dependant_rule);
        }
        else
        {
            #ifdef USE_CUSTOM_SMART_PTRS
                shared_ptr<BetterRule> shared_rule(new BetterRule());
                shared_ptr<BetterAction> shared_action(new BetterAction());
            #else
                shared_ptr<BetterRule> shared_rule = std::make_shared<BetterRule>(*new BetterRule());
                shared_ptr<BetterAction> shared_action = std::make_shared<BetterAction>(*new BetterAction());
            #endif // USE_CUSTOM_SMART_PTRS

            b_cond.insert(shared_rule);
            shared_rule->condition = &b_cond;

            shared_rule->action = shared_action.get();
            shared_action->setBetterRule(shared_rule.get());
            
            shared_rule->insert(shared_action);
            shared_rule->condition->makePersistant();

            rule_list.insertInfo(shared_rule);
            rule_stack.push(shared_rule);

            // BetterRule rule;
            // shared_ptr<BetterRule> shared_rule = std::make_shared<BetterRule>(rule);
            // b_cond.insert(shared_rule);
            // shared_rule->condition = &b_cond;

            // BetterAction action;
            // shared_ptr<BetterAction> shared_action = std::make_shared<BetterAction>(action);
            // shared_rule->action = shared_action.get();
            // shared_action->setBetterRule(shared_rule.get());
            
            // shared_rule->insert(shared_action);
            // shared_rule->condition->makePersistant();

            // rule_list.insertInfo(shared_rule);
            // rule_stack.push(shared_rule);
        }        
    }
    
    /**
     * Cria uma Rule
     * 
     * @param b_cond 
     */
    void NOPManager::CreateRule(BetterCondition& b_cond)
    {
        if(!rule_stack.empty())
        {
            shared_ptr<BetterRule> master_rule = rule_stack.top();

            #ifdef USE_CUSTOM_SMART_PTRS
                shared_ptr<BetterRule> dependant_rule(new BetterRule());
                shared_ptr<BetterAction> dependant_rule_action(new BetterAction());
                shared_ptr<BetterCondition> resultant_condition(new BetterCondition());
            #else
                shared_ptr<BetterRule> dependant_rule = std::make_shared<BetterRule>(*new BetterRule());
                shared_ptr<BetterAction> dependant_rule_action = std::make_shared<BetterAction>(*new BetterAction());
                shared_ptr<BetterCondition> resultant_condition = std::make_shared<BetterCondition>(*new BetterCondition());
            #endif // USE_CUSTOM_SMART_PTRS

            resultant_condition->setQuantity(2);
            b_cond.insert(resultant_condition);
            master_rule->action->insert(resultant_condition);

            resultant_condition->insert(dependant_rule);
            dependant_rule->condition = resultant_condition.get();
            dependant_rule->action = dependant_rule_action.get();
            dependant_rule->insert(dependant_rule_action);
            dependant_rule_action->setBetterRule(dependant_rule.get());
            dependant_rule->condition->makePersistant();

            master_rule->action->dependant_rules.insertInfo(resultant_condition.get());

            rule_stack.push(dependant_rule);

            // shared_ptr<BetterRule> master_rule = rule_stack.top();
            // shared_ptr<BetterRule> dependant_rule = std::make_shared<BetterRule>(*new BetterRule());
            // shared_ptr<BetterAction> dependant_rule_action = std::make_shared<BetterAction>(*new BetterAction());

            // shared_ptr<BetterCondition> resultant_condition = std::make_shared<BetterCondition>(*new BetterCondition());
            // resultant_condition->setQuantity(2);
            // b_cond.insert(resultant_condition);
            // master_rule->action->insert(resultant_condition);

            // resultant_condition->insert(dependant_rule);
            // dependant_rule->condition = resultant_condition.get();
            // dependant_rule->action = dependant_rule_action.get();
            // dependant_rule->insert(dependant_rule_action);
            // dependant_rule_action->setBetterRule(dependant_rule.get());
            // dependant_rule->condition->makePersistant();

            // master_rule->action->dependant_rules.insertInfo(resultant_condition.get());

            // rule_stack.push(dependant_rule);
        }
        else
        {
            #ifdef USE_CUSTOM_SMART_PTRS
                shared_ptr<BetterRule> shared_rule(new BetterRule());
                shared_ptr<BetterAction> shared_action(new BetterAction());
            #else
                shared_ptr<BetterRule> shared_rule = std::make_shared<BetterRule>(*new BetterRule());
                shared_ptr<BetterAction> shared_action = std::make_shared<BetterAction>(*new BetterAction());
            #endif // USE_CUSTOM_SMART_PTRS

            b_cond.insert(shared_rule);
            shared_rule->condition = &b_cond;

            shared_rule->action = shared_action.get();
            shared_action->setBetterRule(shared_rule.get());
            
            shared_rule->insert(shared_action);
            shared_rule->condition->makePersistant();

            rule_list.insertInfo(shared_rule);
            rule_stack.push(shared_rule);

            // BetterRule rule;
            // shared_ptr<BetterRule> shared_rule = std::make_shared<BetterRule>(rule);
            // b_cond.insert(shared_rule);
            // shared_rule->condition = &b_cond;

            // BetterAction action;
            // shared_ptr<BetterAction> shared_action = std::make_shared<BetterAction>(action);
            // shared_rule->action = shared_action.get();
            // shared_action->setBetterRule(shared_rule.get());
            
            // shared_rule->insert(shared_action);
            // shared_rule->condition->makePersistant();

            // rule_list.insertInfo(shared_rule);
            // rule_stack.push(shared_rule);
        }        
    }

    /**
     * Cria e retorna uma Rule nomeada
     * 
     * @param b_cond 
     * @param name 
     * @return BetterRule& 
     */
    BetterRule& NOPManager::CreateRule(BetterCondition& b_cond, CustomString name)
    {
        if(!rule_stack.empty())
        {
            shared_ptr<BetterRule> master_rule = rule_stack.top();
            
            #ifdef USE_CUSTOM_SMART_PTRS
                shared_ptr<BetterRule> dependant_rule(new BetterRule());
                shared_ptr<BetterAction> dependant_rule_action(new BetterAction());
                shared_ptr<BetterCondition> resultant_condition(new BetterCondition());
            #else
                shared_ptr<BetterRule> dependant_rule = std::make_shared<BetterRule>(*new BetterRule());
                shared_ptr<BetterAction> dependant_rule_action = std::make_shared<BetterAction>(*new BetterAction());
                shared_ptr<BetterCondition> resultant_condition = std::make_shared<BetterCondition>(*new BetterCondition());
            #endif // USE_CUSTOM_SMART_PTRS

            resultant_condition->setQuantity(2);
            b_cond.insert(resultant_condition);
            master_rule->action->insert(resultant_condition);

            resultant_condition->insert(dependant_rule);
            dependant_rule->condition = resultant_condition.get();
            dependant_rule->action = dependant_rule_action.get();
            dependant_rule->insert(dependant_rule_action);
            dependant_rule_action->setBetterRule(dependant_rule.get());
            dependant_rule->condition->makePersistant();

            master_rule->action->dependant_rules.insertInfo(resultant_condition.get());

            rule_stack.push(dependant_rule);
            dependant_rule->name = name;
            
            return *dependant_rule;

            // shared_ptr<BetterRule> master_rule = rule_stack.top();
            // shared_ptr<BetterRule> dependant_rule = std::make_shared<BetterRule>(*new BetterRule());
            // shared_ptr<BetterAction> dependant_rule_action = std::make_shared<BetterAction>(*new BetterAction());

            // shared_ptr<BetterCondition> resultant_condition = std::make_shared<BetterCondition>(*new BetterCondition());
            // resultant_condition->setQuantity(2);
            // b_cond.insert(resultant_condition);
            // master_rule->action->insert(resultant_condition);

            // resultant_condition->insert(dependant_rule);
            // dependant_rule->condition = resultant_condition.get();
            // dependant_rule->action = dependant_rule_action.get();
            // dependant_rule->insert(dependant_rule_action);
            // dependant_rule_action->setBetterRule(dependant_rule.get());
            // dependant_rule->condition->makePersistant();

            // master_rule->action->dependant_rules.insertInfo(resultant_condition.get());

            // rule_stack.push(dependant_rule);
            // dependant_rule->name = name;
            
            // return *dependant_rule;
        }
        else
        {
            #ifdef USE_CUSTOM_SMART_PTRS
                shared_ptr<BetterRule> shared_rule(new BetterRule());
                shared_ptr<BetterAction> shared_action(new BetterAction());
            #else
                shared_ptr<BetterRule> shared_rule = std::make_shared<BetterRule>(*new BetterRule());
                shared_ptr<BetterAction> shared_action = std::make_shared<BetterAction>(*new BetterAction());
            #endif // USE_CUSTOM_SMART_PTRS

            b_cond.insert(shared_rule);
            shared_rule->condition = &b_cond;

            shared_rule->action = shared_action.get();
            shared_action->setBetterRule(shared_rule.get());
            
            shared_rule->insert(shared_action);
            shared_rule->condition->makePersistant();

            rule_list.insertInfo(shared_rule);
            rule_stack.push(shared_rule);

            // BetterRule rule;
            // shared_ptr<BetterRule> shared_rule = std::make_shared<BetterRule>(rule);
            // b_cond.insert(shared_rule);
            // shared_rule->condition = &b_cond;
            // shared_rule->condition->makePersistant();

            // BetterAction action;
            // shared_ptr<BetterAction> shared_action = std::make_shared<BetterAction>(action);
            // shared_rule->action = shared_action.get();
            // shared_action->setBetterRule(shared_rule.get());
            
            // shared_rule->insert(shared_action);

            // rule_list.insertInfo(shared_rule);
            // rule_stack.push(shared_rule);
            // shared_rule->name = name;

            return *shared_rule;
        }        
    }

    /**
     * Finaliza uma Rule
     * 
     */
    void NOPManager::EndRule()
    {
        rule_stack.pop();
    }

    /**
     * Cria uma Instigation e adiciona ela à Action da última Rule criada aberta
     * 
     * @param func 
     */
    void NOPManager::CreateInstigation(std::function<void()> func)
    {
        #ifdef USE_CUSTOM_SMART_PTRS
            shared_ptr<BetterInstigation> shared_instigation(new BetterInstigation());
        #else
            shared_ptr<BetterInstigation> shared_instigation = std::make_shared<BetterInstigation>(*new BetterInstigation());
        #endif // USE_CUSTOM_SMART_PTRS
        

        rule_stack.top()->action->insert(shared_instigation);

        shared_instigation->setMt(func);

        // BetterInstigation aux;

        // shared_ptr<std::function<void()>> shared_method = std::make_shared<std::function<void()>>(func);
        // shared_ptr<BetterInstigation> shared_instigation = std::make_shared<BetterInstigation>(aux);

        // rule_stack.top()->action->insert(shared_instigation);

        // shared_instigation->setMt(*shared_method);
    }
}