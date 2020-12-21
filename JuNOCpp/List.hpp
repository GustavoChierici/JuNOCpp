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
            U info;

        public:
            Element();
            ~Element();

            void setNext(Element<U>* pP);
            Element<U>* getNext()
            {
                return pNext;
            }

            void setInfo(U pI);
            U getInfo();
        };

        void setAutoDel(bool del)
        {
            this->auto_delete = del;
        }

        List(bool del = true);
        ~List();

        void insertElement(Element<T>* pEl);
        void insertInfo(T info);
        void removeInfo(T info);

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
    void List<T>::insertInfo(T info)
    {
        Element<T>* pElement;
        pElement = new Element<T>();
        pElement->setInfo(info);
        insertElement(pElement);
    }

    template<class T>
    void List<T>::removeInfo(T info)
    {
        Element<T>* aux = this->getFirst();
        Element<T>* aux2;

        while(aux)
        {
            if(aux->getNext())
            {
                if(aux->getNext()->getInfo() == info)
                {
                    aux2 = aux->getNext();
                    aux->setNext(aux2->getNext());
                    delete aux2;
                }
            }
            else if(aux->getInfo() == info)
            {
                delete aux;
            }
            aux = aux->getNext();
        }
    }

    template<class T>
    template<class U>
    List<T>::Element<U>::Element()
    {
        this->pNext = nullptr;
    }

    template<class T>
    template<class U>
    List<T>::Element<U>::~Element ( )
    {
        this->pNext = nullptr;
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
    void List<T>::Element<U>::setInfo(U info)
    {
        this->info = info;
    }

    template<class T>
    template<class U>
    U List<T>::Element<U>::getInfo()
    {
        return info;
    }

} // namespace JuNOCpp