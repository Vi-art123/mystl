//
// Created by wyx on 2024/3/24.
// 映射/字典（Map）抽象基类
//
#pragma once

namespace mystd
{
    template<typename K, typename V>
    class Map
    {
    public:
        Map() = default;
        Map(const Map& map) = default;
        Map(Map&& map) = default;
        virtual ~Map() = default;

        [[nodiscard]] virtual int size() const noexcept = 0;
        [[nodiscard]] virtual bool isEmpty() const noexcept = 0;
        virtual void clear() = 0;
        virtual V put(const K& key, const V& value) = 0;
        virtual V get(const K& key) const = 0;
        virtual void remove(const K& key) = 0;
        virtual bool containsKey(const K& key) const = 0;
        virtual bool containsValue(const V& value) const = 0;
        virtual void traversal() = 0;
    };
}