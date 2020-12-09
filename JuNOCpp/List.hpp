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
            Element<U>* getNext()
            {
                return pNext;
            }

            void setInfo(U* pI);
            void setInfo(const U* pI);
            U* getInfo();
        };

        void setAutoDel(bool del)
        {
            this->auto_delete = del;
        }

        List(bool del = true);
        ~List();

        void insertElement(Element<T>* pEl);
        void insertInfo(T* pInfo);
        void insertInfo(const T* pInfo);

        Element<T>* getFirst() {return pFirst;}
        Element<T>* getCurrent() {return pCurrent;}

        unsigned int counter;
    protected:
        Element<T>* pFirst;
        Element<T>* pCurrent;

        bool auto_delete;
    };

    template<class T>
    List<T>::List(bool del)
    {
        pFirst = nullptr;
        pCurrent = nullptr;
        this->auto_delete = del;
        this->counter = 0;
    }

    template<class T>
    List<T>::~List()
    {
        if(this->auto_delete)
        {
            Element<T>* pAux = pFirst;
            Element<T>* pAux2;

            pFirst = nullptr;
            pCurrent = nullptr;
            if(pAux)
                while(pAux->getNext() != nullptr)
                {
                    pAux2 = pAux->getNext();
                    delete (pAux);
                    pAux = pAux2;
                }
        }
    }

    template<class T>
    void List<T>::insertElement(Element<T>* pEl)
    {
        if(pEl != nullptr)
        {
            if(pFirst == nullptr)
            {
                pFirst = pEl;
                pFirst->setNext(nullptr);
                pCurrent = pFirst;
            }
            else
            {
                pEl->setNext(nullptr);
                pCurrent->setNext(pEl);
                pCurrent = pCurrent->getNext();
            }
        }
        this->counter++;
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
    void List<T>::insertInfo(const T* pInfo)
    {
        Element<T>* pElement;
        pElement = new Element<T>();
        pElement->setInfo(pInfo);
        insertElement(pElement);
    }

    template<class T>
    template<class U>
    List<T>::Element<U>::Element()
    {
    this->pNext = nullptr;
        this->pInfo = nullptr;
    }

    template<class T>
    template<class U>
    List<T>::Element<U>::~Element ( )
    {
        this->pNext = nullptr;
        this->pInfo = nullptr;
    }

    template<class T>
    template<class U>
    void List<T>::Element<U>::setNext(Element<U>* pP)
    {
        this->pNext = pP;
    }

    // template<class T>
    // template<class U>
    // List<T>::Element<U>* List<T>::Element<U>::getNext()
    // {
    //     return pNext;
    // }

    template<class T>
    template<class U>
    void List<T>::Element<U>::setInfo( U* pI)
    {
        pInfo = pI;
    }

    template<class T>
    template<class U>
    void List<T>::Element<U>::setInfo(const U* pI)
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