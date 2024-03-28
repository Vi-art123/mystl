//
// Created by wyx on 2024/3/28.
// 归并排序
//
#pragma once

#include "Sort.h"

namespace mystd
{
    class MergeSort : public Sort
    {
    public:
        MergeSort(int *arr, int size) : Sort(arr, size, "MergeSort") {}
        void sort() override;

    private:
        void sort(int begin, int end);
        void merge(int begin, int mid, int end);
    };
}
