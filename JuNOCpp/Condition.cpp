#include "Condition.hpp"
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
    this->true_premises = 0;
    this->rule = nullptr;
    this->mode = mode;

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
            //printf("true-condition\n");
            //printf("%dpremises\n", this->true_premises);
            rule->execute();

        }
    }
    else
    {
        this->true_premises--;
        // printf("%dpremises\n", this->true_premises);
        // printf("false-condition\n");
    }

}
