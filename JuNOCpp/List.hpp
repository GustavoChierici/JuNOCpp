#pragma once

#include <stdlib.h>

namespace JuNOCpp
{

    template<class T>
    class List
    {
    public:
        template<class U>
        class Element
        {
        protected:
            Element<U>*  pNext;
            U* pInfo;

        public:
            Element();
            ~Element();

            void setNext(Element<U>* pP);
            Element<U>* getNext();

            void setInfo(U* pI);
            U* getInfo();
        };

        List();
        ~List();

        void insertElement(Element<T>* pEl);
        void insertInfo(T* pInfo);

        Element<T>* getFirst() {return pFirst;}
        Element<T>* getCurrent() {return pCurrent;}
    protected:
        Element<T>* pFirst;
        Element<T>* pCurrent;
    };

    template<class T>
    List<T>::List()
    {
        pFirst = NULL;
        pCurrent = NULL;
    }

    template<class T>
    List<T>::~List()
    {
        Element<T>* pAux = pFirst;
        Element<T>* pAux2;

        pFirst = NULL;
        pCurrent = NULL;

        while(pAux->getNext() != NULL)
        {
            pAux2 = pAux->getNext();
            delete (pAux);
            pAux = pAux2;
        }
    }

    template<class T>
    void List<T>::insertElement(Element<T>* pEl)
    {
        if(pEl != NULL)
        {
            if(pFirst == NULL)
            {
                pFirst = pEl;
                pFirst->setNext(NULL);
                pCurrent = pFirst;
            }
            else
            {
                pEl->setNext(NULL);
                pCurrent->setNext(pEl);
                pCurrent = pCurrent->getNext();
            }
        }
    }

    template<class T>
    void List<T>::insertInfo(T* pInfo)
    {
        Element<T>* pElement;
        pElement = new Element<T>();
        pElement->setInfo (pInfo);
        insertElement(pElement);
    }

    template<class T>
    template<class U>
    List<T>::Element<U>::Element()
    {
    this->pNext = NULL;
        this->pInfo = NULL;
    }

    template<class T>
    template<class U>
    List<T>::Element<U>::~Element ( )
    {
        this->pNext = NULL;
        this->pInfo = NULL;
    }

    template<class T>
    template<class U>
    void List<T>::Element<U>::setNext(Element<U>* pP)
    {
        this->pNext = pP;
    }

    template<class T>
    template<class U>
    List<T>::Element<U>* List<T>::Element<U>::getNext( )
    {
        return pNext;
    }

    template<class T>
    template<class U>
    void List<T>::Element<U>::setInfo( U* pI)
    {
        pInfo = pI;
    }

    template<class T>
    template<class U>
    U* List<T>::Element<U>::getInfo()
    {
        return pInfo;
    }

} // namespace JuNOCpp