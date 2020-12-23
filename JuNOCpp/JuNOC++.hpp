#pragma once

#include "./Table.hpp"
#include "./List.hpp"
#include "./CustomString.hpp"

#include "./Better/BetterAttribute.hpp"
#include "./Better/BetterCondition.hpp"
#include "./Better/BetterPremise.hpp"
#include "./Better/BetterRule.hpp"
#include "./Better/BetterAction.hpp"
#include "./Better/BetterInstigation.hpp"
#include "./Better/NOPManager.hpp"

using namespace JuNOCpp;
using namespace Attributes;

// #define RULE(expression)                NOPManager::Get().CreateRule(expression)
// #define RULE_N(expression, name)        NOPManager::Get().CreateRule(expression, #name)
#define RULE_1(expression)                                                              NOPManager::Get().CreateRule(expression)
#define RULE_2(expression, name)                                                        NOPManager::Get().CreateRule(expression, #name)
#define GET_MACRO(_1,_2, NAME,...) NAME
#define RULE(...) GET_MACRO(__VA_ARGS__, RULE_2, RULE_1)(__VA_ARGS__)
#define INSTIGATE(instigation)                                                          NOPManager::Get().CreateInstigation(instigation)
#define END_RULE                                                                        NOPManager::Get().EndRule()
#define SharedCondition(expression)                                                     BetterCondition::sharedCondition(expression)

namespace NOP {
    template<typename TYPE>
    using Attribute = BetterAttribute<TYPE>;
    template<typename TYPE>
    using AttributePtr = BetterAttribute<TYPE>*;
    template<typename TYPE>
    using Premise = BetterPremise<TYPE>&;
    template<typename TYPE>
    using PremisePtr = BetterPremise<TYPE>*;
    using Condition = BetterCondition&;
    using ConditionPtr = BetterCondition*;
    using Rule = BetterRule&;
    using RulePtr = BetterRule*;
}