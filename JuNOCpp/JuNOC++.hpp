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
#include "./Better/BetterMethod.hpp"
#include "./Better/NOPManager.hpp"

using namespace JuNOCpp;
using namespace Attributes;

#define RULE(expression)                NOPManager::Get().CreateRule(expression)
#define RULE_N(expression, name)        NOPManager::Get().CreateRule(expression, #name)
#define INSTIGATE(instigation)          NOPManager::Get().CreateInstigation(instigation)
#define END_RULE                        NOPManager::Get().EndRule()
#define SharedCondition(expression)     BetterCondition::sharedCondition(expression)

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