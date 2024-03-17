//
// Created by wyx on 2024/3/17.
// 栈
//
#pragma once

#include <ArrayList.hpp>

namespace mystd
{
    template<typename T>
    class Stack
    {
    public:
        int size() { return arrayList.size(); }
        bool isEmpty() { return arrayList.isEmpty(); }
        void push(const T& value) { arrayList.push_back(value); }
        void pop() { arrayList.pop_back(); }
        T top() { return arrayList.get(arrayList.size() - 1); }
        void to_string() { arrayList.to_string(); }

    private:
        ArrayList<T> arrayList;
    };
}