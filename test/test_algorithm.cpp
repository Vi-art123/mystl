//
// Created by wyx on 2024/3/27.
// 测试算法功能
//

#include "test_algorithm.h"
#include <iostream>
#include <BubbleSort.h>
#include <SelectSort.h>

static void printArr(int arr[], int len)
{
    std::cout << "size=" << len << ", ";
    std::cout << "{";
    for (int i = 0; i < len; i++) {
        if (i != 0)
            std::cout << ", ";
        std::cout << arr[i];
    }
    std::cout << "}";
    std::cout << std::endl;
}

void testSort()
{
//    mystd::BubbleSort st;
    mystd::SelectSort st;
    int arr[] = {7, 9, 4, 2, 5, 8, 11, 1, 3, 10, 12};
    int len = sizeof arr/sizeof arr[0];
    st.sort(arr, len);
    printArr(arr, len);
    std::cout << st.getCountCompare() << std::endl;
}