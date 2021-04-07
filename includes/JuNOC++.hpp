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
#define RULE_2(rule, expression)                                                        Core::NOPManager::Get().CreateRule(rule, expression);
#define GET_MACRO(_1,_2, NAME,...) NAME
#define RULE(...) GET_MACRO(__VA_ARGS__, RULE_2, RULE_1)(__VA_ARGS__)
#define INSTIGATE(instigation)                                                          Core::NOPManager::Get().CreateInstigation(instigation);
#define CALL(instigation)                                                               Core::NOPManager::Get().AddInstigation(instigation);
#define END_RULE                                                                        Core::NOPManager::Get().EndRule();
#define PERSISTANT(expression)                                                          Core::Condition::sharedCondition(expression)
#define IMPERTINENT(premise)                                                            premise.impertinentThis()

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
    using PremiseEqual = Core::Premise<PrT, RT, Core::Comparison::EQUAL>&;
    template<class PrT, typename RT>
    using PremiseNotEqual = Core::Premise<PrT, RT, Core::Comparison::NOT_EQUAL>&;
    template<class PrT, typename RT>
    using PremiseGreater = Core::Premise<PrT, RT, Core::Comparison::GREATER>&;
    template<class PrT, typename RT>
    using PremiseGreaterEqual = Core::Premise<PrT, RT, Core::Comparison::GREATER_EQUAL>&;
    template<class PrT, typename RT>
    using PremiseLess = Core::Premise<PrT, RT, Core::Comparison::LESS>&;
    template<class PrT, typename RT>
    using PremiseLessEqual = Core::Premise<PrT, RT, Core::Comparison::LESS_EQUAL>&;

    template<class PrT, typename RT>
    using PremiseEqualPtr = shared_ptr<Core::Premise<PrT, RT, Core::Comparison::EQUAL>>;
    template<class PrT, typename RT>
    using PremiseNotEqualPtr = shared_ptr<Core::Premise<PrT, RT, Core::Comparison::NOT_EQUAL>>;
    template<class PrT, typename RT>
    using PremiseGreaterPtr = shared_ptr<Core::Premise<PrT, RT, Core::Comparison::GREATER>>;
    template<class PrT, typename RT>
    using PremiseGreaterEqualPtr = shared_ptr<Core::Premise<PrT, RT, Core::Comparison::GREATER>>;
    template<class PrT, typename RT>
    using PremiseLessPtr = shared_ptr<Core::Premise<PrT, RT, Core::Comparison::LESS>>;
    template<class PrT, typename RT>
    using PremiseLessEqualPtr = shared_ptr<Core::Premise<PrT, RT, Core::Comparison::LESS_EQUAL>>;

    using Condition = Core::Condition&;
    using ConditionPtr = shared_ptr<Core::Condition>;
    using Rule = Core::Rule;
    using RulePtr = shared_ptr<Core::Rule>;
    using Instigation = Core::Instigation;
}

#endif // !JUNOCPP