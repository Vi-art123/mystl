//
// Created by wyx on 2024/3/27.
// 选择排序法
//
#pragma once

#include "Sort.h"

namespace mystd
{
    class SelectSort : public Sort
    {
    public:
        SelectSort(int *arr, int size) : Sort(arr, size, "SelectSort") {}
        void sort() override;
    };
}
