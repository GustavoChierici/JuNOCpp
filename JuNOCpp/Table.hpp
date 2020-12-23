#pragma once
#include <array>
#include <iostream>
#include <math.h>
#include <climits>
#include "CustomString.hpp"

namespace JuNOCpp
{
    //don't use this, use one of the typedefs in the end of the file
    template <class ValueType, class KeyType>
    class Table
    {
    private:
        int capacity;
        int count;

        typedef struct _elem
        {
            ValueType *value;
            KeyType key;
            struct _elem* next;
        } Elem;
        Elem **array;

    public:
        Table(const int capacity = 1024) : capacity{capacity},
                                           count{0},
                                           array{new Elem *[capacity]}
        {
            for (int i = 0; i < capacity; ++i)
                array[i] = nullptr;
        }

        ~Table()
        {
            for (int i = 0; i < capacity; ++i)
            {
                Elem *el = array[i];
                while (el)
                {
                    Elem *aux = el->next;
                    delete el;
                    el = aux;
                }
            }

            delete[] array;
        }

        void insertValue(const int key, ValueType *value)
        {
            insert(hashing(key), key, value);
        }

        void insertValue(CustomString key, ValueType *value)
        {

            insert(hashing(key.getString()), key, value);
        }

        void insertValue(double key, ValueType *value)
        {
            char aux_str[20];
            sprintf(aux_str, "%f", key);

            insert(hashing(aux_str), key, value);
        }

        ValueType *operator[](KeyType key)
        {
            unsigned int index = hashing(key);
            Elem *el = array[index];
            while (el)
            {
                if (el->key == key)
                    return el->value;
                else
                    el = el->next;
            }
            return nullptr;
        }

        unsigned int hashing(const int key)
        {
            int num_bits = 10;
            int parte1 = key >> num_bits;
            int parte2 = key & (this->capacity - 1);
            int index = (parte1 ^ parte2);
            int u_index = (index < 0 ? UINT_MAX - index : index);
            if (u_index > this->capacity - 1)
                return hashing(u_index);
            else
                return u_index;
        }

        unsigned int hashing(const char *s)
        {
            const int p = 131;
            const int m = 1e4 + 9;
            unsigned int hash = 0;
            unsigned int pow = 1;
            const int lenght = strlen(s);
            for (int i = 0; i < lenght; i++)
            {
                hash = (hash + (s[i] - 'a' + 1) * pow) % m;
                pow = (pow * p) % m;
            }
            if (hash > this->capacity)
                return hashing(hash);
            return hash;
        }

        unsigned int hashing(double key)
        {
            char aux_str[20];
            sprintf(aux_str, "%f", key);

            return hashing(aux_str);
        }

    private:
        void insert(int index, KeyType key, ValueType *value)
        {
            Elem *newElement = new Elem();
            newElement->value = value;
            newElement->key = key;
            newElement->next = array[index];
            array[index] = newElement;
        }
    };

    template <class ValueType>
    using IntTable = Table<ValueType, int>;
    template <class ValueType>
    using StringTable = Table<ValueType, CustomString>;
    template <class ValueType>
    using DoubleTable = Table<ValueType, double>;

} // namespace JuNOCpp
