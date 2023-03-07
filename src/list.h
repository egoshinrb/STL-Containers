#ifndef __LIST_H__
#define __LIST_H__

#include <iostream>
#include <limits>

namespace s21 {

template <typename T>
class List {
    public:
        using value_type = T;
        using reference = T&;
        using const_reference = const T&;
        using size_type = size_t;        

        class Node {
            public:
            value_type data_;
            Node* next_;
            Node* prev_;
            Node(value_type data = value_type(), Node* next = nullptr,
                Node* prev = nullptr) : data_(data), next_(next), prev_(prev) {}
        };

        class ListIterator {
            public:
                Node* curr_;
                Node* listHead_;
                Node* listTail_;

                ListIterator();
                explicit ListIterator(const List &l);
                // ListIterator(const ListIterator &l);
                ~ListIterator() = default;
                ListIterator& operator++();
                ListIterator& operator--();
                ListIterator operator+(size_type count);
                reference operator*() const;
                bool operator==(const ListIterator& other) const noexcept;
                bool operator!=(const ListIterator& other) const noexcept;
                bool operator<(const ListIterator& other) const noexcept;
                bool operator<=(const ListIterator& other) const noexcept;
        };

        class ConstListIterator : public ListIterator {
            public:
                ConstListIterator() : ListIterator() {};
                explicit ConstListIterator(const List &l) : ListIterator(l) {};
                // ConstListIterator(const ListIterator &l);
                const_reference operator*() const noexcept;
                ConstListIterator& operator=(const ListIterator& other);
        };

        using iterator = ListIterator;
        using const_iterator = ConstListIterator;

    private:
        size_type size_;
        Node* head_;
        Node* tail_;

    public:
        // List constructors
        List();
        List(size_type n);
        List(std::initializer_list<value_type> const &items);
        List(const List &l);
        List(List &&l);


        // List dectructor
        ~List();


        // List operators
        List& operator=(const List &l);
        List& operator=(List &&l);


        // List element access
        const_reference front();
        const_reference back();


        // List iterators
        iterator begin();
        iterator end();


        // List capacity
        bool empty();
        size_type size();
        size_type max_size();


        // List modifiers
        void clear();
        iterator insert(iterator pos, const_reference value);
        void erase(iterator pos);
        void push_back(const_reference value);
        void pop_back();
        void push_front(const_reference value);
        void pop_front();
        void swap(List& other);
        void merge(List& other);
        void splice(const_iterator pos, List& other);
        void reverse();
        void unique();
        void sort();


        // utility methods
    private:
        void check_iterator(iterator pos) const;
        void check_iterator(const_iterator pos) const;
        void quick_sort(const iterator& l_board, const iterator& r_board);
};




} // close namespace s21

#include "list.inl"

#endif