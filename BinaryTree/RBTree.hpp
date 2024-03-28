//
// Created by wyx on 2024/3/23.
// 红黑树（匹配4阶B树）
//
#pragma once

#include "BBSTree.hpp"

namespace mystd
{
    enum class RBColor : bool
    {
        RED = false,
        BLACK = true
    };

    template<typename T>
    struct RBNode : public TreeNode<T>
    {
        RBColor color = RBColor::RED;    // 默认为红色，这样能够让红黑树的性质尽快满足（性质1，2，3，5都满足，性质4不一定）

        RBNode(const T& val, std::weak_ptr<TreeNode<T>> p) : TreeNode<T>(val, p) {}

        [[nodiscard]] std::string toString() const override
        {
            std::string str = std::to_string(this->value);
            str.append("_p(");
            if (auto p = this->parent.lock()) {
                str.append(std::to_string(p->value));
            } else {
                str.append("null");
            }
            str.push_back(')');

            str.append("_c(");
            std::string color_str = color == RBColor::RED ? "red" : "black";
            str.append(color_str);
            str.push_back(')');
            return str;
        }
    };

    template<typename T>
    class RBTree : public BBSTree<T>
    {
    protected:
        std::shared_ptr<TreeNode<T>> createNode(const T& value, std::shared_ptr<TreeNode<T>> parent) override
        {
            return std::make_shared<RBNode<T>>(value, parent);
        }
    private:
        void afterAdd(std::shared_ptr<TreeNode<T>> node) override;
        void afterRemove(std::shared_ptr<TreeNode<T>> node) override;
        std::shared_ptr<TreeNode<T>> make_color(std::shared_ptr<TreeNode<T>> node, RBColor color);
        std::shared_ptr<TreeNode<T>> make_red(std::shared_ptr<TreeNode<T>> node) { return make_color(node, RBColor::RED); }
        std::shared_ptr<TreeNode<T>> make_black(std::shared_ptr<TreeNode<T>> node) { return make_color(node, RBColor::BLACK); }

        RBColor colorOf(std::shared_ptr<TreeNode<T>> node) const noexcept
        {
            // 空节点为黑色
            return node == nullptr ? RBColor::BLACK : std::dynamic_pointer_cast<RBNode<T>>(node)->color;
        }

        bool isRed(std::shared_ptr<TreeNode<T>> node) const noexcept { return colorOf(node) == RBColor::RED; }
        bool isBlack(std::shared_ptr<TreeNode<T>> node) const noexcept { return colorOf(node) == RBColor::BLACK; }
    };

    /**
     * 添加节点之后的处理
     * @param node 新添加的节点
     */
    template<typename T>
    void RBTree<T>::afterAdd(std::shared_ptr<TreeNode<T>> node)
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
                this->rotateLeft(parent);
            }
            this->rotateRight(grand);
        } else {    // R
            if (node->isLeftChild()) {  // RL
                make_black(node);
                this->rotateRight(parent);
            } else {    // RR
                make_black(parent);
            }
            this->rotateLeft(grand);
        }
    }

    /**
     * 删除node之后的调整
     * @param node 被删除的节点 或者 用以取代被删除节点的子节点
     */
    template<typename T>
    void RBTree<T>::afterRemove(std::shared_ptr<TreeNode<T>> node)
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
                this->rotateLeft(parent);
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
                    this->rotateRight(sibling);
                    // 旋转之后更换兄弟
                    sibling = parent->right;
                }

                make_color(sibling, colorOf(parent));
                make_black(sibling->right);
                make_black(parent);
                this->rotateLeft(parent);
            }
        } else {    // 被删除的节点在右边，兄弟节点在左边
            if (isRed(sibling)) {
                make_black(sibling);
                make_red(parent);
                this->rotateRight(parent);
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
                    this->rotateLeft(sibling);
                    // 旋转之后更换兄弟
                    sibling = parent->left;
                }

                make_color(sibling, colorOf(parent));
                make_black(sibling->left);
                make_black(parent);
                this->rotateRight(parent);
            }
        }
    }

    /**
     * 对节点进行染色
     * @param node
     * @param color
     * @return 返回染色后的节点
     */
    template<typename T>
    inline std::shared_ptr<TreeNode<T>> RBTree<T>::make_color(std::shared_ptr<TreeNode<T>> node, mystd::RBColor color)
    {
        if (node != nullptr)
            std::dynamic_pointer_cast<RBNode<T>>(node)->color = color;
        return node;
    }
}