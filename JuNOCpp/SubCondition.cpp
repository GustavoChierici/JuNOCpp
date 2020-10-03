#include "SubCondition.hpp"

namespace JuNOCpp
{
    SubCondition::SubCondition(CustomString mode /* = "CONJUNCTION" */)
    {
        if(mode != "CONJUNCTION" && mode != "DISJUNCTION")
        {
            std::cout << "ERRO! SubCondition so pode ser do modo CONJUNCTION ou DISJUNCTION!" << std::endl;
            exit(1);
        }
        this->quantity = 0;
        this->approved_premises_and_subconds = 0;
        this->condition = nullptr;
        this->mode = mode;
        this->current_status = false;
        this->previous_status = false;

        if(this->mode == "DISJUNCTION")
            this->quantity = 1;
    }

    SubCondition::~SubCondition()
    {
    }

    void SubCondition::addPremise(Premise* prm)
    {
        if(this->mode == "CONJUNCTION")
            this->quantity++;
        prm->referenceSubCondition(this);
    }

    void SubCondition::referenceCondition(Condition* cond)
    {
        this->condition = cond;
    }

    void SubCondition::conditionalCheck(bool status)
    {
        if(status)
        {
            this->approved_premises_and_subconds++;

            if(this->approved_premises_and_subconds == this->quantity){
                //printf("true-condition\n");
                //printf("%dpremises\n", this->approved_premises_and_subconds);
                this->current_status = true;

            }
        }
        else
        {
            this->approved_premises_and_subconds--;
            // printf("%dpremises\n", this->approved_premises);
            // printf("false-condition\n");
            this->current_status = false;
        }

        if(this->current_status != this->previous_status)
        {
            this->previous_status = this->current_status;
            SubCondition* aux = dynamic_cast<SubCondition*>(this->condition);
            if(aux)
                aux->conditionalCheck(this->current_status);
            else
                this->condition->conditionalCheck(this->current_status);
        }
    }
}