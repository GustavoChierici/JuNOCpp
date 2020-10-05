#include "Condition.hpp"
#include "SubCondition.hpp"
#include "Rule.hpp"
using namespace JuNOCpp;

Condition::Condition(CustomString mode /* = "CONJUNCTION" */)
{
    if(mode != "CONJUNCTION" && mode != "DISJUNCTION")
    {
        std::cout << "ERRO! Condition so pode ser do modo CONJUNCTION ou DISJUNCTION!" << std::endl;
        exit(1);
    }
    this->quantity = 0;
    this->approved_premises_and_subconds = 0;
    this->rule = nullptr;
    this->mode = mode;
    this->current_subcondition = nullptr;

    if(this->mode == "DISJUNCTION")
        this->quantity = 1;
}

Condition::~Condition()
{
}

void Condition::addPremise(Premise* prm)
{
    if(this->mode == "CONJUNCTION")
        this->quantity++;
    prm->referenceCondition(this);
}

void Condition::addSubCondition(CustomString mode /* = "CONJUNCTION" */)
{
    if(this->mode == "CONJUNCTION")
        this->quantity++;
    SubCondition* aux = new SubCondition(mode);
    this->subconditions.insertInfo(aux);
    aux->referenceCondition(this);
    this->current_subcondition = this->subconditions.getCurrent()->getInfo();
    if(this->subconditions.getCurrent()->getNext() != nullptr)
        this->current_subcondition = this->subconditions.getCurrent()->getNext()->getInfo();
}

void Condition::addSubCondition(SubCondition* subcond)
{
    if(this->mode == "CONJUNCTION")
        this->quantity++;
    this->subconditions.insertInfo(subcond);
    subcond->referenceCondition(this);
    this->current_subcondition = this->subconditions.getCurrent()->getInfo();
    if(this->subconditions.getCurrent()->getNext() != nullptr)
        this->current_subcondition = this->subconditions.getCurrent()->getNext()->getInfo();
}

void Condition::addPremiseToSubCondition(Premise* prm)
{
    this->current_subcondition->addPremise(prm);
}

void Condition::referenceRule(Rule* rule)
{
    this->rule = rule;
}

void Condition::conditionalCheck(bool status)
{
    if(status)
    {
        this->approved_premises_and_subconds++;

        if(this->approved_premises_and_subconds == this->quantity)
            rule->execute();
    }
    else
        this->approved_premises_and_subconds--;
}
