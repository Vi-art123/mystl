//
// Created by wyx on 2024/3/27.
// 计时统计
//
#pragma once

#include <chrono>
#include <iomanip>
#include <functional>
#include <iostream>

namespace mystd
{
    class TimeCount
    {
        using time_point_t = std::chrono::high_resolution_clock::time_point;
        time_point_t start_time = std::chrono::high_resolution_clock::now();
    public:
        int64_t count()
        {
            time_point_t end_time = std::chrono::high_resolution_clock::now();
            return std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
        }

        static void test(const std::string& name, const std::function<void()>& test_func);
    };
}