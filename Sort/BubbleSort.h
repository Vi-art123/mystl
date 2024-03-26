//
// Created by wyx on 2024/3/27.
// 冒泡排序法
//
#pragma once

#include "Sort.h"
#include <utility>

namespace mystd
{
    class BubbleSort : public Sort
    {
    public:
        void sort(int arr[], int size) override;
    };

    void BubbleSort::sort(int *arr, int size)
    {
#if 0
        // 原始版，全遍历
        for (int end = size - 1; end > 0; end--) {
            for (int begin = 1; begin < size; begin++) {
                if (compare(m_arr[begin], m_arr[begin - 1]) < 0) {
                    std::swap(m_arr[begin], m_arr[begin - 1]);
                }
            }
        }
#endif
        // 最坏、平均时间复杂度 O(n^2)
        // 最好时间复杂度 O(n)
        // 空间复杂度 O(1)
        for (int end = size - 1; end > 0; end--) {
            int sortIndex = 1;  // 初始值为1，当没有发生交换时，代表已经是有序的，直接退出循环
            for (int begin = 1; begin < size; begin++) {
                if (compare(arr[begin], arr[begin - 1]) < 0) {
                    std::swap(arr[begin], arr[begin - 1]);
                    sortIndex = begin;
                }
            }
            end = sortIndex;    // 记录最后一次交换的位置（该位置后面的数都是有序的，无需重复遍历）
        }
    }
}
