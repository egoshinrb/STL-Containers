#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <iostream>
#include <limits>

namespace s21 {

template <typename T>
class Vector {
    public:
        using value_type = T;
        using reference = T&;
        using const_reference = const T&;
        using iterator = T*;
        using const_iterator = const T*;
        using size_type = size_t;


// Vector constructors
        Vector();
        explicit Vector(size_type size);
        explicit Vector(std::initializer_list<value_type> const &other);
        Vector(const Vector &other);
        Vector(Vector &&other);

// Vector operators
        Vector& operator=(const Vector &other) noexcept;
        Vector& operator=(Vector &&other) noexcept;
        value_type& operator[](const size_type pos);
        const value_type& operator[](const size_type pos) const;

// Vector dectructor
        ~Vector();

// Vector Element access
        reference at(size_type pos);
        const_reference at(size_type pos) const;
        const_reference front() const;
        const_reference back() const;
        T* data() const noexcept;

// Vector Iterators
        iterator begin() const;
        iterator end() const;

// Vector Capacity
        bool empty() const noexcept;
        size_type size() const noexcept;
        size_type max_size() const noexcept;
        void reserve(size_type size);
        size_type capacity() const noexcept;
        void shrink_to_fit();

// Vector Modifiers
        void clear();
        iterator insert(iterator pos, const_reference value);
        void erase(iterator pos);
        void push_back(const_reference value) noexcept;
        void pop_back() noexcept;
        void swap(Vector& other) noexcept;


    private:
        size_t size_;
        size_t capacity_;
        value_type *arr_;
};
}  // close namespace s21

#include "vector.inl"

#endif