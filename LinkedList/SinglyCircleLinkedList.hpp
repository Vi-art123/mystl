//
// Created by wyx on 2024/3/17.
// 单向循环链表
//
#pragma once

#include "Node.h"
#include <List.hpp>

namespace mystd
{
    template<typename T>
    class SinglyCircleLinkedList : public List<T>
    {
    public:
        ~SinglyCircleLinkedList() { free_tail(); }
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
    };

    template<typename T>
    inline void SinglyCircleLinkedList<T>::free_tail()
    {
        decltype(head) tail;
        if (this->m_size <= 1) {
            tail = head;
        } else {
            tail = get_node(this->m_size - 1);
        }

        if (tail != nullptr) {
            tail->next = nullptr;   // 解除循环引用
        }
    }

    template<typename T>
    inline void SinglyCircleLinkedList<T>::clear()
    {
        free_tail();
        head = nullptr;
        this->m_size = 0;
    }

    template<typename T>
    inline void SinglyCircleLinkedList<T>::add(int index, const T& element)
    {
        this->check_add_index(index);

        if (index == 0) {
            head = std::make_shared<Node<T>>(element, head);

            // 拿到最后一个节点
            auto tail = (this->m_size == 0) ? head : get_node(this->m_size - 1);
            tail->next = head;
        } else {
            auto prev = get_node(index - 1);
            prev->next = std::make_shared<Node<T>>(element, prev->next);
        }
        this->m_size++;
    }

    template<typename T>
    inline void SinglyCircleLinkedList<T>::remove(int index)
    {
        this->check_index(index);

        if (index == 0) {
            if (this->m_size == 1) {    // 循环链表只有一个节点的情况
                head->next = nullptr;   // 解除循环引用
                head = nullptr;
            } else {
                // 拿到最后一个节点
                auto tail = (this->m_size == 0) ? head : get_node(this->m_size - 1);
                head = head->next;
                tail->next = head;
            }
        } else {
            auto prev = get_node(index - 1);
            prev->next = prev->next->next;
        }
        this->m_size--;
    }

    template<typename T>
    inline T SinglyCircleLinkedList<T>::get(int index) const
    {
        return get_node(index)->value;
    }

    template<typename T>
    inline void SinglyCircleLinkedList<T>::set(int index, const T& element)
    {
        get_node(index)->value = element;
    }

    template<typename T>
    inline int SinglyCircleLinkedList<T>::index_of(const T& element) const
    {
        auto node = head;
        for (int i = 0; i < this->m_size; i++) {
            if (node->value == element) return i;
            node = node->next;
        }

        return this->ELEMENT_NOT_FOUND;
    }

    template<typename T>
    std::shared_ptr<Node<T>> SinglyCircleLinkedList<T>::get_node(int index) const
    {
        this->check_index(index);

        auto node = head;
        for (int i = 0; i < index; i++) {
            node = node->next;
        }

        return node;
    }

    template<typename T>
    void SinglyCircleLinkedList<T>::to_string() const
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
}