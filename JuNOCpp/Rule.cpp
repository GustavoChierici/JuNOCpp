#include "Rule.hpp"
#include "Action.hpp"
#include <iostream>

namespace JuNOCpp
{
    using namespace Attributes;
    int Rule::counter = 0;
    /**************************************** 
    * Construtores/Destrutores
    ****************************************/
    Rule::Rule(CustomString mode /* = "CONJUNCTION" */, int rl_mode /* = Rule::COMPLETE */)
    {
        this->cond = new Condition(mode);
        this->cond->referenceRule(this);

        this->mode = rl_mode;

        switch(rl_mode)
        {
            case Rule::COMPLETE:
                this->action = new Action(this);
                this->attr = nullptr;
                this->exec_value = nullptr;
                this->exec = [](Attributes::Attribute* attr = nullptr, void* value = nullptr, Action* act = nullptr)
                {
                    act->callInstigations();
                };
                break;
            case Rule::INCOMPLETE:
                this->action = nullptr;
                break;
            case Rule::DERIVED:
                // Precisa ser implementada ainda
                this->action = nullptr;
                this->exec = nullptr;
                this->exec_value = nullptr;
                this->attr = nullptr;
                break;
        }
    }

    Rule::~Rule()
    {
        delete this->cond;
    }


    /***************************************
    *  Adicionar Premises
    ****************************************/
    void Rule::addPremise(Attributes::Integer* pattr, const int value, CustomString mode/* = "EQUAL"*/)
    {
        Premise* aux = new Premise(mode);
        aux->setAttribute(pattr, value);
        this->cond->addPremise(aux);
    }

    void Rule::addPremise(Attributes::Boolean* pattr, const bool value, CustomString mode/* = "EQUAL"*/)
    {
        Premise* aux = new Premise(mode);
        aux->setAttribute(pattr, value);
        this->cond->addPremise(aux);
    }

    void Rule::addPremise(Attributes::String* pattr, CustomString value, CustomString mode/* = "EQUAL"*/)
    {
        Premise* aux = new Premise(mode);
        aux->setAttribute(pattr, value);
        this->cond->addPremise(aux);
    }

    void Rule::addPremise(Attributes::Char* pattr, const char value, CustomString mode/* = "EQUAL"*/)
    {
        Premise* aux = new Premise(mode);
        aux->setAttribute(pattr, value);
        this->cond->addPremise(aux);
    }

    void Rule::addPremise(Attributes::Double* pattr, const double value, CustomString mode/* = "EQUAL"*/)
    {
        Premise* aux = new Premise(mode);
        aux->setAttribute(pattr, value);
        this->cond->addPremise(aux);
    }

    void Rule::addPremise(Premise* pprm)
    {
        this->cond->addPremise(pprm);
    }

    /***************************************
    *  Adicionar SubConditions
    ****************************************/
    void Rule::addSubcondition(CustomString mode /* = "CONJUNCTION" */)
    {
        this->cond->addSubCondition(mode);
    }

    void Rule::addSubcondition(SubCondition* subcond)
    {
        this->cond->addSubCondition(subcond);
    }

     /***************************************
    *  Adicionar Premises a SubCondition
    ****************************************/
   void Rule::addPremiseToSubCondition(Attributes::Integer* pattr, const int value, CustomString mode/* = "EQUAL"*/)
   {
       Premise* aux = new Premise(mode);
       aux->setAttribute(pattr, value);
       this->cond->addPremiseToSubCondition(aux);
   }

   void Rule::addPremiseToSubCondition(Attributes::Boolean* pattr, const bool value, CustomString mode/* = "EQUAL"*/)
   {
       Premise* aux = new Premise(mode);
       aux->setAttribute(pattr, value);
       this->cond->addPremiseToSubCondition(aux);
   }

   void Rule::addPremiseToSubCondition(Attributes::String* pattr, CustomString value, CustomString mode/* = "EQUAL"*/)
   {
       Premise* aux = new Premise(mode);
       aux->setAttribute(pattr, value);
       this->cond->addPremiseToSubCondition(aux);
   }

   void Rule::addPremiseToSubCondition(Attributes::Char* pattr, const char value, CustomString mode/* = "EQUAL"*/)
   {
       Premise* aux = new Premise(mode);
       aux->setAttribute(pattr, value);
       this->cond->addPremiseToSubCondition(aux);
   }

   void Rule::addPremiseToSubCondition(Attributes::Double* pattr, const double value, CustomString mode/* = "EQUAL"*/)
   {
       Premise* aux = new Premise(mode);
       aux->setAttribute(pattr, value);
       this->cond->addPremiseToSubCondition(aux);
   }

    void Rule::addPremiseToSubCondition(Premise* pprm)
    {
        this->cond->addPremiseToSubCondition(pprm);
    }

    void Rule::referenceAttr(Attributes::Integer* attr, int exec_value)
    {
        this->attr = attr;
        this->exec_value = &exec_value;

        this->exec = [](Attributes::Attribute* attr = nullptr, void* value = nullptr, Action* act = nullptr){
            static_cast<Attributes::Integer*>(attr)->setStatus(*(int*)value);
        };
    }

    void Rule::referenceAttr(Attributes::Boolean* attr, bool exec_value)
    {
        this->attr = attr;
        this->exec_value = &exec_value;

        this->exec = [](Attributes::Attribute* attr = nullptr, void* value = nullptr, Action* act = nullptr){
            static_cast<Attributes::Boolean*>(attr)->setStatus(*(bool*)value);
        };
    }

    void Rule::referenceAttr(Attributes::String* attr, CustomString exec_value)
    {
        this->attr = attr;
        this->exec_value = &exec_value;

        this->exec = [](Attributes::Attribute* attr = nullptr, void* value = nullptr, Action* act = nullptr){
            static_cast<Attributes::String*>(attr)->setStatus((const char*)value);
        };
    }

    void Rule::referenceAttr(Attributes::Char* attr, char exec_value)
    {
        this->attr = attr;
        this->exec_value = &exec_value;

        this->exec = [](Attributes::Attribute* attr = nullptr, void* value = nullptr, Action* act = nullptr){
            static_cast<Attributes::Char*>(attr)->setStatus(*(char*)value);
        };
    }

    void Rule::referenceAttr(Attributes::Double* attr, double exec_value)
    {
        this->attr = attr;
        this->exec_value = &exec_value;

        this->exec = [](Attributes::Attribute* attr = nullptr, void* value = nullptr, Action* act = nullptr){
            static_cast<Attributes::Double*>(attr)->setStatus(*(double*)value);
        };
    }

    void Rule::addInstigation(Instigation* inst)
    {
        this->action->addInstigation(inst);
    }

    void Rule::addInstigation(Method* mt)
    {
        this->action->addInstigation(mt);
    }

    void Rule::addInstigation(Attributes::Integer* attr, int value)
    {
        this->action->addInstigation(attr, value);
    }

    void Rule::addInstigation(Attributes::Boolean* attr, bool value)
    {
        this->action->addInstigation(attr, value);
    }

    void Rule::addInstigation(Attributes::Double* attr, double value)
    {
        this->action->addInstigation(attr, value);
    }

    void Rule::addInstigation(Attributes::Char* attr, char value)
    {
        this->action->addInstigation(attr, value);
    }

    void Rule::addInstigation(Attributes::String* attr, const char* value)
    {
        this->action->addInstigation(attr, value);
    }

    void Rule::execute() //Método execute da Rule (Derived) para modificar diretamente um Attribute, sem a necessidade de uma Action, Instigations e Methods
    {
        //std::cout << "APROVADA - " << this << std::endl;
        Rule::counter++;
        this->exec(this->attr, this->exec_value, this->action);
    }
}