//
// Created by wyx on 2024/3/28.
// 快速排序
//

#include <QuickSort.h>
#include <TimeCount.h>
#include <random>

namespace mystd
{
    void QuickSort::sort()
    {
        TimeCount _time;
        sort(0, m_size);
        timeCount = _time.count();
    }

    /**
     * 对 [begin, end) 范围的数据进行快速排序
     * @param begin
     * @param end
     */
    void QuickSort::sort(int begin, int end)
    {
        if ((end - begin) < 2) return;

        // 确定轴点位置
        int mid = pivotIndex(begin, end);
        // 对子序列也进行快速排序
        sort(begin, mid);
        sort(mid + 1, end);
    }

    /**
     * 构造出 [begin, end) 范围的轴点位置
     * @param begin
     * @param end
     * @return 轴点元素的最终位置
     */
    int QuickSort::pivotIndex(int begin, int end)
    {
#if 0
        // 选取轴点降低最坏情况发生的概率
        // 随机选择一个轴点跟begin位置交换
        std::random_device seed;
        std::ranlux48 e(seed());
        std::uniform_int_distribution<int> distribution(begin, end - 1);
        swap(m_arr[distribution(e)], m_arr[begin]);
#endif
        // 备份begin位置的元素
        int pivot = m_arr[begin];
        // end指向最后一个元素
        end--;

        while (begin < end)
        {
            while (begin < end)
            {
                // 从右往左
                if (compare(pivot, m_arr[end]) < 0) {   // 右边元素 > 轴点元素
                    end--;
                } else {    // 右边元素 <= 元素
                    m_arr[begin++] = m_arr[end];
                    break;
                }
            }

            while (begin < end)
            {
                // 从左往右
                if (compare(pivot, m_arr[begin]) > 0) { // 左边元素 < 轴点元素
                    begin++;
                } else {    // 左边元素 >= 元素
                    m_arr[end--] = m_arr[begin];
                    break;
                }
            }
        }

        // 将轴点元素放入最终位置
        m_arr[begin] = pivot;
        // 返回轴点元素的位置
        return begin;
    }
} // namespace mystd
