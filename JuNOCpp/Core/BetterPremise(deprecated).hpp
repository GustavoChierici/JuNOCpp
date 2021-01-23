#ifndef BETTER_PREMISE_HPP
#define BETTER_PREMISE_HPP
#include <iostream>
#include "../CustomString.hpp"
#include "./CoreAttribute.hpp"
#include "./CoreCondition.hpp"
#include "./Impertinent.hpp"
namespace JuNOCpp
{
    template<class TYPE>
    class BetterPremise: public Impertinent, public Notifier, public Notifiable
    {
    private:
        Attributes::BetterAttribute<TYPE>* attr1;
        Attributes::BetterAttribute<TYPE>* attr2;
        TYPE value;
        bool status;
        bool previous_status;
        int operation;
        bool (*cmp)(TYPE, TYPE);

    public:
        enum Operation {
            DIFFERENT = 0,
            EQUAL,
            GREATER_THAN,
            GREATER_OR_EQUAL_THAN,
            LESS_THAN,
            LESS_OR_EQUAL_THAN
        };

    public:
        BetterPremise(CustomString name = "UnnamedPremise",
            Attributes::BetterAttribute<TYPE>* at1 = nullptr,
            Attributes::BetterAttribute<TYPE>* at2 = nullptr,
            Operation operation = 1);
        BetterPremise(CustomString name,
            Attributes::BetterAttribute<TYPE>* at1,
            const TYPE value,
            Operation operation);
        ~BetterPremise();

        void setOperation(Operation op = BetterPremise::EQUAL);

        void setBetterAttribute(Attributes::BetterAttribute<TYPE>* b_attr1, Attributes::BetterAttribute<TYPE>* b_attr2);
        void setBetterAttribute(Attributes::BetterAttribute<TYPE>* b_attr1, TYPE value);

        void referenceBetterCondition(BetterCondition* b_cond);

        void update(const bool renotify = false);
        void update(const bool renotify, const bool status) {}

        void makeImpertinent();
        /**
         * Ativa a Premise impertinente
         * 
         */
        void activate() override
        {
            #ifdef SHOW_NOP_LOGGER
                Utils::NOPLogger::Get().writeImpertinentActivated(name, this);

                Utils::NOPLogger::Get().incrementIdentation(); 
            #endif // SHOW_NOP_LOGGER

            this->attr1->insert(this->shared_from_this());
            if(this->attr2)
                this->attr2->insert(this->shared_from_this());

            update();

            #ifdef SHOW_NOP_LOGGER
                Utils::NOPLogger::Get().decrementIdentation();
            #endif // SHOW_NOP_LOGGER 
        }
        /**
         * Desativa a Premise impertinente
         * 
         */
        void deactivate() override
        {
            #ifdef SHOW_NOP_LOGGER
                Utils::NOPLogger::Get().writeImpertinentDeactivated(name, this);

                Utils::NOPLogger::Get().incrementIdentation(); 
            #endif // SHOW_NOP_LOGGER

            this->attr1->remove(this->shared_from_this());
            if(this->attr2)
                this->attr2->remove(this->shared_from_this());

            if(status)
                notify(false, false);

            #ifdef SHOW_NOP_LOGGER
                Utils::NOPLogger::Get().decrementIdentation();
            #endif // SHOW_NOP_LOGGER 
        }

        template <class OT>
        BetterCondition& operator &&(BetterPremise<OT>& b_premise);
        template <class OT>
        BetterCondition& operator &&(BetterPremise<OT>&& b_premise);
        template <class OT>
        BetterCondition& operator ||(BetterPremise<OT>& b_premise);
        template <class OT>
        BetterCondition& operator ||(BetterPremise<OT>&& b_premise);

        BetterCondition& operator &&(BetterCondition& b_condition);
        BetterCondition& operator &&(BetterCondition&& b_condition);
        BetterCondition& operator ||(BetterCondition& b_condition);
        BetterCondition& operator ||(BetterCondition&& b_condition);

        bool operator==(BetterPremise<TYPE>& premise)
        {

            if(this->attr1 == premise.attr1 and this->attr2 == premise.attr2 and this->value == premise.value and this->operation == premise.operation)
            {
                return true;
            }

            return false;
        }

        operator BetterCondition&();
    };

    /**
     * Construtor
     * 
     * @tparam TYPE 
     */
    template <class TYPE>
    BetterPremise<TYPE>::BetterPremise(CustomString name,
        Attributes::BetterAttribute<TYPE>* at1,
        Attributes::BetterAttribute<TYPE>* at2,
        Operation operation) : 
    Notifiable(name),
    attr1{at1}, 
    attr2{at2},
    status{false}, 
    previous_status{false}
    {
        setOperation(operation);
    }

    /**
     * Construtor
     * 
     * @tparam TYPE 
     */
    template <class TYPE>
    BetterPremise<TYPE>::BetterPremise(CustomString name,
        Attributes::BetterAttribute<TYPE>* at1,
        const TYPE value,
        Operation operation) : 
    Notifiable(name),
    attr1{at1}, 
    value{value},
    status{false}, 
    previous_status{false}
    {
        setOperation(operation);
    }

    /**
     * Destrutor
     * 
     * @tparam TYPE 
     */
    template <class TYPE>
    BetterPremise<TYPE>::~BetterPremise()
    {
    }

    /**
     * Define o lambda responsável pela operação de comparação da Premise
     * 
     * @tparam TYPE 
     */
    template <class TYPE>
    void BetterPremise<TYPE>::setOperation(Operation op /* = BetterPremise::EQUAL*/)
    {
        operation = op;

        switch (op)
        {
        case BetterPremise::DIFFERENT:
            this->cmp = [](TYPE value1, TYPE value2){
                return value1 != value2;
            };
            break;
        case BetterPremise::EQUAL:
            this->cmp = [](TYPE value1, TYPE value2){
                return value1 == value2;
            };
            break;
        case BetterPremise::GREATER_THAN:
            this->cmp = [](TYPE value1, TYPE value2){
                return value1 > value2;
            };
            break;
        case BetterPremise::GREATER_OR_EQUAL_THAN:
            this->cmp = [](TYPE value1, TYPE value2){
                return value1 >= value2;
            };
            break;
        case BetterPremise::LESS_THAN:
            this->cmp = [](TYPE value1, TYPE value2){
                return value1 < value2;
            };
            break;
        case BetterPremise::LESS_OR_EQUAL_THAN:
            this->cmp = [](TYPE value1, TYPE value2){
                return value1 <= value2;
            };
            break;
        default:
            std::cout << "PREMISE INVÁLIDO!" << std::endl;
            exit(1);
            break;
        }
    }

    /**
     * Faz a ligação entre a Premise e os Attributes dos quais ela depende (2 Attributes)
     * 
     * @tparam TYPE 
     * @param b_attr1 
     * @param b_attr2 
     */
    template <class TYPE>
    void BetterPremise<TYPE>::setBetterAttribute(Attributes::BetterAttribute<TYPE>* b_attr1, Attributes::BetterAttribute<TYPE>* b_attr2)
    {
        this->attr1 = b_attr1;
        this->attr2 = b_attr2;
        
        //this->conditionalCheck();
    }

    /**
     * Faz a ligação entre a Premise e os Attributes dos quais ela depende (1 Attribute e 1 valor constante)
     * 
     * @tparam TYPE 
     * @param b_attr1 
     * @param b_attr2 
     */
    template <class TYPE>
    void BetterPremise<TYPE>::setBetterAttribute(Attributes::BetterAttribute<TYPE>* b_attr1, TYPE value)
    {
        this->attr1 = b_attr1;
        this->value = value;
        // b_attr1->insert(shared_from_this());
        
        //this->conditionalCheck();
    }

    /**
     * Faz a ligação entre a Premise e a Condition que depende dela
     * 
     * @tparam TYPE 
     * @param b_condition 
     */
    template <class TYPE>
    void BetterPremise<TYPE>::referenceBetterCondition(BetterCondition* b_condition)
    {
        this->conditions.insertInfo(*b_condition);
    }

    /**
     * Atualiza o status da Premise após ela ser notificada por um Attribute
     * 
     * @tparam TYPE 
     * @param renotify 
     */
    template <class TYPE>
    void BetterPremise<TYPE>::update(const bool renotify)
    {
        if(this->attr2)
            this->status = this->cmp(this->attr1->getCurrentStatus(), this->attr2->getCurrentStatus());
        else
            this->status = this->cmp(this->attr1->getCurrentStatus(), this->value);
        if(renotify || this->status != this->previous_status)
        {
            #ifdef SHOW_NOP_LOGGER
                Utils::NOPLogger::Get().writeNotifying(name, this, status, renotify);
                
                Utils::NOPLogger::Get().incrementIdentation();
            #endif // SHOW_NOP_LOGGER

            this->previous_status = this->status;
            this->notify(renotify, this->status);

            #ifdef SHOW_NOP_LOGGER
                Utils::NOPLogger::Get().decrementIdentation();
            #endif // SHOW_NOP_LOGGER
        }
    }

    /**
     * Transforma a Premise em impertinente
     * 
     * @tparam TYPE 
     */
    template <class TYPE>
    void BetterPremise<TYPE>::makeImpertinent()
    { 
        this->impertinent = true; 

        this->attr1->addImpertinent(this->shared_from_this());
        this->attr1->remove(this->shared_from_this());
        if(this->attr2)
        {
            this->attr2->addImpertinent(this->shared_from_this());
            this->attr2->remove(this->shared_from_this());
        }
    }

    /**
     * Cria e retorna uma Condition do tipo CONJUNCTION
     * 
     * @tparam TYPE 
     * @tparam OT 
     * @param b_premise 
     * @return BetterCondition& 
     */
    template <class TYPE>
    template <class OT>
    BetterCondition& BetterPremise<TYPE>::operator &&(BetterPremise<OT>& b_premise)
    {
        #ifdef USE_CUSTOM_SMART_PTRS
            shared_ptr<BetterCondition> condition(new BetterCondition());
        #else
            shared_ptr<BetterCondition> condition = std::make_shared<BetterCondition>(*new BetterCondition());
        #endif // USE_CUSTOM_SMART_PTRS

        condition->setQuantity(2);
        condition->setMode(BetterCondition::CONJUNCTION);

        if(this->isImpertinent())
        {
            condition->incCountImpertinents();
            condition->addImpertinent(this);
        }
        if(b_premise.isImpertinent())
        {
            condition->incCountImpertinents();
            condition->addImpertinent(&b_premise);
        }
        // std::cout << condition->count_impertinents << std::endl;
        this->insert(condition);
        b_premise.insert(condition);
        
        return *condition;
    }

    /**
     * Cria e retorna uma Condition do tipo CONJUNCTION
     * 
     * @tparam TYPE 
     * @tparam OT 
     * @param b_premise 
     * @return BetterCondition& 
     */
    template <class TYPE>
    template <class OT>
    BetterCondition& BetterPremise<TYPE>::operator &&(BetterPremise<OT>&& b_premise)
    {
        #ifdef USE_CUSTOM_SMART_PTRS
            shared_ptr<BetterCondition> condition(new BetterCondition());
        #else
            shared_ptr<BetterCondition> condition = std::make_shared<BetterCondition>(*new BetterCondition());
        #endif // USE_CUSTOM_SMART_PTRS
        condition->setQuantity(2);
        condition->setMode(BetterCondition::CONJUNCTION);

        this->insert(condition);
        b_premise.insert(condition);
        
        return *condition;
    }

    /**
     * Cria e retorna uma Condition do tipo DISJUNCTION
     * 
     * @tparam TYPE 
     * @tparam OT 
     * @param b_premise 
     * @return BetterCondition& 
     */
    template <class TYPE>
    template <class OT>
    BetterCondition& BetterPremise<TYPE>::operator ||(BetterPremise<OT>& b_premise)
    {
        #ifdef USE_CUSTOM_SMART_PTRS
            shared_ptr<BetterCondition> condition(new BetterCondition());
        #else
            shared_ptr<BetterCondition> condition = std::make_shared<BetterCondition>(*new BetterCondition());
        #endif // USE_CUSTOM_SMART_PTRS
        condition->setQuantity(1);
        condition->setMode(BetterCondition::DISJUNCTION);

        this->insert(condition);
        b_premise.insert(condition);
        
        return *condition;
    }

    /**
     * Cria e retorna uma Condition do tipo DISJUNCTION
     * 
     * @tparam TYPE 
     * @tparam OT 
     * @param b_premise 
     * @return BetterCondition& 
     */
    template <class TYPE>
    template <class OT>
    BetterCondition& BetterPremise<TYPE>::operator ||(BetterPremise<OT>&& b_premise)
    {
        #ifdef USE_CUSTOM_SMART_PTRS
            shared_ptr<BetterCondition> condition(new BetterCondition());
        #else
            shared_ptr<BetterCondition> condition = std::make_shared<BetterCondition>(*new BetterCondition());
        #endif // USE_CUSTOM_SMART_PTRS
        condition->setQuantity(1);
        condition->setMode(BetterCondition::DISJUNCTION);

        this->insert(condition);
        b_premise.insert(condition);
        
        return *condition;
    }

    /**
     * Cria e retorna uma Condition do tipo CONJUNCTION
     * 
     * @tparam TYPE 
     * @param b_condition
     * @return BetterCondition& 
     */
    template <class TYPE>
    BetterCondition& BetterPremise<TYPE>::operator &&(BetterCondition& b_condition)
    {
        if((b_condition.getMode() == BetterCondition::CONJUNCTION or b_condition.getMode() == BetterCondition::SINGLE) and !b_condition.persistant)
        {
            this->insert(b_condition.shared_from_this());
            b_condition.setQuantity(b_condition.quantity + 1);
            
            return b_condition;
        }
        else
        {
            #ifdef USE_CUSTOM_SMART_PTRS
                shared_ptr<BetterCondition> condition(new BetterCondition());
            #else
                shared_ptr<BetterCondition> condition = std::make_shared<BetterCondition>(*new BetterCondition());
            #endif // USE_CUSTOM_SMART_PTRS

            this->insert(condition);
            b_condition.insert(condition);
            
            return *condition;
        }
    }

    /**
     * Cria e retorna uma Condition do tipo CONJUNCTION
     * 
     * @tparam TYPE 
     * @param b_condition 
     * @return BetterCondition& 
     */
    template <class TYPE>
    BetterCondition& BetterPremise<TYPE>::operator &&(BetterCondition&& b_condition)
    {
        if((b_condition.mode == BetterCondition::CONJUNCTION or b_condition.mode == BetterCondition::SINGLE) and !b_condition.persistant)
        {
            this->insert(b_condition.shared_from_this());
            b_condition.setQuantity(b_condition.quantity + 1);
            
            return b_condition;
        }
        else
        {
            #ifdef USE_CUSTOM_SMART_PTRS
                shared_ptr<BetterCondition> condition(new BetterCondition());
            #else
                shared_ptr<BetterCondition> condition = std::make_shared<BetterCondition>(*new BetterCondition());
            #endif // USE_CUSTOM_SMART_PTRS
            condition->setQuantity(2);
            condition->setMode(BetterCondition::CONJUNCTION);

            this->insert(condition);
            b_condition.insert(condition);
            
            return *condition;
        }
    }

    /**
     * Cria e retorna uma Condition do tipo DISJUNCTION
     * 
     * @tparam TYPE 
     * @param b_condition 
     * @return BetterCondition& 
     */
    template <class TYPE>
    BetterCondition& BetterPremise<TYPE>::operator ||(BetterCondition& b_condition)
    {
        if ((b_condition.getMode() == BetterCondition::DISJUNCTION or b_condition.getMode() == BetterCondition::SINGLE) and !b_condition.persistant)
        {
            this->insert(b_condition.shared_from_this());

            return b_condition;
        }
        else
        {
            #ifdef USE_CUSTOM_SMART_PTRS
                shared_ptr<BetterCondition> condition(new BetterCondition());
            #else
                shared_ptr<BetterCondition> condition = std::make_shared<BetterCondition>(*new BetterCondition());
            #endif // USE_CUSTOM_SMART_PTRS
            condition->setQuantity(1);
            condition->setMode(BetterCondition::DISJUNCTION);

            this->insert(condition);
            b_condition.insert(condition);
            
            return *condition;
        }
    }

    /**
     * Cria e retorna uma Condition do tipo DISJUNCTION
     * 
     * @tparam TYPE  
     * @param b_condition 
     * @return BetterCondition& 
     */
    template <class TYPE>
    BetterCondition& BetterPremise<TYPE>::operator ||(BetterCondition&& b_condition)
    {
        if ((b_condition.mode == BetterCondition::DISJUNCTION or b_condition.mode == BetterCondition::SINGLE) and !b_condition.persistant)
        {
            this->insert(b_condition.shared_from_this());

            return b_condition;
        }
        else
        {
            #ifdef USE_CUSTOM_SMART_PTRS
                shared_ptr<BetterCondition> condition(new BetterCondition());
            #else
                shared_ptr<BetterCondition> condition = std::make_shared<BetterCondition>(*new BetterCondition());
            #endif // USE_CUSTOM_SMART_PTRS
            condition->setQuantity(1);
            condition->setMode(BetterCondition::DISJUNCTION);

            this->insert(condition);
            b_condition.insert(condition);
            
            return *condition;
        }
    }

    /**
     * "Converte" a Premise numa BetterCondition do tipo SINGLE
     * 
     * @tparam TYPE 
     * @return JuNOCpp::BetterCondition& 
     */
    template <class TYPE>
    BetterPremise<TYPE>::operator JuNOCpp::BetterCondition&()
    {
        #ifdef USE_CUSTOM_SMART_PTRS
            shared_ptr<BetterCondition> condition(new BetterCondition());
        #else
            shared_ptr<BetterCondition> condition = std::make_shared<BetterCondition>(*new BetterCondition());
        #endif // USE_CUSTOM_SMART_PTRS
        condition->setQuantity(1);
        condition->setMode(BetterCondition::SINGLE);

        this->insert(condition);
        
        return *condition;
    }
}

#endif