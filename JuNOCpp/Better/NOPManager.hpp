#pragma once
#include "../List.hpp"
#include "./BetterMethod.hpp"
#include "./BetterInstigation.hpp"
#include "Notifier.hpp"
#include <vector>

namespace JuNOCpp
{
    namespace Attributes
    {
        template<class TYPE>
        class BetterAttribute;
    }
        template<class TYPE>
        class BetterPremise;
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

        static void CreateInstigation(std::function<void()> func);

    private:
        NOPManager();

        static List<std::shared_ptr<BetterRule>> rule_list;
        // static List<std::shared_ptr<BetterCondition>> condition_list;
        // static List<BetterAction> action_list;

        static BetterRule* current_rule;
    };
}