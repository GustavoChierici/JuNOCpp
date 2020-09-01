#include "Rule.hpp"
using namespace JuNOCpp;
using namespace Attributes;
#include <iostream>

Rule::Rule(const int exec_value/* = 0*/, Condition* pcond/* = nullptr*/)
{
    this->exec_value = exec_value;
    if(pcond)
        this->cond = pcond;
    else
        this->cond = new Condition();
    this->cond->referenceRule(this);
}

Rule::~Rule()
{
    delete this->cond;
}

void Rule::addPremise(Attributes::Integer* pattr, const int value)
{
    Premise* aux = new Premise();
    aux->setAttribute(pattr, value);
    this->cond->addPremise(aux);
}

void Rule::addPremise(Premise* pprm)
{
    this->cond->addPremise(pprm);
}

void Rule::addCondition(Condition* cond)
{
    this->cond = cond;
    this->cond->referenceRule(this);
}

void Rule::referenceAttr(Attributes::Integer* attr)
{
    this->attr = attr;
}

void Rule::execute() //Método execute da Rule (Derived) para modificar diretamente um Attribute, sem a necessidade de uma Action, Instigations e Methods
{
    //std::cout << "APROVADA" << std::endl;
    this->attr->setStatus(this->exec_value);
}
