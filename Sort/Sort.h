//
// Created by wyx on 2024/3/27.
// 排序算法基类
//
#pragma once

namespace mystd
{
    class Sort
    {
    public:
        Sort() = default;
        Sort(const Sort&) = default;
        Sort(Sort&&) = default;
        virtual ~Sort() = default;

        virtual void sort(int array[], int size) = 0;

        [[nodiscard]] int getCountCompare() const noexcept { return countCompare; }

    protected:
        int compare(int v1, int v2) noexcept
        {
            countCompare++;
            return v1 - v2;
        }

    private:
        int countCompare = 0;
    };
}