//
// Created by 17602 on 2024/3/11.
//
#pragma once

#include <stdexcept>

namespace mystd
{
    template<typename T>
    class List
    {
    public:
        virtual ~List() = default;
        virtual void add(int index, const T& element) = 0;
        virtual void remove(int index) = 0;
        virtual void clear() = 0;
        virtual T get(int index) const = 0;
        virtual void set(int index, const T& element) = 0;
        virtual int index_of(const T& element) const = 0;

        [[nodiscard]] virtual int size() const noexcept { return m_size; }
        virtual void push_back(const T& element) { add(m_size, element); }
        virtual void pop_back() { remove(m_size - 1); }
        [[nodiscard]] virtual bool isEmpty() const noexcept { return m_size == 0; }
        virtual bool contains(const T& element) const { return index_of(element) != ELEMENT_NOT_FOUND; }

    protected:
        virtual void check_index(int index) const final
        {
            if (index < 0 || index >= m_size) {
                throw std::out_of_range("index out of size!");
            }
        }

        virtual void check_add_index(int index) const final
        {
            if (index < 0 || index > m_size) {
                throw std::out_of_range("index out of size!");
            }
        }

    protected:
        static constexpr int ELEMENT_NOT_FOUND = -1;
        int m_size = 0;
    };
} // mystd