//
// Created by wyx on 2024/3/12.
// 单向链表
//
#pragma once

#include <iostream>
#include <memory>
#include <List.hpp>

namespace mystd
{
    template<typename T>
    struct Node
    {
        T value;
        std::shared_ptr<Node> next;
        Node(const T& val, std::shared_ptr<Node> n) : value(val), next(n) {}
//        ~Node() { std::cout << "delete Node: " << value << std::endl; }
    };

    template<typename T>
    class LinkedList : public List<T>
    {
    public:
        LinkedList() = default;
        ~LinkedList() { clear(); }

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

        using List<T>::m_size;
        using List<T>::check_index;
        using List<T>::check_add_index;
        using List<T>::ELEMENT_NOT_FOUND;
    };

    template<typename T>
    inline void LinkedList<T>::clear()
    {
        head = nullptr;
        m_size = 0;
    }

    template<typename T>
    inline void LinkedList<T>::add(int index, const T &element)
    {
        check_add_index(index);

        if (index == 0) {
            head = std::make_shared<Node<T>>(element, head);
        } else {
            auto prev = get_node(index - 1);
            prev->next = std::make_shared<Node<T>>(element, prev->next);
        }
        m_size++;
    }

    template<typename T>
    inline void LinkedList<T>::remove(int index)
    {
        check_index(index);

        if (index == 0) {
            head = head->next;
        } else {
            auto prev = get_node(index - 1);
            prev->next = prev->next->next;
        }
        m_size--;
    }

    template<typename T>
    inline T LinkedList<T>::get(int index) const
    {
        return get_node(index)->value;
    }

    template<typename T>
    inline void LinkedList<T>::set(int index, const T &element)
    {
        get_node(index)->value = element;
    }

    template<typename T>
    inline int LinkedList<T>::index_of(const T &element) const
    {
        auto node = head;
        for (int i = 0; i < m_size; i++) {
            if (node->value == element) return i;
            node = node->next;
        }

        return ELEMENT_NOT_FOUND;
    }

    template<typename T>
    std::shared_ptr<Node<T>> LinkedList<T>::get_node(int index) const
    {
        check_index(index);

        auto node = head;
        for (int i = 0; i < index; i++) {
            node = node->next;
        }

        return node;
    }

    template<typename T>
    void LinkedList<T>::reverse()
    {
        head = reverse_list(head);
    }

//    /**
//     * 链表反转，递归方式
//     * @tparam T
//     * @param node
//     * @return
//     */
//    template<typename T>
//    std::shared_ptr<Node<T>> LinkedList<T>::reverse_list(std::shared_ptr<Node<T>> node)
//    {
//        if (node == nullptr || node->next == nullptr) return node;
//        auto new_head = reverse_list(node->next);
//        node->next->next = node;
//        node->next = nullptr;
//        return new_head;
//    }

    /**
     * 链表反转，遍历方式
     * @tparam T
     * @param node
     * @return
     */
    template<typename T>
    std::shared_ptr<Node<T>> LinkedList<T>::reverse_list(std::shared_ptr<Node<T>> node)
    {
        std::shared_ptr<Node<T>> new_head = nullptr;
        while (node != nullptr) {
            auto tmp = node->next;
            node->next = new_head;
            new_head = node;
            node = tmp;
        }
        return new_head;
    }

    template<typename T>
    void LinkedList<T>::to_string() const
    {
        std::cout << "size:" << m_size << " ";
        std::cout << "[";
        for (auto node = head; node != nullptr; node = node->next) {
            std::cout << node->value;
            if (node->next != nullptr) std::cout << ", ";
        }
        std::cout << "]" << std::endl;
    }
} // mystd
