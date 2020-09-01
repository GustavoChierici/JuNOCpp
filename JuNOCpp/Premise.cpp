#include "Premise.hpp"
#include "./Attributes/Integer.hpp"
#include "./Condition.hpp"
#include <iostream>
using namespace JuNOCpp;
using namespace Attributes;
Premise::Premise()
{
    this->attr_reference = nullptr;
    this->status = false;
    this->previous_status = false;
}

Premise::~Premise()
{
}

Premise::Premise(Attributes::Attribute* attr, const int value)
{
    this->status = false;
    this->previous_status = false;
    this->setAttribute(attr, value);
}

void Premise::setAttribute(Attribute* attr, const int value)
{
    this->attr_reference = attr;
    this->value = value;
    this->attr_reference->getTable()->insertValue(this->value, this);
}

void Premise::setAttribute(Attribute* attr, const bool value)
{
    this->attr_reference = attr;
    this->value = value;
    this->attr_reference->getTable()->insertValue(this->value, this);
}

void Premise::conditionalCheck()
{
    Integer* aux = static_cast<Integer*>(this->attr_reference);
    //if(aux){
        if(aux->getState() == this->value)
        {
            this->status = true;
            //std::cout<<"true"<<std::endl;
        }
        else{
            this->status = false;
            //std::cout<< "false" << std::endl;
        }
        this->notifyConditions();
    //}

}

void Premise::referenceCondition(Condition* pcond)
{
    this->conditions.push_back(pcond);
}

void Premise::notifyConditions()
{
    //std::cout << "previous:" << this->previous_state <<std::endl;
    //std::cout << "current:" << this->state <<std::endl;
    if(this->previous_status != this->status)
    {
        this->previous_status = this->status;
        for(auto i : this->conditions)
            i->conditionalCheck(this->status);
    }
}

