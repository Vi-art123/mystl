//
// Created by wyx on 2024/3/27.
// 冒泡排序法
//
#pragma once

#include "Sort.h"
#include <utility>

namespace mystd
{
    class SelectSort : public Sort
    {
    public:
        void sort(int arr[], int size) override;
    };

    void SelectSort::sort(int *arr, int size)
    {
        for (int end = size - 1; end > 0; end--) {
            int maxIndex = 0;
            for (int begin = 1; begin <= end; begin++) {
                if (compare(arr[maxIndex], arr[begin]) <= 0) {
                    maxIndex = begin;
                }
                std::swap(arr[maxIndex], arr[end]);
            }
        }
    }
}
