//
// Created by wyx on 2024/3/28.
// 归并排序
//

#include "MergeSort.h"
#include <TimeCount.h>

namespace mystd
{
    void MergeSort::sort()
    {
        TimeCount _time;
        left_arr = std::make_unique<int[]>(m_size >> 1);
        sort(0, m_size);
        timeCount = _time.count();
    }

    /**
     * 对 [begin, end) 范围的数据进行归并排序
     * @param {int} begin
     * @param {int} end
     * @return 
     */    
    void MergeSort::sort(int begin, int end)
    {
        if ((end - begin) < 2) return;

        int mid = (begin + end) >> 1;
        sort(begin, mid);
        sort(mid, end);
        merge(begin, mid, end);
    }

    /**
     * 将 [begin, mid) 和 [mid, end) 范围的序列合并成一个有序序列
     * @param begin
     * @param mid
     * @param end
     */
    void MergeSort::merge(int begin, int mid, int end)
    {
        int li = 0, le = mid - begin;
        int ri = mid, re = end;
        int ai = begin;

        // 备份左边数组
        memcpy(left_arr.get(), m_arr.get() + begin, sizeof(int) * le);

        // 如果左边还没结束
        while (li < le)
        {
            if (ri < re && compare(left_arr[li], m_arr[ri]) > 0) {
                m_arr[ai++] = m_arr[ri++];
            } else {
                m_arr[ai++] = left_arr[li++];
            }
        }
    }
} // namespace mystd
