#include "Premise.hpp"
#include "./Attributes/Integer.hpp"
#include "./Attributes/Boolean.hpp"
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

void Premise::setAttribute(Attribute* attr, int value)
{
    this->attr_reference = attr;
    this->value = value;
    this->attr_reference->getTable()->insertValue(this->value, this);
}

void Premise::setAttribute(Attribute* attr, bool value)
{
    this->attr_reference = attr;
    this->value = int(value);
    this->attr_reference->getTable()->insertValue(this->value, this);
}

void Premise::setAttribute(Attribute* attr, CustomString value)
{
    this->attr_reference = attr;
    this->str_value = value;
    this->attr_reference->getTable()->insertValue(this->str_value, this);
}

void Premise::setAttribute(Attribute* attr, char value)
{
    this->attr_reference = attr;
    this->char_value = value;
    this->attr_reference->getTable()->insertValue(this->char_value, this);
}

void Premise::setAttribute(Attribute* attr, double value)
{
    this->attr_reference = attr;
    this->double_value = value;
    this->attr_reference->getTable()->insertValue(this->double_value, this);
}

void Premise::conditionalCheck(int value)
{
   
    if(value == this->value)
    {
        this->status = true;
        //std::cout<<"true"<<std::endl;
    }
    else{
        this->status = false;
        //std::cout<< "false" << std::endl;
    }
        this->notifyConditions();
}

void Premise::conditionalCheck(bool value)
{
    
    if(value == (bool)this->value)
    {
        this->status = true;
        //std::cout<<"true"<<std::endl;
    }
    else{
        this->status = false;
        //std::cout<< "false" << std::endl;
    }
    this->notifyConditions();
}

void Premise::conditionalCheck(CustomString value)
{
    if(value == this->str_value)
    {
        this->status = true;
        //std::cout<<"true"<<std::endl;
    }
    else{
        this->status = false;
        //std::cout<< "false" << std::endl;
    }
    this->notifyConditions();
}

void Premise::conditionalCheck(char value)
{
    
    if(value == this->char_value)
    {
        this->status = true;
        //std::cout<<"true"<<std::endl;
    }
    else{
        this->status = false;
        //std::cout<< "false" << std::endl;
    }
    this->notifyConditions();
}

void Premise::conditionalCheck(double value)
{
    
    if(value == this->double_value)
    {
        this->status = true;
        //std::cout<<"true"<<std::endl;
    }
    else{
        this->status = false;
        //std::cout<< "false" << std::endl;
    }
    this->notifyConditions();
}

void Premise::referenceCondition(Condition* pcond)
{
    this->conditions.insertInfo(pcond);
}

void Premise::notifyConditions()    
{
    // std::cout << "previous:" << this->previous_status <<std::endl;
    // std::cout << "current:" << this->status <<std::endl;
    if(this->previous_status != this->status)
    {
        this->previous_status = this->status;
        
        List<Condition>::Element<Condition>* aux = this->conditions.getFirst();

        while(aux != nullptr)
        {
            aux->getInfo()->conditionalCheck(this->status);
            aux = aux->getNext();
        }
    }
}

