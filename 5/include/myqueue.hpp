#pragma once

#include <iostream>
#include <vector>
#include "./allocator.hpp"
#include "./iterators.hpp"

// #define DEBUG

template <typename T>
struct Node {
    T data;
    Node* next;
    Node(const T& value) : data(value), next(nullptr) {}
};

constexpr size_t DefaultSize = 100;

template < typename T, typename Allocator = CustomAllocator<Node<T>, DefaultSize> >
class MyQueue {
    public:
        using iterator_category = std::forward_iterator_tag;
        using qNode             = Node<T>;
        using value_type        = T;
        using pointer           = value_type*;
        using reference         = value_type&;
        using iterator          = Iterator<qNode>;
        using const_iterator    = ConstIterator<qNode>;
        // Конструктор
        MyQueue() : frontNode(nullptr), rearNode(nullptr) {}

        // Деструктор
        ~MyQueue() {
            while (!empty()) {
                pop();
            }
        }

        // Проверка на пустоту
        bool empty() const {
            return frontNode == nullptr;
        }

        // Добавление элемента в конец очереди
        void push(const T& value) {
            qNode* newNode = allocator.allocate(1);
            newNode->data = value;
            newNode->next = nullptr;

            if (empty()) {
                frontNode = rearNode = newNode;
            } else {
                rearNode->next = newNode;
                rearNode = newNode;
            }
        }

        // Удаление элемента из начала очереди
        void pop() {
            if (empty()) {
                throw std::out_of_range("Queue is empty");
            }

            qNode* temp = frontNode;
            frontNode = frontNode->next;
            allocator.deallocate(temp, 1);

            if (frontNode == nullptr) {
                rearNode = nullptr;
            }
        }

        // Получение элемента из начала очереди
        T& front() const {
            if (empty()) {
                throw std::out_of_range("Queue is empty");
            }
            return frontNode->data;
        }

        iterator begin() { iterator headIter(frontNode); return headIter; }
        iterator end() { iterator rearIter(nullptr); return rearIter; }

        const_iterator begin() const { const_iterator headIter(frontNode); return headIter; }
        const_iterator end() const { const_iterator rearIter(nullptr); return rearIter; }

    private:
        qNode* frontNode;
        qNode* rearNode;
        Allocator allocator;
};