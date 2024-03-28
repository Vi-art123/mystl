//
// Created by wyx on 2024/3/28.
// 归并排序
//

#include <MergeSort.h>
#include <TimeCount.h>

namespace mystd
{
    void MergeSort::sort()
    {
        TimeCount _time;
        sort(0, m_size);
        timeCount = _time.count();
    }

    /**
     * 对[begin, end)范围的数据进行归并排序
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

    void MergeSort::merge(int begin, int mid, int end)
    {

    }
} // namespace mystd
