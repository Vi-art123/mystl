//
// Created by wyx on 2024/3/10.
// 动态数组
//
#pragma once
#include <List.hpp>

namespace mystd
{
    template<typename T>
    class ArrayList : public List<T>
    {
    public:
        ArrayList() : ArrayList(DEFAULT_CAPACITY) {}
        explicit ArrayList(const int& capacity)
        {
            m_capacity = (capacity < DEFAULT_CAPACITY) ? DEFAULT_CAPACITY : capacity;
            m_arr = new T[m_capacity];
        }

        ~ArrayList()
        {
            m_size = 0;
            delete[] m_arr;
            m_arr = nullptr;
            m_capacity = 0;
        }

        void add(int index, const T& element) override;
        void remove(int index) override;
        void clear() noexcept override { m_size = 0; }
        T get(int index) const override;
        void set(int index, const T& element) override;
        int capacity() noexcept { return m_capacity; }
        int index_of(const T& element) const override;
        void to_string() const;

    private:
        [[nodiscard]] int free_space() const noexcept { return m_capacity - m_size; }
        void ensure_capacity();

    private:
        static constexpr int DEFAULT_CAPACITY = 10;
        int m_capacity = DEFAULT_CAPACITY;
        T *m_arr = nullptr;

        using List<T>::m_size;
        using List<T>::check_index;
        using List<T>::check_add_index;
        using List<T>::ELEMENT_NOT_FOUND;
    };


    /**
     * 动态扩容
     * @tparam T
     */
    template<typename T>
    inline void ArrayList<T>::ensure_capacity()
    {
        if (free_space() > 0) return;
        m_capacity += (m_capacity >> 1);
        T* new_arr = new T[m_capacity];
        for (int i = 0; i < m_size; i++) {
            new_arr[i] = m_arr[i];
        }
        delete[] m_arr;
        m_arr = new_arr;
    }

    template<typename T>
    void ArrayList<T>::add(int index, const T &element)
    {
        check_add_index(index);

        ensure_capacity();

        for (int i = m_size - 1 ; i >= index; i--) {
            m_arr[i + 1] = m_arr[i];
        }
        m_arr[index] = element;
        m_size++;
    }

    template<typename T>
    void ArrayList<T>::remove(int index)
    {
        check_index(index);

        for (int i = index + 1; i < m_size - 1; i++) {
            m_arr[i - 1] = m_arr[i];
        }
        m_size--;
    }

    template<typename T>
    inline int ArrayList<T>::index_of(const T& element) const
    {
        for (int i = 0; i < m_size; i++) {
            if (m_arr[i] == element) return i;
        }

        return ELEMENT_NOT_FOUND;
    }


    template<typename T>
    inline T ArrayList<T>::get(int index) const
    {
        check_index(index);
        return m_arr[index];
    }

    template<typename T>
    inline void ArrayList<T>::set(int index, const T& element)
    {
        check_index(index);
        m_arr[index] = element;
    }

    template<typename T>
    void ArrayList<T>::to_string() const
    {
        std::cout << "size:" << m_size << " ";
        std::cout << "{";
        for (int i = 0; i < m_size; i++) {
            std::cout << m_arr[i];
            if (i != m_size - 1) std::cout << ", ";
        }
        std::cout << "}" << std::endl;
    }
} // mystd