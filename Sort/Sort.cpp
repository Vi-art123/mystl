//
// Created by wyx on 2024/3/27.
// 排序算法基类
//

#include <Sort.h>
#include <string.h>
#include <iostream>

namespace mystd
{
    Sort::Sort(int *arr, int size, std::string s_name) : m_size(size), sort_name(s_name)
    {
        m_arr = new int[m_size];
        memcpy(m_arr, arr, sizeof(int) * m_size);
    }

    void Sort::to_string() const
    {
        std::cout << "【" + sort_name + "】" << std::endl;
#if 0
        std::cout << "size=" << m_size << ", ";
        std::cout << "{";
        for (int i = 0; i < m_size; i++) {
            if (i != 0)
                std::cout << ", ";
            std::cout << m_arr[i];
        }
        std::cout << "}";
        std::cout << std::endl;
#endif
        std::cout << "耗时：" << std::fixed << timeCount/1000000.0 << " s    ";
        std::cout << "比较：" << getCountCompare() << "    ";
        std::cout << "交换：" << getSwapCount() << std::endl;
        std::cout << "--------------------------------------------------------------" << std::endl;
    }
}