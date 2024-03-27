//
// Created by wyx on 2024/3/27.
// 插入排序法
//
#pragma once

#include "Sort.h"

namespace mystd
{
    class InsertionSort : public Sort
    {
    public:
        InsertionSort(int *arr, int size) : Sort(arr, size, "InsertionSort") {}
        void sort() override;

    private:
        [[nodiscard]] int binary_search(int v) noexcept;
    };
}
