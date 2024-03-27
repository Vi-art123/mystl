//
// Created by wyx on 2024/3/27.
// 排序算法基类
//
#pragma once

#include <utility>
#include <string>

namespace mystd
{
    enum SortOrder
    {
        ASC = true,
        DESC = false
    };

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
        void setOrder(SortOrder order) { _order = order; }

        void to_string() const;

    protected:
        int compare(int v1, int v2) noexcept
        {
            countCompare++;
            return (_order == ASC) ? v1 - v2 : v2 - v1;
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
        uint64_t countCompare = 0;
        uint64_t swapCount = 0;
        std::string sort_name;
        SortOrder _order = ASC;
    };
}