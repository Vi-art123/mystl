//
// Created by wyx on 2024/3/27.
// 插入排序法，最坏（逆序对最多）的时间复杂度为O(n^2)，最好（逆序对为0）的时间复杂度为O(n)
// 空间复杂度为O(1)
//

#include <InsertionSort.h>
#include <TimeCount.h>

namespace mystd
{
    void InsertionSort::sort()
    {
        TimeCount _time;
#if 0   // 原始写法
        for (int begin = 1; begin < m_size; begin++) {
            int curr = begin;
            while(curr > 0 && compare(m_arr[curr], m_arr[curr - 1]) < 0)
            {
                swap(m_arr[curr], m_arr[curr - 1]);
                curr--;
            }
        }
#endif
        // 优化版本，使用二分法优化
        for (int begin = 1; begin < m_size; begin++) {
            int insertIndex = binary_search(begin);
            for (int i = begin; i > insertIndex; i--) {
                swap(m_arr[i], m_arr[i - 1]);
            }
        }
        timeCount = _time.count();
    }

    /**
     * 使用二分查找找到合适的插入位置
     * @param index
     * @return
     */
    int InsertionSort::binary_search(int index) noexcept
    {
        int begin = 0;
        int end = index;
        while (begin < end)
        {
            int mid = (begin + end) >> 1;
            if (compare(m_arr[index], m_arr[mid]) < 0) {
                end = mid;
            } else {
                begin = mid + 1;
            }
        }
        return begin;
    }
} // namespace mystd
