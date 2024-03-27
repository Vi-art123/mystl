//
// Created by wyx on 2024/3/27.
// 测试算法功能
//

#include "test_algorithm.h"
#include <BubbleSort.h>
#include <SelectSort.h>
#include <HeapSort.h>
#include <thread>


void testSort()
{
    int arr[] = {7, 9, 4, 2, 5, 8, 11, 1, 3, 10, 12, 9};
    int len = sizeof arr/sizeof arr[0];

    std::cout << "--------------------------------------------------------------" << std::endl;
    mystd::BubbleSort bubble(arr, len);
    bubble.sort();
    bubble.to_string();
    std::cout << "--------------------------------------------------------------" << std::endl;

    mystd::SelectSort select(arr, len);
    select.sort();
    select.to_string();
    std::cout << "--------------------------------------------------------------" << std::endl;

    mystd::HeapSort heap(arr, len);
    heap.sort();
    heap.to_string();
    std::cout << "--------------------------------------------------------------" << std::endl;
}

void testTime()
{
    mystd::TimeCount::test("testTime", []{std::this_thread::sleep_for(std::chrono::milliseconds(500));});
}