//
// Created by wyx on 2024/3/27.
// 排序算法基类
//
#pragma once

#include <utility>
#include <string>

namespace mystd
{
    class Sort
    {
    public:
        Sort(int *arr, int size, std::string s_name = "null");
        Sort(const Sort&) = delete;
        Sort(Sort&&) = delete;
        virtual ~Sort() { delete[] m_arr; }

        Sort& operator=(const Sort&) = delete;

        virtual void sort() = 0;

        [[nodiscard]] int getCountCompare() const noexcept { return countCompare; }
        [[nodiscard]] int getSwapCount() const noexcept { return swapCount; }

        void to_string() const;

    protected:
        int compare(int v1, int v2) noexcept
        {
            countCompare++;
            return v1 - v2;
        }

        void swap(int& v1, int& v2) noexcept
        {
            swapCount++;
            std::swap(v1, v2);
        }

    protected:
        int m_size = 0;
        int64_t timeCount = 0;
        int *m_arr = nullptr;
    private:
        int countCompare = 0;
        int swapCount = 0;
        std::string sort_name;
    };
}