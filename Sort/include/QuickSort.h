//
// Created by wyx on 2024/3/28.
// 快速排序
//
#pragma once

#include "Sort.h"

namespace mystd
{
    class QuickSort : public Sort
    {
    public:
        QuickSort(int *arr, int size) : Sort(arr, size, "QuickSort") {}
        void sort() override;

    private:
        void sort(int begin, int end);
        int pivotIndex(int begin, int end);
    };
}
