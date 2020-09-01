#pragma once
#include <array>
#include <iostream>

namespace JuNOCpp
{
    template <class T>
    class Table {
    private:
        int capacity;
        int count;
        T* array[100000];

    public:
        Table(const int capacity = 50)
        {
            this->capacity = capacity;
            this->count = 0;
            for(int i = 0; i < 50; i++)
                array[i] = nullptr;
        }

        void insertValue(const int key, T* value)
        {
            int index = hashing(key);

            array[index] = value;
        }

        T* operator[](const int key)
        {
            int index = hashing(key);
           // std::cout << index << std::endl;
            return array[index];
        }

        int hashing(const int key)
        {
            int num_bits = 10;
            int parte1 = key >> num_bits;
            int parte2 = key & (capacity-1);
            return parte1 ^ parte2;
        }
    };

}
