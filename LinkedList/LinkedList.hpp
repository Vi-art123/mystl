//
// Created by wyx on 2024/3/17.
// 双向链表
//
#pragma once

#include "Node.h"
#include <List.hpp>

namespace mystd
{
    template<typename T>
    class LinkedList : public List<T>
    {
    public:
        void add(int index, const T& element) override;
        void remove(int index) override;
        void clear() override;
        T get(int index) const override;
        void set(int index, const T& element) override;
        int index_of(const T& element) const override;
        void to_string() const;
        void reverse();

    private:
        std::shared_ptr<Node<T>> get_node(int index) const;
        std::shared_ptr<Node<T>> reverse_list(std::shared_ptr<Node<T>> node);

    private:
        std::shared_ptr<Node<T>> head = nullptr;
        std::shared_ptr<Node<T>> tail = nullptr;
    };

    template<typename T>
    inline void LinkedList<T>::clear()
    {
        head = nullptr;
        tail = nullptr;
        this->m_size = 0;
    }

    template<typename T>
    inline void LinkedList<T>::add(int index, const T& element)
    {
        this->check_add_index(index);

        if (index == this->m_size) {  // 往最后面添加元素
            auto old_tail = tail;
            tail = std::make_shared<Node<T>>(element, nullptr, old_tail);
            if (old_tail == nullptr) {  // 添加的第一个元素
                head = tail;
            } else {
                old_tail->next = tail;
            }
        } else {
            auto next = get_node(index);
            auto prev = next->prev.lock();
            auto node = std::make_shared<Node<T>>(element, next, prev);
            next->prev = node;

            if (prev == nullptr) {  // index == 0
                head = node;
            } else {
                prev->next = node;
            }
        }

        this->m_size++;
    }

    template<typename T>
    inline void LinkedList<T>::remove(int index)
    {
        this->check_index(index);

        auto node = get_node(index);
        auto prev = node->prev.lock();
        auto next = node->next;

        if (prev == nullptr) {  // index == 0
            head = next;
        } else {
            prev->next = next;
        }

        if (next == nullptr) {  // index == m_size - 1
            tail = prev;
        } else {
            next->prev = prev;
        }

        this->m_size--;
    }

    template<typename T>
    inline T LinkedList<T>::get(int index) const
    {
        return get_node(index)->value;
    }

    template<typename T>
    inline void LinkedList<T>::set(int index, const T& element)
    {
        get_node(index)->value = element;
    }

    template<typename T>
    inline int LinkedList<T>::index_of(const T& element) const
    {
        auto node = head;
        for (int i = 0; i < this->m_size; i++) {
            if (node->value == element) return i;
            node = node->next;
        }

        return this->ELEMENT_NOT_FOUND;
    }

    template<typename T>
    std::shared_ptr<Node<T>> LinkedList<T>::get_node(int index) const
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
    void LinkedList<T>::reverse()
    {
        auto old_head = head;
        head = reverse_list(old_head);
        tail = old_head;
    }

#if 0
    /**
     * 链表反转，递归方式
     * @tparam T
     * @param node
     * @return
     */
    template<typename T>
    std::shared_ptr<Node<T>> LinkedList<T>::reverse_list(std::shared_ptr<Node<T>> node)
    {
        if (node == nullptr || node->next == nullptr) return node;
        auto new_head = reverse_list(node->next);
        node->next->next = node;
        node->prev = node->next;
        node->next = nullptr;
        return new_head;
    }
#endif

    /**
     * 链表反转，遍历方式
     * @tparam T
     * @param node
     * @return
     */
    template<typename T>
    std::shared_ptr<Node<T>> LinkedList<T>::reverse_list(std::shared_ptr<Node<T>> node)
    {
        if (node == nullptr || node->next == nullptr) return node;

        decltype(node) new_head = nullptr;
        while (node != nullptr) {
            auto tmp = node->next;
            node->next = new_head;
            node->prev = decltype(node)(nullptr);
            if (new_head != nullptr) {
               new_head->prev = node;
            }
            new_head = node;
            node = tmp;
        }
        return new_head;
    }

    template<typename T>
    void LinkedList<T>::to_string() const
    {
        std::cout << "size:" << this->m_size << " ";
        std::cout << "[";
        for (auto node = head; node != nullptr; node = node->next) {
            std::cout << node->value;
            if (node->next != nullptr) std::cout << ", ";
        }
        std::cout << "]" << std::endl;
    }
} // mystd
