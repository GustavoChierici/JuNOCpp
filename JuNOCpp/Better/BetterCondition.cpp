#include "BetterCondition.hpp"
#include "BetterPremise.hpp"
#include "BetterRule.hpp"
using namespace JuNOCpp;

BetterCondition::BetterCondition()
{
    this->persistant = false;
    this->quantity = 0;
    this->count_approved = 0;
    this->count_impertinents = 0;
    this->rule = nullptr;
    this->previous_status = false;
    this->current_status = false;
}

BetterCondition::~BetterCondition()
{
}

void BetterCondition::update(const bool renotify)
{
}

void BetterCondition::update(const bool renotify, const bool status)
{
    if(status)
    {
        this->count_approved++;

        if(this->count_approved == this->quantity)
        {
            this->current_status = true;
        }
        // std::cout << "(+) ";
    }
    else if(this->count_approved > 0)
    {
        this->count_approved--;
        this->current_status = false;
        // std::cout << "(-) ";
    }
    // std::cout << "CONDITION - " << this << " - " << this->count_approved << "/" << this->quantity <<std::endl;
    if(renotify || this->current_status != this->previous_status)
    {
        this->previous_status = this->current_status;
        notify(renotify);
    }
    if(this->count_approved + this->count_impertinents == this->quantity)
    {
        activateImpertinents();
        this->is_impertinents_active = true;
    }
    else if(is_impertinents_active)
    {
        is_impertinents_active = false;
        deactivateImpertinents();
    }
}

void BetterCondition::notify(const bool renotify)
{
    auto aux = this->notifiables.getFirst();

    while(aux)
    {
        auto cond = dynamic_cast<BetterCondition*>(aux->getInfo().get());
        if(cond)
            cond->update(renotify, this->current_status);
        else if(this->current_status)
            aux->getInfo()->update(renotify);

        aux = aux->getNext();
    }
    
}

void BetterCondition::activateImpertinents()
{
    auto aux = this->impertinents.getFirst();

    while(aux)
    {
        aux->getInfo()->activate();

        aux = aux->getNext();
    }
}

void BetterCondition::deactivateImpertinents()
{
    auto aux = this->impertinents.getFirst();

    while(aux)
    {
        aux->getInfo()->deactivate();

        aux = aux->getNext();
    }
}

void BetterCondition::setQuantity(const int quant)
{
    this->quantity = quant;
}

BetterCondition& BetterCondition::operator &&(BetterCondition& b_condition)
{
    if((b_condition.mode == BetterCondition::CONJUNCTION or b_condition.mode == BetterCondition::SINGLE)
     and (this->mode == BetterCondition::CONJUNCTION or this->mode == BetterCondition::SINGLE) 
     and !b_condition.persistant and !this->persistant)
    {
        b_condition.insert(this->shared_from_this());
        this->setQuantity(this->quantity + 1);

        return *this;
    }
    else
    {
        BetterCondition aux;

        std::shared_ptr<BetterCondition> condition = std::make_shared<BetterCondition>(aux);
        condition->setQuantity(2);
        condition->mode = BetterCondition::CONJUNCTION;

        this->insert(condition);
        b_condition.insert(condition);
        
        return *condition;
    }
}

BetterCondition& BetterCondition::operator &&(BetterCondition&& b_condition)
{
    if((b_condition.mode == BetterCondition::CONJUNCTION or b_condition.mode == BetterCondition::SINGLE)
     and (this->mode == BetterCondition::CONJUNCTION or this->mode == BetterCondition::SINGLE) 
     and !b_condition.persistant and !this->persistant)
    {
        b_condition.insert(this->shared_from_this());
        this->setQuantity(this->quantity + 1);

        return *this;
    }
    else
    {
        BetterCondition aux;

        std::shared_ptr<BetterCondition> condition = std::make_shared<BetterCondition>(aux);
        condition->setQuantity(2);
        condition->mode = BetterCondition::CONJUNCTION;

        this->insert(condition);
        b_condition.insert(condition);
        
        return *condition;
    }
}

BetterCondition& BetterCondition::operator ||(BetterCondition& b_condition)
{
    if((b_condition.mode == BetterCondition::DISJUNCTION or b_condition.mode == BetterCondition::SINGLE)
     and (this->mode == BetterCondition::DISJUNCTION or this->mode == BetterCondition::SINGLE) 
     and !b_condition.persistant and !this->persistant)
    {
        b_condition.insert(this->shared_from_this());

        return *this;
    }
    else
    {
        BetterCondition aux;

        std::shared_ptr<BetterCondition> condition = std::make_shared<BetterCondition>(aux);
        condition->setQuantity(1);
        condition->mode = BetterCondition::DISJUNCTION;

        this->insert(condition);
        b_condition.insert(condition);
        
        return *condition;
    }
}

BetterCondition& BetterCondition::operator ||(BetterCondition&& b_condition)
{
    if((b_condition.mode == BetterCondition::DISJUNCTION or b_condition.mode == BetterCondition::SINGLE)
     and (this->mode == BetterCondition::DISJUNCTION or this->mode == BetterCondition::SINGLE) 
     and !b_condition.persistant and !this->persistant)
    {
        b_condition.insert(this->shared_from_this());

        return *this;
    }
    else
    {
        BetterCondition aux;

        std::shared_ptr<BetterCondition> condition = std::make_shared<BetterCondition>(aux);
        condition->setQuantity(1);
        condition->mode = BetterCondition::DISJUNCTION;

        this->insert(condition);
        b_condition.insert(condition);
        
        return *condition;
    }
}

