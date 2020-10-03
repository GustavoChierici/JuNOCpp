#include "Premise.hpp"
#include "./Attributes/Integer.hpp"
#include "./Attributes/Boolean.hpp"
#include "./Condition.hpp"
#include "./SubCondition.hpp"
#include <iostream>
using namespace JuNOCpp;
using namespace Attributes;
Premise::Premise(CustomString mode/* = "EQUAL"*/)
{
    this->attr_reference = nullptr;
    this->status = false;
    this->previous_status = false;
    this->comp_int = nullptr;
    this->comp_double = nullptr;
    this->comp_str = nullptr;

    if(mode == "NOT_EQUAL" || mode == "!=")
    {
        this->mode = 0;
        this->comp_int = [](int a, int b)
        {
            return a != b;
        };
        this->comp_double = [](double a, double b)
        {
            return a != b;
        };
        this->comp_str = [](CustomString a, CustomString b)
        {
            return a != b;
        };
    }
    else if(mode == "EQUAL" || mode == "==")
    {
        this->mode = 1;
        this->comp_int = [](int a, int b)
        {
            return a == b;
        };
        this->comp_double = [](double a, double b)
        {
            return a == b;
        };
        this->comp_str = [](CustomString a, CustomString b)
        {
            return a == b;
        };
    }
    else if(mode == "GREATER_THAN" || mode == ">")
    {
        this->mode = 2;
        this->comp_int = [](int a, int b)
        {
            return a > b;
        };
        this->comp_double = [](double a, double b)
        {
            return a > b;
        };   
    }
    else if(mode == "GREATER_OR_EQUAL_THAN" || mode == ">=")
    {
        this->mode = 3;
        this->comp_int = [](int a, int b)
        {
            return a >= b;
        };
        this->comp_double = [](double a, double b)
        {
            return a >= b;
        };  
    }
    else if(mode == "LESS_THAN" || mode == "<")
    {
        this->mode = 4;
        this->comp_int = [](int a, int b)
        {
            return a < b;
        };
        this->comp_double = [](double a, double b)
        {
            return a < b;
        };  
    }
    else if(mode == "LESS_OR_EQUAL_THAN" || mode == "<=")
    {
        this->mode = 5;
        this->comp_int = [](int a, int b)
        {
            return a <= b;
        };
        this->comp_double = [](double a, double b)
        {
            return a <= b;
        };  
    }
}

Premise::~Premise()
{
}

Premise::Premise(Attributes::Attribute* attr, const int value, CustomString mode/* = "EQUAL"*/)
{
    if(mode == "NOT_EQUAL" || mode == "!=")
    {
        this->mode = 0;
        this->comp_int = [](int a, int b)
        {
            return a != b;
        };
        this->comp_double = [](double a, double b)
        {
            return a != b;
        };
        this->comp_str = [](CustomString a, CustomString b)
        {
            return a != b;
        };
    }
    else if(mode == "EQUAL" || mode == "==")
    {
        this->mode = 1;
        this->comp_int = [](int a, int b)
        {
            return a == b;
        };
        this->comp_double = [](double a, double b)
        {
            return a == b;
        };
        this->comp_str = [](CustomString a, CustomString b)
        {
            return a == b;
        };
    }
    else if(mode == "GREATER_THAN" || mode == ">")
    {
        this->mode = 2;
        this->comp_int = [](int a, int b)
        {
            return a > b;
        };
        this->comp_double = [](double a, double b)
        {
            return a > b;
        };   
    }
    else if(mode == "GREATER_OR_EQUAL_THAN" || mode == ">=")
    {
        this->mode = 3;
        this->comp_int = [](int a, int b)
        {
            return a >= b;
        };
        this->comp_double = [](double a, double b)
        {
            return a >= b;
        };  
    }
    else if(mode == "LESS_THAN" || mode == "<")
    {
        this->mode = 4;
        this->comp_int = [](int a, int b)
        {
            return a < b;
        };
        this->comp_double = [](double a, double b)
        {
            return a < b;
        };  
    }
    else if(mode == "LESS_OR_EQUAL_THAN" || mode == "<=")
    {
        this->mode = 5;
        this->comp_int = [](int a, int b)
        {
            return a <= b;
        };
        this->comp_double = [](double a, double b)
        {
            return a <= b;
        };  
    }

    this->status = false;
    this->previous_status = false;
    this->setAttribute(attr, value);
}

void Premise::setAttribute(Attribute* attr, int value)
{
    this->attr_reference = attr;
    this->value = value;
    if(this->mode != 1)
        this->attr_reference->getList()->insertInfo(this);
    else
        this->attr_reference->getTable()->insertValue(this->value, this);
}

void Premise::setAttribute(Attribute* attr, bool value)
{
    this->attr_reference = attr;
    this->value = int(value);
    if(this->mode != 1)
        this->attr_reference->getList()->insertInfo(this);
    else
        this->attr_reference->getTable()->insertValue(this->value, this);
}

void Premise::setAttribute(Attribute* attr, CustomString value)
{
    this->attr_reference = attr;
    this->str_value = value;
    if(this->mode != 1)
        this->attr_reference->getList()->insertInfo(this);
    else
        this->attr_reference->getTable()->insertValue(this->str_value, this);
}

void Premise::setAttribute(Attribute* attr, char value)
{
    this->attr_reference = attr;
    this->char_value = value;
    this->value = (int)value;
    if(this->mode != 1)
        this->attr_reference->getList()->insertInfo(this);
    else
        this->attr_reference->getTable()->insertValue(this->char_value, this);
}

void Premise::setAttribute(Attribute* attr, double value)
{
    this->attr_reference = attr;
    this->double_value = value;
    if(this->mode != 1)
        this->attr_reference->getList()->insertInfo(this);
    else
        this->attr_reference->getTable()->insertValue(this->double_value, this);
}

void Premise::conditionalCheck(int value)
{
    this->status = this->comp_int(value, this->value);
    this->notifyConditions();
}

void Premise::conditionalCheck(bool value)
{
    
    this->status = this->comp_int(value, this->value);
    this->notifyConditions();
}

void Premise::conditionalCheck(CustomString value)
{
    this->status = this->comp_str(value, this->str_value);
    this->notifyConditions();
}

void Premise::conditionalCheck(char value)
{
    this->status = this->comp_int(value, this->value);
    this->notifyConditions();
}

void Premise::conditionalCheck(double value)
{
    this->status = this->comp_double(value, this->double_value);
    this->notifyConditions();
}

void Premise::referenceCondition(Condition* pcond)
{
    this->conditions.insertInfo(pcond);
}

void Premise::referenceSubCondition(SubCondition* subcond)
{
    this->subconditions.insertInfo(subcond);
}

void Premise::notifyConditions()    
{
    // std::cout << "previous:" << this->previous_status <<std::endl;
    // std::cout << "current:" << this->status <<std::endl;
    if(this->previous_status != this->status)
    {
        this->previous_status = this->status;
        
        List<Condition>::Element<Condition>* aux = this->conditions.getFirst();
        List<SubCondition>::Element<SubCondition>* aux2 = this->subconditions.getFirst();

        while(aux != nullptr)
        {
            aux->getInfo()->conditionalCheck(this->status);
            aux = aux->getNext();
        }

        while(aux2 != nullptr)
        {
            aux2->getInfo()->conditionalCheck(this->status);
            aux2 = aux2->getNext();
        }

    }
}

