#ifndef JUNOCPP
#define JUNOCPP

#include "CustomString.hpp"
#include "smart_ptr.hpp"
#include "forward_list.hpp"
#include "tuple_helper.hpp"
#include "Attribute.hpp"
#include "Condition.hpp"
#include "Premise.hpp"
#include "Rule.hpp"
#include "Action.hpp"
#include "Instigation.hpp"
#include "NOPManager.hpp"
#include ".config.hpp"

using namespace JuNOCpp;
using namespace Utils;

#define RULE_1(expression)                                                              Core::NOPManager::Get().CreateRule(expression);
#define RULE_2(expression, name)                                                        Core::NOPManager::Get().CreateRule(expression, #name);
#define GET_MACRO(_1,_2, NAME,...) NAME
#define RULE(...) GET_MACRO(__VA_ARGS__, RULE_2, RULE_1)(__VA_ARGS__)
#define INSTIGATE(instigation)                                                          Core::NOPManager::Get().CreateInstigation(instigation);
#define CALL(instigation)                                                               Core::NOPManager::Get().AddInstigation(instigation);
#define END_RULE                                                                        Core::NOPManager::Get().EndRule();
#define SharedCondition(expression)                                                     Core::Condition::sharedCondition(expression)

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
    using Attribute = Core::Attribute<TYPE>;
    template<typename TYPE>
    using AttributePtr = shared_ptr<Core::Attribute<TYPE>>;

    template<class PrT, typename RT>
    using PremiseEqual = Core::Premise<PrT, RT, NOPTraits::equal_t>&;
    template<class PrT, typename RT>
    using PremiseNotEqual = Core::Premise<PrT, RT, NOPTraits::not_equal_t>&;
    template<class PrT, typename RT>
    using PremiseGreater = Core::Premise<PrT, RT, NOPTraits::greater_t>&;
    template<class PrT, typename RT>
    using PremiseGreaterEqual = Core::Premise<PrT, RT, NOPTraits::greater_equal_t>&;
    template<class PrT, typename RT>
    using PremiseLess = Core::Premise<PrT, RT, NOPTraits::less_t>&;
    template<class PrT, typename RT>
    using PremiseLessEqual = Core::Premise<PrT, RT, NOPTraits::less_equal_t>&;

    template<class PrT, typename RT>
    using PremiseEqualPtr = shared_ptr<Core::Premise<PrT, RT, NOPTraits::equal_t>>;
    template<class PrT, typename RT>
    using PremiseNotEqualPtr = shared_ptr<Core::Premise<PrT, RT, NOPTraits::not_equal_t>>;
    template<class PrT, typename RT>
    using PremiseGreaterPtr = shared_ptr<Core::Premise<PrT, RT, NOPTraits::greater_t>>;
    template<class PrT, typename RT>
    using PremiseGreaterEqualPtr = shared_ptr<Core::Premise<PrT, RT, NOPTraits::greater_equal_t>>;
    template<class PrT, typename RT>
    using PremiseLessPtr = shared_ptr<Core::Premise<PrT, RT, NOPTraits::less_t>>;
    template<class PrT, typename RT>
    using PremiseLessEqualPtr = shared_ptr<Core::Premise<PrT, RT, NOPTraits::less_equal_t>>;

    using Condition = Core::Condition&;
    using ConditionPtr = shared_ptr<Core::Condition>;
    using Rule = Core::Rule&;
    using RulePtr = shared_ptr<Core::Rule>;
    using Instigation = Core::Instigation;
}

#endif // !JUNOCPP