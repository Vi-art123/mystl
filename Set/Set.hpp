//
// Created by wyx on 2024/3/24.
// 集合抽象类
//
#pragma once

namespace mystd
{
    template<typename T>
    class Set
    {
    public:
        Set() = default;
        Set(const Set& set) = default;
        Set(Set&& set) = default;
        virtual ~Set() = default;

        [[nodiscard]] virtual int size() const noexcept = 0;
        [[nodiscard]] virtual bool isEmpty() const noexcept = 0;
        virtual void clear() = 0;
        virtual bool contains(const T& value) const = 0;
        virtual void add(const T& value) = 0;
        virtual void remove(const T& value) = 0;
        virtual void traversal() = 0;
    };
}
