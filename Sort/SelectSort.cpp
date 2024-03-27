//
// Created by wyx on 2024/3/27.
// 选择排序法
//

#include <SelectSort.h>
#include <TimeCount.h>

namespace mystd
{
    void SelectSort::sort()
    {
        TimeCount _time;
        for (int end = m_size - 1; end > 0; end--) {
            int maxIndex = 0;
            for (int begin = 1; begin <= end; begin++) {
                if (compare(m_arr[maxIndex], m_arr[begin]) <= 0) {
                    maxIndex = begin;
                }
                swap(m_arr[maxIndex], m_arr[end]);  // 找到最大的放末尾
            }
        }
        timeCount = _time.count();
    }
} // namespace mystd
