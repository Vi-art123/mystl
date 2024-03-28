//
// Created by wyx on 2024/3/27.
// 排序算法基类
//
#pragma once

#include <memory>

namespace mystd
{
    enum class SortOrder : bool
    {
        ASC = true,
        DESC = false
    };

    class Sort
    {
    public:
        Sort(int *arr, int size, std::string  s_name = "null");
        Sort(const Sort&) = delete;
        Sort(Sort&&) = delete;
        virtual ~Sort() = default;

        Sort& operator=(const Sort&) = delete;

        virtual void sort() = 0;

        [[nodiscard]] uint64_t getCountCompare() const noexcept { return countCompare; }
        [[nodiscard]] uint64_t getSwapCount() const noexcept { return swapCount; }
        [[nodiscard]] int64_t getTimeCount() const noexcept { return timeCount; }
        void setOrder(SortOrder order) { _order = order; }
        std::string getSortName() { return sort_name; }
        [[nodiscard]] bool is_ordered() const;

        void to_string() const;

    protected:
        int compare(int v1, int v2) noexcept
        {
            countCompare++;
            return (_order == SortOrder::ASC) ? v1 - v2 : v2 - v1;
        }

        void swap(int& v1, int& v2) noexcept
        {
            swapCount++;
            std::swap(v1, v2);
        }

    protected:
        int m_size = 0;
        int64_t timeCount = 0;
        std::unique_ptr<int[]> m_arr;
    private:
        uint64_t countCompare = 0;
        uint64_t swapCount = 0;
        std::string sort_name;
        SortOrder _order = SortOrder::ASC;
    };
}