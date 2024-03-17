//
// Created by wyx on 2024/3/17.
// 双向循环链表
//
#pragma once

#include "Node.h"
#include <List.hpp>

namespace mystd
{
    template<typename T>
    class CircleLinkedList : public List<T>
    {
    public:
        ~CircleLinkedList() { free_tail(); }
        void add(int index, const T& element) override;
        void remove(int index) override;
        void clear() override;
        T get(int index) const override;
        void set(int index, const T& element) override;
        int index_of(const T& element) const override;
        void to_string() const;

    private:
        std::shared_ptr<Node<T>> get_node(int index) const;
        void free_tail();

    private:
        std::shared_ptr<Node<T>> head = nullptr;
        std::shared_ptr<Node<T>> tail = nullptr;
    };

    template<typename T>
    inline void CircleLinkedList<T>::free_tail()
    {
        if (tail != nullptr) {
            tail->next = nullptr;
        }
    }

    template<typename T>
    inline void CircleLinkedList<T>::clear()
    {
        free_tail();
        head = nullptr;
        tail = nullptr;
        this->m_size = 0;
    }

    template<typename T>
    inline void CircleLinkedList<T>::add(int index, const T& element)
    {
        this->check_add_index(index);

        if (index == this->m_size) {  // 往最后面添加元素
            auto old_tail = tail;
            tail = std::make_shared<Node<T>>(element, head, old_tail);
            if (old_tail == nullptr) {  // 添加的第一个元素
                head = tail;
                head->next = head;
                head->prev = head;
            } else {
                old_tail->next = tail;
                head->prev = tail;
            }
        } else {
            auto next = get_node(index);
            auto prev = next->prev.lock();
            auto node = std::make_shared<Node<T>>(element, next, prev);
            next->prev = node;
            prev->next = node;

            if (next == head) { // index == 0
                head = node;
            }
        }

        this->m_size++;
    }

    template<typename T>
    inline void CircleLinkedList<T>::remove(int index)
    {
        this->check_index(index);

        if (this->m_size == 1) {
            /* 解除循环引用 */
            head->next = nullptr;

            head = nullptr;
            tail = nullptr;
        } else {
            auto node = get_node(index);
            auto prev = node->prev.lock();
            auto next = node->next;
            prev->next = next;
            next->prev = prev;

            if (node == head) {    // index == 0
                head = next;
            }

            if (node == tail) {    // index == m_size - 1
                tail = prev;
            }
        }

        this->m_size--;
    }

    template<typename T>
    inline T CircleLinkedList<T>::get(int index) const
    {
        return get_node(index)->value;
    }

    template<typename T>
    inline void CircleLinkedList<T>::set(int index, const T& element)
    {
        get_node(index)->value = element;
    }

    template<typename T>
    inline int CircleLinkedList<T>::index_of(const T& element) const
    {
        auto node = head;
        for (int i = 0; i < this->m_size; i++) {
            if (node->value == element) return i;
            node = node->next;
        }

        return this->ELEMENT_NOT_FOUND;
    }

    template<typename T>
    std::shared_ptr<Node<T>> CircleLinkedList<T>::get_node(int index) const
    {
        this->check_index(index);

        // 查找元素比单向链表效率高，最坏的情况下就是遍历链表一半的长度
        decltype(head) node;
        if (index < (this->m_size >> 1)) {
            node = head;
            for (int i = 0; i < index; i++) {
                node = node->next;
            }
        } else {
            node = tail;
            for (int i = this->m_size - 1; i > index; i--) {
                node = node->prev.lock();
            }
        }
        return node;
    }

    template<typename T>
    void CircleLinkedList<T>::to_string() const
    {
        std::cout << "size:" << this->m_size << " ";
        std::cout << "[";
        if (head != nullptr) {
            auto node = head;
            do {
                std::cout << node->value;
                if (node->next != head) std::cout << ", ";
                node = node->next;
            } while (node != head);
        }
        std::cout << "]" << std::endl;
    }
} // mystd
