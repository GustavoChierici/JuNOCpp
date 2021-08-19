#include "NOPManager.hpp"
#include "Condition.hpp"
#include "Attribute.hpp"
#include "Premise.hpp"
#include "Rule.hpp"
#include "Action.hpp"

namespace JuNOCpp
{
    namespace Core
    {
        Utils::forward_list<shared_ptr<Rule>> NOPManager::rule_list;
        std::stack<shared_ptr<Rule>> NOPManager::rule_stack;
        Rule* NOPManager::current_rule = nullptr;

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
        void NOPManager::CreateRule(Condition&& b_cond)
        {
        if(!rule_stack.empty())
            {
                shared_ptr<Rule> master_rule = rule_stack.top();

                #ifdef USE_CUSTOM_SMART_PTRS
                    shared_ptr<Rule> dependant_rule(new Rule());
                    shared_ptr<Action> dependant_rule_action(new Action());
                    shared_ptr<Condition> resultant_condition(new Condition());
                #else
                    shared_ptr<Rule> dependant_rule = std::make_shared<Rule>(*new Rule());
                    shared_ptr<Action> dependant_rule_action = std::make_shared<Action>(*new Action());
                    shared_ptr<Condition> resultant_condition = std::make_shared<Condition>(*new Condition());
                #endif // USE_CUSTOM_SMART_PTRS

                resultant_condition->setQuantity(2);
                b_cond.insert(resultant_condition);
                master_rule->action->insert(resultant_condition);

                resultant_condition->insert(dependant_rule);
                dependant_rule->condition = resultant_condition.get();
                dependant_rule->action = dependant_rule_action.get();
                dependant_rule->insert(dependant_rule_action);
                dependant_rule_action->setRule(dependant_rule.get());
                dependant_rule->condition->makePersistant();

                std::string cond_name = dependant_rule->getName().get_str();
                cond_name += "Condition";

                dependant_rule->condition->setName(cond_name);

                rule_stack.push(dependant_rule);
                rule_list.push_back(dependant_rule);
            }
            else
            {
                #ifdef USE_CUSTOM_SMART_PTRS
                    shared_ptr<Rule> shared_rule(new Rule());
                    shared_ptr<Action> shared_action(new Action());
                #else
                    shared_ptr<Rule> shared_rule = std::make_shared<Rule>(*new Rule());
                    shared_ptr<Action> shared_action = std::make_shared<Action>(*new Action());
                #endif // USE_CUSTOM_SMART_PTRS

                b_cond.insert(shared_rule);
                shared_rule->condition = &b_cond;

                shared_rule->action = shared_action.get();
                shared_action->setRule(shared_rule.get());
                
                shared_rule->insert(shared_action);
                shared_rule->condition->makePersistant();

                std::string cond_name = shared_rule->getName().get_str();
                cond_name += "Condition";

                shared_rule->condition->setName(cond_name);

                rule_list.push_back(shared_rule);
                rule_stack.push(shared_rule);

            }        
        }
        
        /**
         * Cria uma Rule
         * 
         * @param b_cond 
         */
        void NOPManager::CreateRule(Condition& b_cond)
        {
            if(!rule_stack.empty())
            {
                shared_ptr<Rule> master_rule = rule_stack.top();

                #ifdef USE_CUSTOM_SMART_PTRS
                    shared_ptr<Rule> dependant_rule(new Rule());
                    shared_ptr<Action> dependant_rule_action(new Action());
                    shared_ptr<Condition> resultant_condition(new Condition());
                #else
                    shared_ptr<Rule> dependant_rule = std::make_shared<Rule>(*new Rule());
                    shared_ptr<Action> dependant_rule_action = std::make_shared<Action>(*new Action());
                    shared_ptr<Condition> resultant_condition = std::make_shared<Condition>(*new Condition());
                #endif // USE_CUSTOM_SMART_PTRS

                resultant_condition->setQuantity(2);
                b_cond.insert(resultant_condition);
                master_rule->action->insert(resultant_condition);

                resultant_condition->insert(dependant_rule);
                dependant_rule->condition = resultant_condition.get();
                dependant_rule->action = dependant_rule_action.get();
                dependant_rule->insert(dependant_rule_action);
                dependant_rule_action->setRule(dependant_rule.get());
                dependant_rule->condition->makePersistant();

                master_rule->action->dependant_rules.push_back(resultant_condition.get());

                std::string cond_name = dependant_rule->getName().get_str();
                cond_name += "Condition";

                dependant_rule->condition->setName(cond_name);

                rule_stack.push(dependant_rule);
                rule_list.push_back(dependant_rule);
            }
            else
            {
                #ifdef USE_CUSTOM_SMART_PTRS
                    shared_ptr<Rule> shared_rule(new Rule());
                    shared_ptr<Action> shared_action(new Action());
                #else
                    shared_ptr<Rule> shared_rule = std::make_shared<Rule>(*new Rule());
                    shared_ptr<Action> shared_action = std::make_shared<Action>(*new Action());
                #endif // USE_CUSTOM_SMART_PTRS

                b_cond.insert(shared_rule);
                shared_rule->condition = &b_cond;

                shared_rule->action = shared_action.get();
                shared_action->setRule(shared_rule.get());
                
                shared_rule->insert(shared_action);
                shared_rule->condition->makePersistant();

                std::string cond_name = shared_rule->getName().get_str();
                cond_name += "Condition";

                shared_rule->condition->setName(cond_name);

                rule_list.push_back(shared_rule);
                rule_stack.push(shared_rule);
            }        
        }

        /**
         * Cria e retorna uma Rule nomeada
         * 
         * @param rule 
         * @param b_cond 
         */
        void NOPManager::CreateRule(Rule& rule, Condition& b_cond)
        {
            if(!rule_stack.empty())
            {
                shared_ptr<Rule> master_rule = rule_stack.top();
                
                #ifdef USE_CUSTOM_SMART_PTRS
                    shared_ptr<Rule> dependant_rule(&rule);
                    shared_ptr<Action> dependant_rule_action(new Action());
                    shared_ptr<Condition> resultant_condition(new Condition());
                #else
                    shared_ptr<Rule> dependant_rule = std::make_shared<Rule>(rule);
                    shared_ptr<Action> dependant_rule_action = std::make_shared<Action>(*new Action());
                    shared_ptr<Condition> resultant_condition = std::make_shared<Condition>(*new Condition());
                #endif // USE_CUSTOM_SMART_PTRS

                resultant_condition->setQuantity(2);
                b_cond.insert(resultant_condition);
                master_rule->action->insert(resultant_condition);

                resultant_condition->insert(dependant_rule);
                dependant_rule->condition = resultant_condition.get();
                dependant_rule->action = dependant_rule_action.get();
                dependant_rule->insert(dependant_rule_action);
                dependant_rule_action->setRule(dependant_rule.get());
                dependant_rule->condition->makePersistant();

                master_rule->action->dependant_rules.push_back(resultant_condition.get());

                rule_stack.push(dependant_rule);
                rule_list.push_back(dependant_rule);

                std::string cond_name = dependant_rule->getName().get_str();
                cond_name += "Condition";

                dependant_rule->condition->setName(cond_name);
            }
            else
            {
                #ifdef USE_CUSTOM_SMART_PTRS
                    shared_ptr<Rule> shared_rule(&rule);
                    shared_ptr<Action> shared_action(new Action());
                #else
                    shared_ptr<Rule> shared_rule = std::make_shared<Rule>(rule);
                    shared_ptr<Action> shared_action = std::make_shared<Action>(*new Action());
                #endif // USE_CUSTOM_SMART_PTRS

                b_cond.insert(shared_rule);
                shared_rule->condition = &b_cond;

                shared_rule->action = shared_action.get();
                shared_action->setRule(shared_rule.get());
                
                shared_rule->insert(shared_action);
                shared_rule->condition->makePersistant();

                std::string cond_name = shared_rule->getName().get_str();
                cond_name += "Condition";

                shared_rule->condition->setName(cond_name);

                rule_list.push_back(shared_rule);
                rule_stack.push(shared_rule);
            }        
        }

        /**
         * Finaliza uma Rule
         * 
         */
        void NOPManager::EndRule()
        {
            if(rule_stack.top()->condition->getCurrentStatus());
                rule_stack.top()->update();
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
                shared_ptr<Instigation> shared_instigation(new Instigation());
            #else
                shared_ptr<Instigation> shared_instigation = std::make_shared<Instigation>(*new Instigation());
            #endif // USE_CUSTOM_SMART_PTRS
            

            rule_stack.top()->action->insert(shared_instigation);

            shared_instigation->setMt(func);
        }

        void NOPManager::AddInstigation(Instigation& inst)
        {
            #ifdef USE_CUSTOM_SMART_PTRS
                shared_ptr<Instigation> shared_instigation(&inst);
            #else
                shared_ptr<Instigation> shared_instigation = std::make_shared<Instigation>(inst);
            #endif 

            rule_stack.top()->action->insert(shared_instigation);
        }
    } // namespace Core
    
} // namespace JuNOCpp