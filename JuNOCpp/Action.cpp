#include "Action.hpp"

namespace JuNOCpp
{
    Action::Action(Rule* rl /* = nullptr */)
    {
        this->rule;
    }

    Action::~Action()
    {
    }

    /***************************************
    *  Adicionar Instigations
    ****************************************/

    void Action::addInstigation(Instigation* inst)
    {
        this->instigations.insertInfo(inst);
    }

    void Action::addInstigation(Method* mt)
    {
        Instigation* aux = new Instigation(mt);
        this->instigations.insertInfo(aux);
    }

    void Action::addInstigation(Attributes::Integer* attr, int value)
    {
        Instigation* aux = new Instigation(attr, value);
        this->instigations.insertInfo(aux);
    }

    void Action::addInstigation(Attributes::Boolean* attr, bool value)
    {
        Instigation* aux = new Instigation(attr, value);
        this->instigations.insertInfo(aux);
    }

    void Action::addInstigation(Attributes::Double* attr, double value)
    {
        Instigation* aux = new Instigation(attr, value);
        this->instigations.insertInfo(aux);
    }

    void Action::addInstigation(Attributes::Char* attr, char value)
    {
        Instigation* aux = new Instigation(attr, value);
        this->instigations.insertInfo(aux);
    }

    void Action::addInstigation(Attributes::String* attr, const char* value)
    {
        Instigation* aux = new Instigation(attr, value);
        this->instigations.insertInfo(aux);
    }

    void Action::setRule(Rule* rl)
    {
        this->rule = rl;
    }

    void Action::callInstigations()
    {
        List<Instigation>::Element<Instigation>* aux = this->instigations.getFirst();

        while(aux != nullptr)
        {
            aux->getInfo()->call();
            aux = aux->getNext();
        }
    }
}