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
        explicit ArrayList(int capacity)
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
            m_arr = new T[m_capacity];
            for (int i = 0; i < this->m_size; i++) {
                m_arr[i] = ary.m_arr[i];
            }
        }

        ArrayList(ArrayList&& ary) noexcept : List<T>(std::move(ary)), m_capacity(ary.m_capacity), m_arr(ary.m_arr)
        {
            ary.m_arr = nullptr;
            ary.m_size = 0;
            ary.m_capacity = DEFAULT_CAPACITY;
        }

        ArrayList& operator=(const ArrayList& ary) noexcept
        {
            // 先拷贝一个临时对象，再交换到当前对象，避免自我赋值和异常
            ArrayList(ary).swap(*this);
            return *this;
        }

        ArrayList& operator=(ArrayList&& ary) noexcept
        {
#if 0
            List<T>::operator=(std::move(ary));
            m_capacity = ary.m_capacity;
            m_arr = ary.m_arr;

            ary.m_arr = nullptr;
            ary.m_size = 0;
            ary.m_capacity = DEFAULT_CAPACITY;
#endif
            // 使用上面注释掉的也可以正常赋值，和下面这个相比哪个效率高？
            // 先移动到一个临时对象，再交换到当前对象
            ArrayList(std::move(ary)).swap(*this);  // 这里的交换效率高吗？
            return *this;
        }

        void add(int index, const T& element) override;
        void remove(int index) override;
        void clear() noexcept override { this->m_size = 0; }
        T get(int index) const override;
        void set(int index, const T& element) override;
        int capacity() noexcept { return m_capacity; }
        int index_of(const T& element) const override;
        void to_string() const;

    private:
        [[nodiscard]] int free_space() const noexcept { return m_capacity - this->m_size; }
        void ensure_capacity();
        void swap(ArrayList& ary) noexcept;

    private:
        static constexpr int DEFAULT_CAPACITY = 10;
        int m_capacity = DEFAULT_CAPACITY;
        T *m_arr = nullptr;
    };

    template<typename T>
    inline void ArrayList<T>::swap(ArrayList &ary) noexcept
    {
        std::swap(m_arr, ary.m_arr);
        std::swap(this->m_size, ary.m_size);
        std::swap(m_capacity, ary.m_capacity);
    }

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
        for (int i = 0; i < this->m_size; i++) {
            new_arr[i] = m_arr[i];
        }
        delete[] m_arr;
        m_arr = new_arr;
    }

    template<typename T>
    void ArrayList<T>::add(int index, const T& element)
    {
        this->check_add_index(index);

        ensure_capacity();

        for (int i = this->m_size - 1 ; i >= index; i--) {
            m_arr[i + 1] = m_arr[i];
        }
        m_arr[index] = element;
        this->m_size++;
    }

    template<typename T>
    void ArrayList<T>::remove(int index)
    {
        this->check_index(index);

        for (int i = index + 1; i < this->m_size - 1; i++) {
            m_arr[i - 1] = m_arr[i];
        }
        this->m_size--;
    }

    template<typename T>
    inline int ArrayList<T>::index_of(const T& element) const
    {
        for (int i = 0; i < this->m_size; i++) {
            if (m_arr[i] == element) return i;
        }

        return this->ELEMENT_NOT_FOUND;
    }


    template<typename T>
    inline T ArrayList<T>::get(int index) const
    {
        this->check_index(index);
        return m_arr[index];
    }

    template<typename T>
    inline void ArrayList<T>::set(int index, const T& element)
    {
        this->check_index(index);
        m_arr[index] = element;
    }

    template<typename T>
    void ArrayList<T>::to_string() const
    {
        std::cout << "size:" << this->m_size << " ";
        std::cout << "{";
        for (int i = 0; i < this->m_size; i++) {
            std::cout << m_arr[i];
            if (i != this->m_size - 1) std::cout << ", ";
        }
        std::cout << "}" << std::endl;
    }
} // mystd