//
// Created by wyx on 2024/3/27.
// 测试算法功能
//

#include "test_algorithm.h"
#include <BubbleSort.h>
#include <SelectSort.h>
#include <HeapSort.h>
#include <InsertionSort.h>
#include <thread>
#include <iostream>
#include <random>
#include <TimeCount.h>


void testSort(std::vector<std::shared_ptr<mystd::Sort>>& sorts)
{
    if (sorts.empty()) {
        return;
    }

    for (const auto& s : sorts) {
        s->sort();
    }

    auto SortFunc = [](decltype(sorts[0])& s1, decltype(sorts[0])& s2) -> bool {
        return s1->getTimeCount() < s2->getTimeCount();
    };
    // 按耗时情况排序
    std::sort(sorts.begin(), sorts.end(), SortFunc);

    for (const auto& s : sorts) {
        s->to_string();
    }
}

void testSort()
{
    constexpr int min = 0;
    constexpr int max = 10000;
    int arr[max] = {0};

    std::random_device seed;    // 硬件生成随机数种子
    std::ranlux48 engine(seed());   // 利用种子生成随机数引擎
    std::uniform_int_distribution<> distrib(min, max);
    for (int & i : arr) {
        i = distrib(engine);   // 随机数
    }
    int len = max;

    std::vector<std::shared_ptr<mystd::Sort>> sorts;
    sorts.emplace_back(std::make_shared<mystd::SelectSort>(arr, len));
    sorts.emplace_back(std::make_shared<mystd::BubbleSort>(arr, len));
    sorts.emplace_back(std::make_shared<mystd::HeapSort>(arr, len));
    sorts.emplace_back(std::make_shared<mystd::InsertionSort>(arr, len));
    testSort(sorts);
}

void testTime()
{
    mystd::TimeCount::test("testTime", []{std::this_thread::sleep_for(std::chrono::milliseconds(500));});
}