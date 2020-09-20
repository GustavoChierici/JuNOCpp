#include "Rule.hpp"
using namespace JuNOCpp;
using namespace Attributes;
#include <iostream>

Rule::Rule(CustomString mode /* = "CONJUNCTION" */)
{
    this->cond = new Condition(mode);
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

void Rule::addPremise(Attributes::Boolean* pattr, const bool value)
{
    Premise* aux = new Premise();
    aux->setAttribute(pattr, value);
    this->cond->addPremise(aux);
}

void Rule::addPremise(Attributes::String* pattr, CustomString value)
{
    Premise* aux = new Premise();
    aux->setAttribute(pattr, value);
    this->cond->addPremise(aux);
}

void Rule::addPremise(Attributes::Char* pattr, const char value)
{
    Premise* aux = new Premise();
    aux->setAttribute(pattr, value);
    this->cond->addPremise(aux);
}

void Rule::addPremise(Premise* pprm)
{
    this->cond->addPremise(pprm);
}

void Rule::referenceAttr(Attributes::Integer* attr, const int exec_value)
{
    this->attr = attr;
    this->attr_type = 0;
    this->exec_value_int = exec_value;
}

void Rule::referenceAttr(Attributes::Boolean* attr, const bool exec_value)
{
    this->attr = attr;
    this->attr_type = 1;
    this->exec_value_bool = exec_value;
}

void Rule::referenceAttr(Attributes::String* attr, CustomString exec_value)
{
    this->attr = attr;
    this->attr_type = 2;
    this->exec_value_str = exec_value;
}

void Rule::referenceAttr(Attributes::Char* attr, const char exec_value)
{
    this->attr = attr;
    this->attr_type = 3;
    this->exec_value_char = exec_value;
}

void Rule::execute() //Método execute da Rule (Derived) para modificar diretamente um Attribute, sem a necessidade de uma Action, Instigations e Methods
{
    //std::cout << "APROVADA" << std::endl;
    switch(this->attr_type)
    {
        case 0:
            static_cast<Attributes::Integer*>(this->attr)->setStatus(this->exec_value_int);
            break;
        case 1:
            static_cast<Attributes::Boolean*>(this->attr)->setStatus(this->exec_value_bool);
            break;
        case 2:
            static_cast<Attributes::String*>(this->attr)->setStatus(this->exec_value_str);
            break;
        case 3:
            static_cast<Attributes::Char*>(this->attr)->setStatus(this->exec_value_char);
            break;
    }
}
