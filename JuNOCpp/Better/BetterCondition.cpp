#include "BetterCondition.hpp"
#include "BetterPremise.hpp"
#include "BetterRule.hpp"
using namespace JuNOCpp;


/**
 * Construtor
 * 
 */
BetterCondition::BetterCondition() :
    quantity{0},
    count_approved{0},
    persistant{false},
    count_impertinents{0},
    previous_status{false},
    current_status{false}
{  
}

/**
 * Destrutor
 * 
 */
BetterCondition::~BetterCondition()
{
}

/**
 * Sobrecarga do update inútil para uma Condition
 * 
 * @param renotify 
 */
void BetterCondition::update(const bool renotify)
{
}

/**
 * Analisa se a Condition foi aprovada ou não
 * 
 * @param renotify 
 * @param status 
 */
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
    if(this->count_approved + this->count_impertinents == this->quantity and this->impertinents.empty())
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

/**
 * Notifica as demais Conditions e Rules que dependem da Condition
 * 
 * @param renotify 
 */
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

/**
 * Notifica as Premises impertinentes sobre sua ativação, para que então elas passem a ser notificadas pelos Attributes dos quais dependem
 * 
 */
void BetterCondition::activateImpertinents()
{
    auto aux = this->impertinents.getFirst();

    while(aux)
    {
        aux->getInfo()->activate();

        aux = aux->getNext();
    }
}

/**
 * Notifica as Premises impertinentes sobre sua desativação, para que parem de ser notificadas pelos Attributes dos quais dependem
 * 
 */
void BetterCondition::deactivateImpertinents()
{
    auto aux = this->impertinents.getFirst();

    while(aux)
    {
        aux->getInfo()->deactivate();

        aux = aux->getNext();
    }
}

/**
 * Define a quantidade de notificações true que a Condition precisa para ser aprovada
 * 
 * @param quant 
 */
void BetterCondition::setQuantity(const int quant)
{
    this->quantity = quant;
}

/**
 * Cria e retorna uma Condition do tipo CONJUNCTION
 * 
 * @param b_condition 
 * @return BetterCondition& 
 */
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
        shared_ptr<BetterCondition> condition(new BetterCondition());

        // BetterCondition aux;

        // shared_ptr<BetterCondition> condition = std::make_shared<BetterCondition>(aux);
        condition->setQuantity(2);
        condition->mode = BetterCondition::CONJUNCTION;

        this->insert(condition);
        b_condition.insert(condition);
        
        return *condition;
    }
}

/**
 * Cria e retorna uma Condition do tipo CONJUNCTION
 * 
 * @param b_condition 
 * @return BetterCondition& 
 */
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
        #ifdef USE_CUSTOM_SMART_PTRS
            shared_ptr<BetterCondition> condition(new BetterCondition());
        #else
            shared_ptr<BetterCondition> condition = std::make_shared<BetterCondition>(*new BetterCondition());
        #endif // USE_CUSTOM_SMART_PTRS
        condition->setQuantity(2);
        condition->mode = BetterCondition::CONJUNCTION;

        this->insert(condition);
        b_condition.insert(condition);
        
        return *condition;
    }
}

/**
 * Cria e retorna uma Condition do tipo DISJUNCTION
 * 
 * @param b_condition 
 * @return BetterCondition& 
 */
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
        #ifdef USE_CUSTOM_SMART_PTRS
            shared_ptr<BetterCondition> condition(new BetterCondition());
        #else
            shared_ptr<BetterCondition> condition = std::make_shared<BetterCondition>(*new BetterCondition());
        #endif // USE_CUSTOM_SMART_PTRS
        condition->setQuantity(1);
        condition->mode = BetterCondition::DISJUNCTION;

        this->insert(condition);
        b_condition.insert(condition);
        
        return *condition;
    }
}

/**
 * Cria e retorna uma Condition do tipo DISJUNCTION
 * 
 * @param b_condition 
 * @return BetterCondition& 
 */
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
        #ifdef USE_CUSTOM_SMART_PTRS
            shared_ptr<BetterCondition> condition(new BetterCondition());
        #else
            shared_ptr<BetterCondition> condition = std::make_shared<BetterCondition>(*new BetterCondition());
        #endif // USE_CUSTOM_SMART_PTRS
        condition->setQuantity(1);
        condition->mode = BetterCondition::DISJUNCTION;

        this->insert(condition);
        b_condition.insert(condition);
        
        return *condition;
    }
}

