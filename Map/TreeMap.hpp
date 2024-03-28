//
// Created by wyx on 2024/3/24.
// 基于红黑树实现的map
//
#pragma once

#include "Map.hpp"
#include <RBTree.hpp>

namespace mystd
{
    template<typename K, typename V>
    class TreeMap : public Map<K, V>
    {
    private:
        struct TMNode
        {
            K key;
            V value;

            RBColor color = RBColor::RED;    // 默认为红色，这样能够让红黑树的性质尽快满足（性质1，2，3，5都满足，性质4不一定）

            std::weak_ptr<TMNode> parent;
            std::shared_ptr<TMNode> left;
            std::shared_ptr<TMNode> right;
            TMNode() = default;
            TMNode(const TMNode& node) = default;
            TMNode(TMNode&& node) = default;
            TMNode(const K& k, const V& val, std::weak_ptr<TMNode> p) : key(k), value(val), parent(p) {}
            // virtual ~TMNode() { std::cout << "delete TMNode: " << key << ":" << value << std::endl; }


            /**
             * 度是否为2
             * @return 
             */
            [[nodiscard]] bool hasTwoChildren() const noexcept
            {
                return (left != nullptr && right != nullptr);
            }

            /**
             * 是否为叶子节点
             * @return 
             */
            [[nodiscard]] bool isLeaf() const noexcept
            {
                return (left == nullptr && right == nullptr);
            }

            /**
             * 判断节点是否在左边
             * @return 
             */
            [[nodiscard]] bool isLeftChild() const noexcept
            {
                return (parent.lock() && this == parent.lock()->left.get());
            }

            /**
             * 判断节点是否在右边
             * @return 
             */
            [[nodiscard]] bool isRightChild() const noexcept
            {
                return (parent.lock() && this == parent.lock()->right.get());
            }

            /**
             * 获取兄弟节点
             * @return
             */
            std::shared_ptr<TMNode> sibling() const noexcept
            {
                if (!parent.lock()) {
                    return nullptr;
                }
                return isLeftChild() ? parent.lock()->right : parent.lock()->left;
            }
        };
    public:
        [[nodiscard]] int size() const noexcept override { return m_size; }
        [[nodiscard]] bool isEmpty() const noexcept override { return m_size == 0; }
        void clear() override
        {
            root = nullptr; // 自动释放内存
            m_size = 0;
        }

        void inOrderTraverse()
        {
            if (root == nullptr) return;
            inOrderTraverse(root);
        }

        V put(const K& key, const V& value) override;

        V get(const K& key) const override;
        void remove(const K& key) override { remove(get_node(key)); }
        bool containsKey(const K& key) const override;
        bool containsValue(const V& value) const override;
        void traversal() override;

    private:
        std::shared_ptr<TMNode> get_node(const K& key) const;
        std::shared_ptr<TMNode> predecessor(std::shared_ptr<TMNode> node);
        std::shared_ptr<TMNode> make_color(std::shared_ptr<TMNode> node, RBColor color);
        std::shared_ptr<TMNode> make_red(std::shared_ptr<TMNode> node) { return make_color(node, RBColor::RED); }
        std::shared_ptr<TMNode> make_black(std::shared_ptr<TMNode> node) { return make_color(node, RBColor::BLACK); }

        bool isRed(std::shared_ptr<TMNode> node) const noexcept { return colorOf(node) == RBColor::RED; }
        bool isBlack(std::shared_ptr<TMNode> node) const noexcept { return colorOf(node) == RBColor::BLACK; }
        void remove(std::shared_ptr<TMNode> node);
        void afterAdd(std::shared_ptr<TMNode> node);
        void afterRemove(std::shared_ptr<TMNode> node);
        void rotateLeft(std::shared_ptr<TMNode> grand);
        void rotateRight(std::shared_ptr<TMNode> grand);
        void afterRotate(std::shared_ptr<TMNode> grand,
                         std::shared_ptr<TMNode> parent,
                         std::shared_ptr<TMNode> child);
        void inOrderTraverse(std::shared_ptr<TMNode> node);

        RBColor colorOf(std::shared_ptr<TMNode> node) const noexcept
        {
            // 空节点为黑色
            return node == nullptr ? RBColor::BLACK : node->color;
        }

        int compare(const K& k1, const K& k2) const
        {
            if (k1 == k2) return 0;
            return k1 < k2 ? -1 : 1;
        }

    private:
        int m_size = 0;
        std::shared_ptr<TMNode> root;
    };

    template<typename K, typename V>
    V TreeMap<K, V>::put(const K& key, const V& value)
    {
        // 第一次添加
        if (root == nullptr) {
            root = std::make_shared<TMNode>(key, value, root);
            m_size++;
            // 新添加节点之后的处理
            afterAdd(root);
            return value;
        }

        int cmp = 0;
        auto node = root;
        auto parent = root;
        while (node != nullptr) {
            parent = node;
            cmp = compare(node->key, key);
            if (cmp > 0) {
                node = node->left;
            } else if (cmp < 0) {
                node = node->right;
            } else {    // 相等则覆盖
                V oldValue = node->value;
                node->value = value;
                return oldValue;
            }
        }

        auto new_node = std::make_shared<TMNode>(key, value, parent);
        if (cmp > 0) {
            parent->left = new_node;
        } else {
            parent->right = new_node;
        }
        m_size++;

        // 新添加节点之后的处理
        afterAdd(new_node);
        return value;
    }

    template<typename K, typename V>
    inline V TreeMap<K, V>::get(const K& key) const
    {
        auto node = get_node(key);
        if (node == nullptr) {
            return V();
        }
        return node->value;
    }

    template<typename K, typename V>
    inline bool TreeMap<K, V>::containsKey(const K& key) const
    {
        return get_node(key) != nullptr;
    }

    template<typename K, typename V>
    bool TreeMap<K, V>::containsValue(const V& value) const
    {
        UNUSED(value);
        return true;
    }

    template<typename K, typename V>
    void TreeMap<K, V>::traversal()
    {
        std::cout << "size:" << size() << ", ";
        std::cout << "{ ";
        inOrderTraverse();
        std::cout << "}";
        std::cout << std::endl;
    }

    template<typename K, typename V>
    void TreeMap<K, V>::remove(std::shared_ptr<TMNode> node)
    {
        if (node == nullptr) return;
        m_size--;

        if (node->hasTwoChildren()) {   // 度为2的节点
            // 找到前驱节点或后继节点的值
            auto p = predecessor(node);
            // 将前驱节点或后继节点的值覆盖当前节点
            node->value = p->value;
            // 将前驱节点或后继节点删除
            node = p;
        }

        // 删除node节点，到达此处node的度必然是1或者0
        decltype(node) replacement = node->left != nullptr ? node->left : node->right;
        if (replacement != nullptr) {   // node是度为1的节点
            // 更改parent
            replacement->parent = node->parent;

            // 更改parent的left或right指向
            if (!node->parent.lock()) { // node是度为1的节点，并且是根节点
                root = replacement;
            } else if (node == node->parent.lock()->left) {
                node->parent.lock()->left = replacement;
            } else {    // node == node->parent.lock()->right
                node->parent.lock()->right = replacement;
            }

            // 删除节点之后的处理
            afterRemove(replacement);
        } else if (!node->parent.lock()) {    // node是叶子节点并且是根节点
            root = nullptr;

            // 删除节点之后的处理
            afterRemove(node);
        } else {    // node是叶子节点，但不是根节点
            if (node == node->parent.lock()->left) {
                node->parent.lock()->left = nullptr;
            } else {    // node == node->parent.lock()->righ
                node->parent.lock()->right = nullptr;
            }

            // 删除节点之后的处理
            afterRemove(node);
        }
    }

    template<typename K, typename V>
    void TreeMap<K, V>::inOrderTraverse(std::shared_ptr<TMNode> node)
    {
        if (node == nullptr) return;
        inOrderTraverse(node->left);
        std::cout << node->key << " ";
        inOrderTraverse(node->right);
    }

    template<typename K, typename V>
    std::shared_ptr<typename TreeMap<K, V>::TMNode> TreeMap<K, V>::get_node(const K &key) const
    {
        auto node = root;
        while (node != nullptr)
        {
            int cmp = compare(node->key, key);
            if (cmp == 0) return node;
            if (cmp > 0) {
                node = node->left;
            } else {
                node = node->right;
            }
        }

        return nullptr;
    }

    /**
     * 寻找某个节点的前驱节点
     * @param node
     * @return
     */
    template<typename K, typename V>
    std::shared_ptr<typename TreeMap<K, V>::TMNode> TreeMap<K, V>::predecessor(std::shared_ptr<TMNode> node)
    {
        if (node == nullptr) return node;

        // 前驱节点在左子树当中(left.right.right....)
        auto p = node->left;
        if (p != nullptr) {
            while (p->right != nullptr)
            {
                p = p->right;
            }
            return p;
        }

        // 从父节点、祖父节点中寻找前驱节点
        while (node->parent.lock() && node == node->parent.lock()->left)
        {
            node = node->parent.lock();
        }

        return node->parent.lock();
    }

    /**
     * 添加节点之后的处理
     * @param node 新添加的节点
     */
    template<typename K, typename V>
    void TreeMap<K, V>::afterAdd(std::shared_ptr<TMNode> node)
    {
        auto parent = node->parent.lock();

        // 添加的是根节点
        if (parent == nullptr) {
            make_black(node);
            return;
        }

        // 如果父节点是黑色，直接返回
        if (isBlack(parent)) return;

        // 叔父节点
        auto uncle = parent->sibling();
        // 祖父节点
        auto grand = make_red(parent->parent.lock());
        // 叔父节点是红色（B树节点上溢）
        if (isRed(uncle)) {
            make_black(parent);
            make_black(uncle);
            // 把祖父节点当作新添加的节点
            afterAdd(grand);
            return;
        }

        // 叔父节点不是红色
        if (parent->isLeftChild()) {    // L
            if (node->isLeftChild()) {  // LL
                make_black(parent);
            } else {    // LR
                make_black(node);
                rotateLeft(parent);
            }
            rotateRight(grand);
        } else {    // R
            if (node->isLeftChild()) {  // RL
                make_black(node);
                rotateRight(parent);
            } else {    // RR
                make_black(parent);
            }
            rotateLeft(grand);
        }
    }

    /**
     * 删除node之后的调整
     * @param node 被删除的节点 或者 用以取代被删除节点的子节点
     */
    template<typename K, typename V>
    void TreeMap<K, V>::afterRemove(std::shared_ptr<TMNode> node)
    {
        // 如果删除的节点是红色
        // 或者 用以取代被删除节点的子节点是红色，将用以取代被删除节点的子节点染成黑色
        if (isRed(node)) {
            make_black(node);
            return;
        }

        auto parent = node->parent.lock();
        // 删除的是根节点
        if (parent == nullptr) return;

        // 删除的是黑色叶子节点（下溢 ）
        // 判断被删除的node是左还是右
        bool left = parent->left == nullptr || node->isLeftChild();
        auto sibling = left ? parent->right : parent->left;
        if (left) { // 被删除的节点在左边，兄弟节点在右边
            if (isRed(sibling)) {
                make_black(sibling);
                make_red(parent);
                rotateLeft(parent);
                // 更换兄弟
                sibling = parent->right;
            }

            // 兄弟节点必然是黑色
            if (isBlack(sibling->left) && isBlack(sibling->right)) {
                // 兄弟节点没有一个红色子节点，父节点要向下合并
                bool p_black = isBlack(parent);
                make_black(parent);
                make_red(sibling);
                if (p_black) {  // 如果父节点是黑色，可能导致父节点下溢，将parent当作被删除的节点处理
                    afterRemove(parent);
                }
            } else {    // 兄弟节点至少有一个红色子节点，向兄弟节点借元素（B树特性）
                if (isBlack(sibling->right)) {
                    // 兄弟节点左边是黑色，兄弟要先左旋转
                    rotateRight(sibling);
                    // 旋转之后更换兄弟
                    sibling = parent->right;
                }

                make_color(sibling, colorOf(parent));
                make_black(sibling->right);
                make_black(parent);
                rotateLeft(parent);
            }
        } else {    // 被删除的节点在右边，兄弟节点在左边
            if (isRed(sibling)) {
                make_black(sibling);
                make_red(parent);
                rotateRight(parent);
                // 更换兄弟
                sibling = parent->left;
            }

            // 兄弟节点必然是黑色
            if (isBlack(sibling->left) && isBlack(sibling->right)) {
                // 兄弟节点没有一个红色子节点，父节点要向下合并
                bool p_black = isBlack(parent);
                make_black(parent);
                make_red(sibling);
                if (p_black) {  // 如果父节点是黑色，可能导致父节点下溢，将parent当作被删除的节点处理
                    afterRemove(parent);
                }
            } else {    // 兄弟节点至少有一个红色子节点，向兄弟节点借元素（B树特性）
                if (isBlack(sibling->left)) {
                    // 兄弟节点左边是黑色，兄弟要先左旋转
                    rotateLeft(sibling);
                    // 旋转之后更换兄弟
                    sibling = parent->left;
                }

                make_color(sibling, colorOf(parent));
                make_black(sibling->left);
                make_black(parent);
                rotateRight(parent);
            }
        }
    }

    /**
     * 对节点进行染色
     * @param node
     * @param color
     * @return 返回染色后的节点
     */
    template<typename K, typename V>
    inline std::shared_ptr<typename TreeMap<K, V>::TMNode> TreeMap<K, V>::make_color(std::shared_ptr<TMNode> node, mystd::RBColor color)
    {
        if (node != nullptr)
            node->color = color;
        return node;
    }

    template<typename K, typename V>
    void TreeMap<K, V>::rotateLeft(std::shared_ptr<TMNode> grand)
    {
        auto parent = grand->right;
        auto child = parent->left;
        grand->right = child;
        parent->left = grand;

        // 执行旋转后的操作
        afterRotate(grand, parent, child);
    }

    template<typename K, typename V>
    void TreeMap<K, V>::rotateRight(std::shared_ptr<TMNode> grand)
    {
        auto parent = grand->left;
        auto child = parent->right;
        grand->left = child;
        parent->right = grand;

        // 执行旋转后的操作
        afterRotate(grand, parent, child);
    }

    template<typename K, typename V>
    void TreeMap<K, V>::afterRotate(std::shared_ptr<TMNode> grand,
                                    std::shared_ptr<TMNode> parent,
                                    std::shared_ptr<TMNode> child)
    {
        // 让parent成为子树的根节点
        parent->parent = grand->parent;
        if (grand->isLeftChild()) {
            grand->parent.lock()->left = parent;
        } else if (grand->isRightChild()) {
            grand->parent.lock()->right = parent;
        } else {    // grand是根节点
            root = parent;
        }

        // 更新child的parent
        if (child != nullptr) {
            child->parent = grand;
        }

        // 更新grand的parent
        grand->parent = parent;
    }
}