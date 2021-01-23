/**
 * @file vector.hpp
 * @author Gustavo Brunholi Chierici (gustavobchierici@gmail.com)
 * @brief Vector feito especificamente para o JuNOC++
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <exception>

namespace JuNOCpp
{
    namespace Utils
    {
        
        template<typename VectorType>
        struct vector_iterator
        {
        private:
            VectorType* vector_element_ptr;

        public:
            explicit vector_iterator(VectorType* ele_ptr = nullptr):
            vector_element_ptr{ele_ptr}
            { }

            virtual ~vector_iterator() { vector_element_ptr = nullptr; }

            bool operator==(const vector_iterator& rhs) const
            {
                return vector_element_ptr == rhs.vector_element_ptr;
            }

            bool operator!=(const vector_iterator& rhs) const
            {
                return vector_element_ptr != rhs.vector_element_ptr;
            }

            VectorType operator*() { return *vector_element_ptr; }
            
            VectorType* operator->() { return vector_element_ptr; }

            vector_iterator& operator++()
            {
                ++vector_element_ptr;
                return *this;
            }

            vector_iterator operator++(int)
            {
                vector_iterator temp(*this);
                ++*this;
                return temp;
            }

        };

        template <typename VectorType>
        class vector
        {
        private:
            VectorType* array;

            unsigned long long capacity;
            unsigned long long length;

        public:
			class bad_vector_element: public std::exception
			{
			private:
				const char* m_msg;

			public:
				bad_vector_element(const char* msg = "bad_vector_element"):
					m_msg{msg} { }

				const char* what() const noexcept override
				{
					return this->m_msg;
				}
			};

        public:
            vector(unsigned long long cap = 1):
            array{new VectorType[cap]}, capacity{cap}, length{0}
            { }

            vector(const vector& rhs):
            array(rhs.array), capacity(rhs.capacity), length(rhs.length)
            { }

            vector(vector&& rhs):
            array(rhs.array), capacity(rhs.capacity), length(rhs.length)
            { }

            virtual ~vector()
            { 
                clear();
                ::operator delete[](array, capacity * sizeof(VectorType));
            }

            void clear()
            {
                for(unsigned long long i = 0; i < length; i++)
                    array[i].~VectorType();

                length = 0;
            }

            void allocate()
            {
                VectorType* temp = (VectorType*)::operator new((2 * capacity) * sizeof(VectorType));

                for(unsigned long long i = 0; i < capacity; i++)
                    temp[i] = array[i];

                for(unsigned long long i = 0; i < length; i++)
                    array[i].~VectorType();

                ::operator delete(array, capacity * sizeof(VectorType));
                capacity *= 2;
                array = temp;
            }

            void push_back(VectorType data)
            {
                if(length == capacity)
                    allocate();

                array[length] = data;
                length++;
            }

            void insert(VectorType data, unsigned long long index)
            {
                // if index is equal to capacity, push_back, if is greater,
                // double capacity and then push_back
                if(index >= capacity)
                    push_back(data);
                else
                    array[index] = data;
            }

            bool remove(VectorType data)
            {
                for(unsigned long long i = 0; i < length; i++)
                {
                    if(array[i] == data)
                    {
                        VectorType* new_array = new VectorType[length - 1];
                        for(unsigned long long j = 0; j < i; j++)
                            new_array[j] = array[j];

                        for(; i < length - 1; i++)
                            new_array[i] = array[i + 1];

                        delete[] array;
                        array = new_array;
                        delete[] new_array;
                        --length;

                        return true;
                    }
                }
                return false;
            }

            VectorType at(unsigned long long index)
            {
                if(index < length)
                    return *(array + index);
                else
                    throw bad_vector_element("vector: vector out of bound"); 
            }

            VectorType operator[](unsigned long long index)
            {
                return at(index);
            }

            VectorType pop_back() { return array[length--]; }

            unsigned long long size() const { return length; }
            unsigned long long getCapacity() const {return capacity; }

            vector_iterator<VectorType> begin() { return vector_iterator(array); }
            vector_iterator<VectorType> end() { return vector_iterator(array + length); }

        };

    } // namespace Utils
    
} // namespace JuNOCpp

#endif // !VECTOR_HPP