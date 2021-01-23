#ifndef JUNOCPP
#define JUNOCPP

#include "./Table.hpp"
#include "./Utils/CustomString.hpp"
#include "./Utils/smart_ptr.hpp"
// #include "./Utils/forward_list.hpp"
#include "./Utils/tuple_helper.hpp"
#include "./Core/Attribute.hpp"
#include "./Core/BetterCondition.hpp"
#include "./Core/Premise.hpp"
#include "./Core/BetterRule.hpp"
#include "./Core/BetterAction.hpp"
#include "./Core/BetterInstigation.hpp"
#include "./Core/NOPManager.hpp"

using namespace JuNOCpp;
using namespace Utils;

#define RULE_1(expression)                                                              NOPManager::Get().CreateRule(expression);
#define RULE_2(expression, name)                                                        NOPManager::Get().CreateRule(expression, #name);
#define GET_MACRO(_1,_2, NAME,...) NAME
#define RULE(...) GET_MACRO(__VA_ARGS__, RULE_2, RULE_1)(__VA_ARGS__)
#define INSTIGATE(instigation)                                                          NOPManager::Get().CreateInstigation(instigation);
#define CALL(instigation)                                                               NOPManager::Get().AddInstigation(instigation);
#define END_RULE                                                                        NOPManager::Get().EndRule();
#define SharedCondition(expression)                                                     BetterCondition::sharedCondition(expression)

namespace NOP {
    #ifdef USE_CUSTOM_SMART_PTRS
        #include "./Utils/smart_ptr.hpp"
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
    using Instigation = BetterInstigation;
}

#endif // !JUNOCPP