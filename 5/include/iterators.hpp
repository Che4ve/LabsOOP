#pragma once

#include <iostream>
#include <stdexcept>

template <typename T>
class Iterator 
{
    using iterator_category = std::forward_iterator_tag;
    using difference_type   = std::ptrdiff_t;
    using value_type        = T;
    using pointer           = value_type*;
    using reference         = value_type&;

    public:
        Iterator(pointer ptr) : m_ptr(ptr) {}

        reference operator*() const { return *m_ptr; }
        pointer operator->() { return m_ptr; }

        // Prefix increment
        Iterator& operator++() { m_ptr = m_ptr->next; return *this; }

        // Postfix increment
        Iterator operator++(int){ Iterator tmp = *this; ++(*this); return tmp; }

        friend bool operator==(const Iterator& a, const Iterator& b) {
            return a.m_ptr == b.m_ptr;
        }
        friend bool operator!=(const Iterator& a, const Iterator& b) { 
            return !(a == b); 
        }

    private:
        pointer m_ptr;
};

template <typename T>
class ConstIterator 
{
    using iterator_category = std::forward_iterator_tag;
    using difference_type   = std::ptrdiff_t;
    using value_type        = const T;
    using pointer           = const value_type*;
    using reference         = const value_type&;

    public:
        ConstIterator(pointer ptr) : m_ptr(ptr) {}

        reference operator*() const { return *m_ptr; }
        pointer operator->() const { return m_ptr; }

        // Prefix increment
        ConstIterator& operator++() { m_ptr = m_ptr->next; return *this; }

        // Postfix increment
        ConstIterator operator++(int){ ConstIterator tmp = *this; ++(*this); return tmp; }

        friend bool operator==(const ConstIterator& a, const ConstIterator& b) {
            return a.m_ptr == b.m_ptr;
        }
        friend bool operator!=(const ConstIterator& a, const ConstIterator& b) { 
            return !(a == b); 
        }

    private:
        pointer m_ptr;
};