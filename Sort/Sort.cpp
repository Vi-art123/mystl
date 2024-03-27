//
// Created by wyx on 2024/3/27.
// 排序算法基类
//

#include <Sort.h>
#include <cstring>
#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>

namespace mystd
{
    Sort::Sort(int *arr, int size, std::string s_name) : m_size(size), sort_name(std::move(s_name))
    {
        m_arr = new int[m_size];
        memcpy(m_arr, arr, sizeof(int) * m_size);
    }

    void Sort::to_string() const
    {
        std::cout << "<<" + sort_name + ">>" << std::endl;
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
        std::cout << "ordered: " << std::boolalpha << is_ordered() << std::endl;
        std::cout << "elapsed time: " << std::fixed << static_cast<double>(timeCount/1000000.0) << " s    ";
        std::cout << "compare count: " << getCountCompare() << "    ";
        std::cout << "swap count: " << getSwapCount() << std::endl;
        std::cout << "------------------------------------------------------------------------------------------------------" << std::endl;
    }

    inline bool Sort::is_ordered() const
    {
        std::vector<int> test_vec(m_arr, m_arr + m_size);
        return std::is_sorted(test_vec.begin(), test_vec.end());
    }
}