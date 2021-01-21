#pragma once

#include "./Table.hpp"
#include "./CustomString.hpp"
#include "./Utils/SmartPtr.hpp"
// #include "./Utils/forward_list.hpp"
#include "./Utils/tuple_helper.hpp"
// #include "./Better/BetterAttribute.hpp"
#include "./Better/Attribute.hpp"
#include "./Better/BetterCondition.hpp"
#include "./Better/Premise.hpp"
#include "./Better/BetterRule.hpp"
#include "./Better/BetterAction.hpp"
#include "./Better/BetterInstigation.hpp"
#include "./Better/NOPManager.hpp"

using namespace JuNOCpp;
using namespace Utils;
using namespace Attributes;

// #define RULE(expression)                NOPManager::Get().CreateRule(expression)
// #define RULE_N(expression, name)        NOPManager::Get().CreateRule(expression, #name)
#define RULE_1(expression)                                                              NOPManager::Get().CreateRule(expression);
#define RULE_2(expression, name)                                                        NOPManager::Get().CreateRule(expression, #name);
#define GET_MACRO(_1,_2, NAME,...) NAME
#define RULE(...) GET_MACRO(__VA_ARGS__, RULE_2, RULE_1)(__VA_ARGS__)
#define INSTIGATE(instigation)                                                          NOPManager::Get().CreateInstigation(instigation);
#define END_RULE                                                                        NOPManager::Get().EndRule();
#define SharedCondition(expression)                                                     BetterCondition::sharedCondition(expression)

namespace NOP {
    #ifdef USE_CUSTOM_SMART_PTRS
        #include "./Utils/SmartPtr.hpp"
        template <typename T>
        using shared_ptr = JuNOCpp::Utils::shared_ptr<T>;
        template <typename T>
        using weak_ptr = JuNOCpp::Utils::weak_ptr<T>;
    #else
        #include <memory>
        template <typename T>
        using shared_ptr = std::shared_ptr<T>;
        template <typename T>
        using weak_ptr = std::weak_ptr<T>;
    #endif // USE_CUSTOM_SMART_PTRS



    template<typename TYPE>
    using Attribute = Attribute<TYPE>;
    template<typename TYPE>
    using AttributePtr = Attribute<TYPE>*;



    template<class PrT, typename RT>
    using PremiseEqual = Premise<PrT, RT, NOPTraits::equal_t>&;
    template<class PrT, typename RT>
    using PremiseNotEqual = Premise<PrT, RT, NOPTraits::not_equal_t>&;
    template<class PrT, typename RT>
    using PremiseGreater = Premise<PrT, RT, NOPTraits::greater_t>&;
    template<class PrT, typename RT>
    using PremiseGreaterEqual = Premise<PrT, RT, NOPTraits::greater_equal_t>&;
    template<class PrT, typename RT>
    using PremiseLess = Premise<PrT, RT, NOPTraits::less_t>&;
    template<class PrT, typename RT>
    using PremiseLessEqual = Premise<PrT, RT, NOPTraits::less_equal_t>&;

    template<class PrT, typename RT>
    using PremiseEqualPtr = shared_ptr<Premise<PrT, RT, NOPTraits::equal_t>>;
    template<class PrT, typename RT>
    using PremiseNotEqualPtr = shared_ptr<Premise<PrT, RT, NOPTraits::not_equal_t>>;
    template<class PrT, typename RT>
    using PremiseGreaterPtr = shared_ptr<Premise<PrT, RT, NOPTraits::greater_t>>;
    template<class PrT, typename RT>
    using PremiseGreaterEqualPtr = shared_ptr<Premise<PrT, RT, NOPTraits::greater_equal_t>>;
    template<class PrT, typename RT>
    using PremiseLessPtr = shared_ptr<Premise<PrT, RT, NOPTraits::less_t>>;
    template<class PrT, typename RT>
    using PremiseLessEqualPtr = shared_ptr<Premise<PrT, RT, NOPTraits::less_equal_t>>;



    using Condition = BetterCondition&;
    using ConditionPtr = BetterCondition*;
    using Rule = BetterRule&;
    using RulePtr = BetterRule*;
}