//
// Created by wyx on 2024/3/17.
// 链表节点定义
//
#pragma once

#include <iostream>
#include <memory>

namespace mystd
{
    template<typename T>
    struct Node
    {
        T value;
        std::shared_ptr<Node> next;
        std::weak_ptr<Node> prev;
        Node(const T& val, decltype(next) n, decltype(prev) p = decltype(next)(nullptr)) : value(val), next(n), prev(p) {}
//        ~Node() { std::cout << "delete Node: " << value << std::endl; }
    };
}