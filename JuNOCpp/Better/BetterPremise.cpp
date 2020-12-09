// #include "BetterPremise.hpp"
// #include "BetterAttribute.hpp"
// #include "./BetterCondition.hpp"
// #include <iostream>
// using namespace JuNOCpp;
// using namespace Attributes;

// // template <class TYPE>
// // BetterPremise<TYPE>::BetterPremise(CustomString mode/* = "EQUAL"*/)
// // {
// // }

// template <class TYPE>
// BetterPremise<TYPE>::~BetterPremise()
// {
// }

// template <class TYPE>
// void BetterPremise<TYPE>::setOperation(const int op /* = BetterPremise::EQUAL*/)
// {
//     switch (op)
//     {
//     case BetterPremise::DIFFERENT:
//         this->cmp = [](TYPE value1, TYPE value2){
//             return value1 != value2;
//         };
//         break;
//     case BetterPremise::EQUAL:
//         this->cmp = [](TYPE value1, TYPE value2){
//             return value1 == value2;
//         };
//         break;
//     case BetterPremise::GREATHER_THAN:
//         this->cmp = [](TYPE value1, TYPE value2){
//             return value1 > value2;
//         };
//         break;
//     case BetterPremise::GREATHER_OR_EQUAL_THAN:
//         this->cmp = [](TYPE value1, TYPE value2){
//             return value1 >= value2;
//         };
//         break;
//     case BetterPremise::LESS_THAN:
//         this->cmp = [](TYPE value1, TYPE value2){
//             return value1 < value2;
//         };
//         break;
//     case BetterPremise::LESS_OR_EQUAL_THAN:
//         this->cmp = [](TYPE value1, TYPE value2){
//             return value1 <= value2;
//         };
//         break;
//     default:
//         std::cout << "PREMISE INVÁLIDO!" << std::endl;
//         exit(1);
//         break;
//     }
// }

// template <class TYPE>
// void BetterPremise<TYPE>::setBetterAttributes(BetterAttribute<TYPE>* b_attr1, BetterAttribute<TYPE>* b_attr2)
// {
//     this->attr1 = b_attr1;
//     this->attr2 = b_attr2;

//     b_attr1->referenceBetterPremise(this);
//     b_attr2->referenceBetterPremise(this);
    
//     this->conditionalCheck();
// }

// template <class TYPE>
// void BetterPremise<TYPE>::conditionalCheck(bool renotify /* = false */)
// {
//     this->status = this->cmp(this->attr1->getCurrentStatus(), this->attr2->getCurrentStatus());
//     this->notifyBetterConditions();
// }

// template <class TYPE>
// void BetterPremise<TYPE>::notifyBetterConditions()    
// {
//     // std::cout << "previous:" << this->previous_status <<std::endl;
//     // std::cout << "current:" << this->status <<std::endl;
//     if(this->previous_status != this->status)
//     {
//         this->previous_status = this->status;
        
//         List<BetterCondition>::Element<BetterCondition>* aux = this->conditions.getFirst();

//         while(aux != nullptr)
//         {
//             aux->getInfo()->conditionalCheck(this->status);
//             aux = aux->getNext();
//         }
//     }
// }

// template <class TYPE>
// BetterCondition BetterPremise<TYPE>::operator &&(BetterPremise<TYPE>& b_premise)
// {
//     BetterCondition aux;
//     aux.addBetterPremise(this);
//     aux.addBetterPremise(&b_premise);
//     aux.setQuantity(2);

//     this->
    
//     return aux;
// }

// template <class TYPE>
// BetterCondition BetterPremise<TYPE>::operator ||(BetterPremise<TYPE>& b_premise)
// {
//     BetterCondition aux;
//     aux.addBetterPremise(this);
//     aux.addBetterPremise(&b_premise);
//     aux.setQuantity(1);
    
//     return aux;
// }

// template <class TYPE>
// BetterCondition BetterPremise<TYPE>::operator &&(BetterCondition& b_condition)
// {
//     BetterCondition aux;
//     aux.addBetterPremise(this);
//     aux.addBetterCondition(&b_condition);
//     aux.setQuantity(2);
    
//     return aux;
// }

// template <class TYPE>
// BetterCondition BetterPremise<TYPE>::operator ||(BetterCondition& b_condition)
// {
//     BetterCondition aux;
//     aux.addBetterPremise(this);
//     aux.addBetterCondition(&b_condition);
//     aux.setQuantity(1);
    
//     return aux;
// }

