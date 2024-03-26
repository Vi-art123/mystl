//
// Created by wyx on 2024/3/27.
//
#include <AVLTree.hpp>
#include <RBTree.hpp>
#include <CircleLinkedList.hpp>
#include <SinglyLinkedList.hpp>
#include <SinglyCircleLinkedList.hpp>
#include <Stack.hpp>
#include <Queue.hpp>
#include <Deque.hpp>
#include <PriorityQueue.hpp>
#include <ListSet.hpp>
#include <TreeSet.hpp>
#include <TreeMap.hpp>
#include <BinaryHeap.hpp>

#include "test_data_structure.h"


void testTree()
{
    mystd::RBTree<int> bst;
    // int arr[] = {7, 9, 4, 2, 5, 8, 11, 1, 3, 10, 12};
//    int arr[] = {7, 9, 4, 2, 5, 8, 11, 1, 3};
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int len = sizeof arr/sizeof arr[0];
    for (int i = 0; i < len; ++i) {
        bst.add(arr[i]);
//        bst.to_string();
//        std::cout << "---------------------------------" << std::endl;
    }
#if 1
    bst.to_string();
    std::cout << "---------------------------------" << std::endl;
    for (int i = 0; i < len; ++i) {
        bst.remove(arr[i]);
        bst.to_string();
        std::cout << "---------------------------------" << std::endl;
    }
#endif
    std::cout << std::endl;
    std::cout << "size=" << bst.size() << std::endl;
    std::cout << "height=" << bst.height() << std::endl;

//    bst.invertTree();
//    bst.to_string();
}

void testArray()
{
    mystd::ArrayList<int> al;
    int arr[] = {7, 9, 4, 2, 5, 8, 11, 1, 3, 10, 12};
    int len = sizeof arr/sizeof arr[0];
    for (int i = 0; i < len; ++i) {
        al.push_back(arr[i]);
    }

//    al.pop_back();
//    al.set(8, 6);
//    al.add(8, 6);
    al.to_string();
//    std::cout << al.get(9) << std::endl;
}

void testLink()
{
    mystd::CircleLinkedList<int> ll;
    int arr[] = {7, 9, 4, 2, 5, 8, 11, 1, 3, 10, 12};
    int len = sizeof arr/sizeof arr[0];
    for (int i = 0; i < len; ++i) {
        ll.push_back(arr[i]);
    }

    {
        decltype(ll) list = ll;
        ll.to_string();
    }

//    ll.pop_back();
//    ll.set(8, 6);
//    ll.add(8, 6);
//    ll.to_string();
//    ll.reverse();
//    ll.add(0, 6);
//    ll.pop_back();
    ll.to_string();
//    std::cout << ll.get(9) << std::endl;
}

void testStack()
{
    mystd::Stack<int> stack;
    int arr[] = {7, 9, 4, 2, 5, 8, 11, 1, 3, 10, 12};
    int len = sizeof arr/sizeof arr[0];
    for (int i = 0; i < len; ++i) {
        stack.push(arr[i]);
    }

    stack.pop();
    stack.to_string();
    std::cout << stack.top() << std::endl;
}

void testQueue()
{
    mystd::PriorityQueue<int> queue;
    int arr[] = {7, 9, 4, 2, 5, 8, 11, 1, 3, 10, 12};
    int len = sizeof arr/sizeof arr[0];
    for (int i = 0; i < len; ++i) {
        queue.enQueue(arr[i]);
    }

//    queue.deQueue();
    queue.to_string();
    std::cout << queue.front() << std::endl;
}

void testSet()
{
    mystd::TreeSet<int> set;
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 9};
    int len = sizeof arr/sizeof arr[0];
    for (int i = 0; i < len; ++i) {
        set.add(arr[i]);
    }

    set.traversal();
}

void testMap()
{
    mystd::TreeMap<std::string, int> tmap;
    tmap.put("wyx", 1);
    tmap.put("zs", 2);
    tmap.put("ls", 3);
    tmap.put("ww", 78);

    tmap.traversal();
}

void testHeap()
{
    // topK问题

    // 创建一个小顶堆
    mystd::BinaryHeap<int> heap([](const int& v1, const int& v2) -> int {
        return v2 - v1;
    });

    // 找出最大的前k个数
    int k = 5;
    int arr[] = {
            7, 9, 4, 2, 5, 8, 11, 1, 3, 10, 12, 13, 20, 6
    };
    int len = sizeof arr/sizeof arr[0];
    for (int i = 0; i < len; ++i) {
        if (heap.size() < k) {  // 前k个数添加到小顶堆
            heap.add(arr[i]);
        } else if (arr[i] > heap.get()) {  // 如果是第k+1个数，并且大于堆顶
            heap.replace(arr[i]);
        }
    }
//    mystd::BinaryHeap<int> heap(arr, len);

    heap.to_string();
}