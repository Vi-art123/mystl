//
// Created by wyx on 2024/3/27.
// 堆排序法
//
#pragma once

#include "Sort.h"

namespace mystd
{
    class HeapSort : public Sort
    {
        int heapSize = 0;
        void sift_down(int index);
    public:
        HeapSort(int *arr, int size) : Sort(arr, size, "HeapSort") {}
        void sort() override;
    };
}
