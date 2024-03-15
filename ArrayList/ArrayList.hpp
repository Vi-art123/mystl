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
            delete[] m_arr;
        }

        ArrayList(const ArrayList& ary) : List<T>(ary), m_capacity(ary.m_capacity)
        {
            // if (m_arr != nullptr) delete m_arr;  // 如果不加这一句会不会内存泄漏？
            m_arr = new T[m_capacity];
            for (int i = 0; i < m_size; i++) {
                m_arr[i] = ary.m_arr[i];
            }
        }

        ArrayList(ArrayList&& ary) : List<T>(ary), m_capacity(ary.m_capacity), m_arr(ary.m_arr)
        {
            ary.m_arr = nullptr;
            ary.m_size = 0;
            ary.m_capacity = DEFAULT_CAPACITY;
        }

        ArrayList& operator=(const ArrayList& ary)
        {
            List<T>::operator=(ary);
            m_capacity = ary.m_capacity;
            if (m_arr != nullptr) delete m_arr;  // 如果不加这一句会不会内存泄漏？
            m_arr = new T[m_capacity];
            for (int i = 0; i < m_size; i++) {
                m_arr[i] = ary.m_arr[i];
            }
            return *this;
        }

        ArrayList& operator=(ArrayList&& ary)
        {
            List<T>::operator=(ary);
            m_capacity = ary.m_capacity;
            m_arr = ary.m_arr;
            
            ary.m_arr = nullptr;
            ary.m_size = 0;
            ary.m_capacity = DEFAULT_CAPACITY;
            return *this;
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

    // 建议：即使一个常量静态数据成员在类内部被初始化了，通常情况下也应该在类的外部定义一下该成员。
    template<typename T>
    constexpr int ArrayList<T>::DEFAULT_CAPACITY;


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
    void ArrayList<T>::add(int index, const T& element)
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