#ifndef JUNOCPP_NOP_MANAGER_HPP
#define JUNOCPP_NOP_MANAGER_HPP

#include "Instigation.hpp"
#include "Notifier.hpp"
#include "CustomString.hpp"
#include <stack>

namespace JuNOCpp
{
    namespace Core
    {
        class Condition;
        class Action;
        class Rule;
        class NOPManager // Singleton
        {
        public:
            NOPManager(const NOPManager&) = delete;

            static NOPManager& Get(); 

            static void CreateRule(Condition&& b_cond);
            static void CreateRule(Condition& b_cond);
            static void CreateRule(Rule& rule, Condition& b_cond);
            static void CreateRule(Rule&& rule, Condition&& b_cond);
            static void EndRule();

            static void CreateInstigation(std::function<void()> func);
            static void AddInstigation(Instigation& inst);
            static void AddInstigation(Instigation&& inst);

        private:
            NOPManager();

            static Utils::forward_list<shared_ptr<Rule>> rule_list;
            static std::stack<shared_ptr<Rule>> rule_stack;

            static Rule* current_rule;
        };
    } // namespace Core
}

#endif // !JUNOCPP_NOP_MANAGER_HPP