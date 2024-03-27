//
// Created by wyx on 2024/3/27.
// 冒泡排序法
//
#pragma once

#include "Sort.h"

namespace mystd
{
    class BubbleSort : public Sort
    {
    public:
        BubbleSort(int *arr, int size) : Sort(arr, size, "BubbleSort") {}
        void sort() override;
    };
}
