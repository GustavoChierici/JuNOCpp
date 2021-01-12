#ifndef FORWARD_LIST_HPP
#define FORWARD_LIST_HPP

#include "../.config.hpp"

namespace JuNOCpp
{
    namespace Utils
    {
        template <typename T>
        struct node
        {
            T element;
            node<T>* next;

            node(T elem, node<T>* next_ptr = nullptr):
            element(elem), next(next_ptr) { }

            ~node() { next =  nullptr; }

            node<T>* getNext() { return next; }
        };

        template <typename T>
        struct fwl_iterator
        {
            node<T>* current_node;

            fwl_iterator(node<T>* node_ptr = nullptr):
            current_node(node_ptr)
            { }

            fwl_iterator(const fwl_iterator& rhs):
            current_node(rhs.current_node)
            { }

            fwl_iterator(fwl_iterator&& rhs):
            current_node(rhs.current_node)
            { }

            ~fwl_iterator() { current_node = nullptr; }

            fwl_iterator& operator=(node<T>* node_ptr)
            {
                current_node = node_ptr;
                return *this;
            }

            fwl_iterator& operator++()
            {
                if(current_node)
                    current_node = current_node->next;

                return *this;
            }

            fwl_iterator& operator++(int)
            {
                fwl_iterator iterator = *this;
                ++*this;
                return iterator;
            }

            bool operator!=(const fwl_iterator& rhs)
            {
                return current_node != rhs.current_node;
            }

            T operator*()
            {
                return current_node->element;
            }

            T* operator->()
            {
                return &current_node->element;
            }
        };

        template <class T>
        class forward_list
        {
        #ifdef FASTER_DATA_STRUCTURES
        public:
        #else
        private:
        #endif // DEBUG
            node<T>* first;
            node<T>* last;
            const bool delete_elements_on_destroy;
        public:
            forward_list(node<T>* first_ptr = nullptr, node<T>* last_ptr = nullptr, const bool del = true) :
            first(first_ptr), last(last_ptr), delete_elements_on_destroy(del) 
            { }

            forward_list(T elem, const bool del = true):
            first(new node<T>(elem)), last(nullptr), delete_elements_on_destroy(del)
            { }

            forward_list(const forward_list& rhs):
            first(rhs.first), last(rhs.last), delete_elements_on_destroy(rhs.delete_elements_on_destroy)
            { }

            forward_list(forward_list&& rhs):
            first(rhs.first), last(rhs.last), delete_elements_on_destroy(rhs.delete_elements_on_destroy)
            { }

            ~forward_list()
            {
                if(delete_elements_on_destroy)
                    clear();
                else
                {
                    first = nullptr;
                    last = nullptr;
                }   
            }

            void clear()
            {
                node<T>* aux_node = first;
                node<T>* aux_node2;

                if(aux_node)
                    while(aux_node->next)
                    {
                        aux_node2 = aux_node->next;
                        delete aux_node;
                        aux_node = aux_node2;
                    }

                first = nullptr;
                last = nullptr;
            }

            bool empty() const { return first == last; }

            #ifndef FASTER_DATA_STRUCTURES
                node<T>* getFirst() { return first; }
                node<T>* getLast() { return last; }
            #endif // !FASTER_DATA_STRUCTURES

            fwl_iterator<T> begin() { return fwl_iterator<T>(first); }

            fwl_iterator<T> end() { return fwl_iterator<T>(nullptr); }

            void push_back(T elem) 
            { 
                node<T>* aux_node = new node<T>(elem);
                if(aux_node)
                {
                    if(!first)
                        first = aux_node;
                    else if(!first->next)
                    {
                        last = aux_node;
                        first->next = last;
                    }
                    else
                    {
                        last->next = aux_node;
                        last = last->next;
                    }
                }
            }

            void remove(T elem)
            {
                if(first and first->element == elem)
                {
                    node<T>* aux_node = first;
                    first = first->next;
                    delete aux_node;

                    return;
                }

                node<T>* aux_node = first->next;

                while(aux_node)
                {
                    node<T>* aux_node2 = aux_node;
                    aux_node = aux_node->next;
                    if(aux_node and aux_node->element == elem)
                    {
                        aux_node2->next = aux_node->next;
                        delete aux_node;

                        break;
                    }
                }
            }
        };
    } // namespace Utils
} // namespace JuNOCpp

#endif // !FORWARD_LIST_HPP