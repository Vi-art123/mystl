//
// Created by wyx on 2024/3/27.
// 测试算法功能
//

#include "test_algorithm.h"
#include <BubbleSort.h>
#include <SelectSort.h>
#include <HeapSort.h>
#include <thread>
#include <iostream>
#include <random>
#include <TimeCount.h>


void testSort()
{
    constexpr int min = 0;
    constexpr int max = 10000;
    int arr[max];

    std::random_device seed;    // 硬件生成随机数种子
    std::ranlux48 engine(seed());   // 利用种子生成随机数引擎
    std::uniform_int_distribution<> distrib(min, max);
    for (int i = 0; i < max; i++) {
        arr[i] = distrib(engine);   // 随机数
    }
    int len = max;

    mystd::BubbleSort bubble(arr, len);
    bubble.sort();
    bubble.to_string();

    mystd::SelectSort select(arr, len);
    select.sort();
    select.to_string();

    mystd::HeapSort heap(arr, len);
    heap.sort();
    heap.to_string();
}

void testTime()
{
    mystd::TimeCount::test("testTime", []{std::this_thread::sleep_for(std::chrono::milliseconds(500));});
}