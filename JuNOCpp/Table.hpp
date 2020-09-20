#pragma once
#include <array>
#include <iostream>
#include <math.h>
#include "CustomString.hpp"

namespace JuNOCpp
{
    template <class T>
    class Table {
    private:
        int capacity;
        int count;
        T* array[1000];

    public:
        Table(const int capacity = 1000)
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

        T* operator[](const int key)
        {
            unsigned int index = hashing(key);
            //std::cout << index << std::endl;
            return array[index];
        }

        T* operator[](CustomString key)
        {
            int index = hashing(key.getString());
            //std::cout << index << std::endl;
            return array[index];
        }

        int hashing(const int key)
        {
            int num_bits = 1000;
            unsigned int parte1 = key >> num_bits;
            unsigned int parte2 = key & (this->capacity-1);
            if((parte1 ^ parte2) > this->capacity)
                return(hashing(parte1 ^ parte2));
            else
                return (parte1 ^ parte2);
        }

        int hashing(const char* s)
        {
            const int p = 131;
            const int m = 1e12 + 9;
            unsigned int hash = 0;
            unsigned int pow = 1;
            for(int i = 0; i < strlen(s); i++)
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
