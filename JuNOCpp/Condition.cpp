#include "Condition.hpp"
#include "Rule.hpp"
using namespace JuNOCpp;

Condition::Condition()
{
    this->quantity = 0;
    this->true_premises = 0;
    this->rule = nullptr;
}

Condition::~Condition()
{
}

void Condition::addPremise(Premise* prm)
{
    this->quantity++;
    prm->referenceCondition(this);
}

void Condition::referenceRule(Rule* rule)
{
    this->rule = rule;
}

void Condition::conditionalCheck(bool status)
{
    if(status)
    {
        this->true_premises++;

        if(this->true_premises == this->quantity){
           // printf("true-condition\n");
           // printf("%dpremises\n", this->true_premises);
            rule->execute();

        }
    }
    else
    {
        this->true_premises--;
        //printf("%dpremises\n", this->true_premises);
        //printf("false-condition\n");
    }

}
