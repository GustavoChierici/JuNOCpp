#pragma once
#include <array>
#include <iostream>
#include <math.h>
#include <climits>
#include "CustomString.hpp"

namespace JuNOCpp
{
    template <class T>
    class Table {
    private:
        int capacity;
        int count;
        T* array[1024];

    public:
        Table(const int capacity = 1024)
        {
            this->capacity = capacity;
            this->count = 0;
            for(int i = 0; i < capacity; i++)
                array[i] = nullptr;
        }

        void insertValue(const int key, T* value)
        {
            int index = hashing(key);

            array[index] = value;
        }

        void insertValue(CustomString key, T* value)
        {
            int index = hashing(key.getString());

            array[index] = value;
        }

        void insertValue(double key, T* value)
        {
            char aux_str[1000];
            sprintf(aux_str, "%f", key);

            unsigned int index(hashing(aux_str));

            array[index] = value;
        }

        T* operator[](const int key)
        {
            unsigned int index = hashing(key);
            //std::cout << index << std::endl;
            return array[index];
        }

        T* operator[](CustomString key)
        {
            unsigned int index = hashing(key.getString());
            //std::cout << index << std::endl;
            return array[index];
        }

        T* operator[](double key)
        {
            char aux_str[1000];
            sprintf(aux_str, "%f", key);

            unsigned int index(hashing(aux_str));

            return array[index];
        }

        unsigned int hashing(const int key)
        {
            int num_bits = 10;
            int parte1 = key >> num_bits;
            int parte2 = key & (this->capacity - 1);
            int index = (parte1 ^ parte2);
            int u_index = (index < 0 ? UINT_MAX - index : index);
            if(u_index > this->capacity - 1)
                return hashing(u_index);
            else
                return u_index;
        }

        unsigned int hashing(const char* s)
        {
            const int p = 131;
            const int m = 1e4 + 9;
            unsigned int hash = 0;
            unsigned int pow = 1;
            const int lenght = strlen(s);
            for(int i = 0; i < lenght; i++)
            {
                hash = (hash + (s[i] - 'a' + 1) * pow) % m;
                pow = (pow * p) % m;
            }
            if(hash > this->capacity)
                return hashing(hash);
            return hash;
        }
    };
}
