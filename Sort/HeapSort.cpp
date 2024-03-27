//
// Created by wyx on 2024/3/27.
// 堆排序法
//

#include <HeapSort.h>
#include <TimeCount.h>

namespace mystd
{
    void HeapSort::sort()
    {
        TimeCount _time;
        // 原地建堆
        heapSize = m_size;
        for (int i = (heapSize >> 1) - 1; i >= 0; i--) {
            sift_down(i);
        }

        while (heapSize > 1)
        {
            // 交换堆顶元素和尾部元素
            swap(m_arr[0], m_arr[--heapSize]);

            // 对0位置进行sift_down（恢复堆的性质）
            sift_down(0);
        }

        timeCount = _time.count();
    }

    void HeapSort::sift_down(int index)
    {
        int half = heapSize >> 1;
        // 必须保证index位置是非叶子节点（index小于第一个叶子节点的索引）
        // 第一个叶子节点的索引等于非叶子节点的数量
        while (index < half)
        {
            // index位置的节点有2种情况（完全二叉树性质）
            // 1.只有左子节点
            // 2.同时有左右子节点

            // 默认为左子节点跟它进行比较
            int childIndex = (index << 1) + 1;

            // 右子节点
            int rightIndex = childIndex + 1;

            // 选出左右子节点最大的那个
            if (rightIndex < heapSize && compare(m_arr[rightIndex], m_arr[childIndex]) > 0) {
                childIndex = rightIndex;
            }

            if (compare(m_arr[index], m_arr[childIndex]) >= 0) return;

            // 将子节点与index交换
            swap(m_arr[index], m_arr[childIndex]);

            index = childIndex;
        }
    }
} // namespace mystd
