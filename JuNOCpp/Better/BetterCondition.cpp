#include "BetterCondition.hpp"
#include "BetterPremise.hpp"
#include "BetterRule.hpp"
using namespace JuNOCpp;

BetterCondition::BetterCondition()
{
    this->permanent = false;
    this->quantity = 0;
    this->approved_premises_and_subconds = 0;
    this->rule = nullptr;
    this->previous_status = false;
    this->current_status = false;
    this->better_condition_above = nullptr;
}

BetterCondition::~BetterCondition()
{
}

void BetterCondition::addBetterCondition(BetterCondition* b_condition)
{
    b_condition->better_condition_above = this;
}

void BetterCondition::referenceBetterRule(BetterRule* rule)
{
    this->rule = rule;
}

void BetterCondition::update(const bool renotify)
{
}

void BetterCondition::notify(const bool renotify)
{
    for(auto notf : notfs)
    {
        auto cond = dynamic_cast<BetterCondition*>(notf.get());
        if(cond)
            cond->conditionalCheck(this->current_status);
        else if(this->current_status)
            notf->update(renotify);
    }
}

void BetterCondition::conditionalCheck(bool status, bool renotify)
{
    if(status)
    {
        this->approved_premises_and_subconds++;

        if(this->approved_premises_and_subconds == this->quantity)
        {
            this->current_status = true;
        }
        // std::cout << "(+) ";
    }
    else if(this->approved_premises_and_subconds > 0)
    {
        this->approved_premises_and_subconds--;
        this->current_status = false;
        // std::cout << "(-) ";
    }
    // std::cout << "CONDITION - " << this << " - " << this->approved_premises_and_subconds << "/" << this->quantity <<std::endl;
    if(renotify || this->current_status != this->previous_status)
    {
        this->previous_status = this->current_status;
        notify(renotify);
    }
}

void BetterCondition::setQuantity(const int quant)
{
    this->quantity = quant;
}

BetterCondition& BetterCondition::operator &&(BetterCondition& b_condition)
{
    BetterCondition aux;

    std::shared_ptr<BetterCondition> condition = std::make_shared<BetterCondition>(aux);
    condition->setQuantity(2);

    this->insert(condition);
    b_condition.insert(condition);
    
    return *condition;
}

BetterCondition& BetterCondition::operator &&(BetterCondition&& b_condition)
{
    BetterCondition aux;

    std::shared_ptr<BetterCondition> condition = std::make_shared<BetterCondition>(aux);
    condition->setQuantity(2);

    this->insert(condition);
    b_condition.insert(condition);
    
    return *condition;
}

BetterCondition& BetterCondition::operator ||(BetterCondition& b_condition)
{
    BetterCondition aux;

    std::shared_ptr<BetterCondition> condition = std::make_shared<BetterCondition>(aux);
    condition->setQuantity(1);

    this->insert(condition);
    b_condition.insert(condition);
    
    return *condition;
}

BetterCondition& BetterCondition::operator ||(BetterCondition&& b_condition)
{
    BetterCondition aux;

    std::shared_ptr<BetterCondition> condition = std::make_shared<BetterCondition>(aux);
    condition->setQuantity(1);

    this->insert(condition);
    b_condition.insert(condition);
    
    return *condition;
}

