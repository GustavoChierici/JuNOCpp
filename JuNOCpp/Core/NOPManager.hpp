#ifndef JUNOCPP_NOP_MANAGER_HPP
#define JUNOCPP_NOP_MANAGER_HPP

#include "./BetterInstigation.hpp"
#include "Notifier.hpp"
#include "../Utils/CustomString.hpp"
#include <stack>

namespace JuNOCpp
{
        class BetterCondition;
        class BetterAction;
        class BetterRule;
    class NOPManager // Singleton
    {
    public:
        NOPManager(const NOPManager&) = delete;

        static NOPManager& Get(); 

        static void CreateRule(BetterCondition&& b_cond);
        static void CreateRule(BetterCondition& b_cond);
        static BetterRule& CreateRule(BetterCondition& b_cond, Utils::CustomString name);
        static void EndRule();

        static void CreateInstigation(std::function<void()> func);
        static void AddInstigation(BetterInstigation& inst);
        static void AddInstigation(BetterInstigation&& inst);

    private:
        NOPManager();

        static Utils::forward_list<shared_ptr<BetterRule>> rule_list;
        static std::stack<shared_ptr<BetterRule>> rule_stack;

        static BetterRule* current_rule;
    };
}

#endif // !JUNOCPP_NOP_MANAGER_HPP