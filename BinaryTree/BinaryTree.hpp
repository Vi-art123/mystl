//
// Created by wyx on 2024/3/21.
// 二叉树基类
//
#pragma once

#include <iostream>
#include <queue>
#include <memory>

namespace mystd
{
    template<typename T>
    struct TreeNode
    {
        T value;
        std::weak_ptr<TreeNode> parent;
        std::shared_ptr<TreeNode> left;
        std::shared_ptr<TreeNode> right;
        TreeNode() = default;
        TreeNode(const TreeNode& node) = default;
        TreeNode(TreeNode&& node) = default;
        TreeNode(const T& val, std::weak_ptr<TreeNode> p) : value(val), parent(p) {}
//        virtual ~TreeNode() { std::cout << "delete TreeNode: " << value << std::endl; }
        virtual ~TreeNode() = default;

        /**
         * 节点转换为字符串
         * @return 
         */    
        [[nodiscard]] virtual std::string toString() const
        {
            std::string str = std::to_string(value);
            str.append("_p(");
            if (auto p = parent.lock()) {
                str.append(std::to_string(p->value));
            } else {
                str.append("null");
            }
            str.push_back(')');

            return str;
        }

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
        std::shared_ptr<TreeNode> sibling() const noexcept
        {
            if (!parent.lock()) {
                return nullptr;
            }
            return isLeftChild() ? parent.lock()->right : parent.lock()->left;
        }
    };


    template<typename T>
    class BinaryTree
    {
    public:
        BinaryTree() = default;
        BinaryTree(const BinaryTree& bt) = default;
        BinaryTree(BinaryTree&& bt) = default;
        virtual ~BinaryTree() = default;
         
        void clear() noexcept;
        void preOrderTraverse();
        void inOrderTraverse();
        void postOrderTraverse();
        void levelOrderTraverse();
        void invertTree();
        void to_string() const;
        [[nodiscard]] bool isComplete() const;
        [[nodiscard]] int height() const;
        [[nodiscard]] int height2() const { return height2(root); };
        [[nodiscard]] int size() const noexcept { return m_size; }
        [[nodiscard]] bool isEmpty() const noexcept { return m_size == 0; }
    protected:
        std::shared_ptr<TreeNode<T>> predecessor(std::shared_ptr<TreeNode<T>> node);
        std::shared_ptr<TreeNode<T>> successor(std::shared_ptr<TreeNode<T>> node);
        virtual std::shared_ptr<TreeNode<T>> createNode(const T& value, std::shared_ptr<TreeNode<T>> parent);
    private:
        int height2(std::shared_ptr<TreeNode<T>> node) const;
        virtual void preOrderTraverse(std::shared_ptr<TreeNode<T>> node);
        virtual void inOrderTraverse(std::shared_ptr<TreeNode<T>> node);
        virtual void postOrderTraverse(std::shared_ptr<TreeNode<T>> node);
    protected:
        int m_size = 0;
        std::shared_ptr<TreeNode<T>> root;
    };

    template<typename T>
    inline void BinaryTree<T>::clear() noexcept
    {
        root = nullptr; // 自动释放内存
        m_size = 0;
    }

    /**
     * 创建节点，派生类重写此方法来创建自己的节点
     * @return 
     */    
    template<typename T>
    inline std::shared_ptr<TreeNode<T>> BinaryTree<T>::createNode(const T& value, std::shared_ptr<TreeNode<T>> parent)
    {
        return std::make_shared<TreeNode<T>>(value, parent);
    }

    /**
     * 前序遍历
     */
    template<typename T>
    inline void BinaryTree<T>::preOrderTraverse()
    {
        if (root == nullptr) return;
        preOrderTraverse(root);
    }

    template<typename T>
    void BinaryTree<T>::preOrderTraverse(std::shared_ptr<TreeNode<T>> node)
    {
        if (node == nullptr) return;
        std::cout << node->value << " ";
        preOrderTraverse(node->left);
        preOrderTraverse(node->right);
    }

    /**
     * 中序遍历
     */
    template<typename T>
    inline void BinaryTree<T>::inOrderTraverse()
    {
        if (root == nullptr) return;
        inOrderTraverse(root);
    }

    template<typename T>
    void BinaryTree<T>::inOrderTraverse(std::shared_ptr<TreeNode<T>> node)
    {
        if (node == nullptr) return;
        inOrderTraverse(node->left);
        std::cout << node->value << " ";
        inOrderTraverse(node->right);
    }

    /**
     * 后序遍历
     */
    template<typename T>
    inline void BinaryTree<T>::postOrderTraverse()
    {
        if (root == nullptr) return;
        postOrderTraverse(root);
    }

    template<typename T>
    void BinaryTree<T>::postOrderTraverse(std::shared_ptr<TreeNode<T>> node)
    {
        if (node == nullptr) return;
        postOrderTraverse(node->left);
        postOrderTraverse(node->right);
        std::cout << node->value << " ";
    }

    /**
     * 层序遍历
     */
    template<typename T>
    void BinaryTree<T>::levelOrderTraverse()
    {
        if (root == nullptr) return;
        std::queue<decltype(root)> qp;
        qp.push(root);
        while (!qp.empty())
        {
            auto node = qp.front();
            qp.pop();
            std::cout << node->value << " ";
            if (node->left != nullptr) {
                qp.push(node->left);
            }

            if (node->right != nullptr) {
                qp.push(node->right);
            }
        }
    }

    /**
     * 翻转二叉树，把所有节点的左右子树交换（可以使用前序，后续，中序，层序遍历实现）
     */    
    template<typename T>
    void BinaryTree<T>::invertTree()
    {
        if (root == nullptr) return;
        std::queue<decltype(root)> qp;
        qp.push(root);
        while (!qp.empty())
        {
            auto node = qp.front();
            qp.pop();

            auto tmpNode = node->left;
            node->left = node->right;
            node->right = tmpNode;

            if (node->left != nullptr) {
                qp.push(node->left);
            }

            if (node->right != nullptr) {
                qp.push(node->right);
            }
        }
    }

    /**
     * 获取树的高度（层序遍历方式）
     * @return 
     */    
    template<typename T>
    int BinaryTree<T>::height() const
    {
        if (root == nullptr) return 0;
        int height_ = 0;   // 树的高度
        int levelRowSize = 1;  // 每一层的元素个数
        std::queue<decltype(root)> qp;
        qp.push(root);
        while (!qp.empty())
        {
            auto node = qp.front();
            qp.pop();
            levelRowSize--;

            if (node->left != nullptr) {
                qp.push(node->left);
            }

            if (node->right != nullptr) {
                qp.push(node->right);
            }

            if (levelRowSize == 0) {    // 意味着即将进入下一层
                levelRowSize = qp.size();
                height_++;
            }
        }
        return height_;
    }

    /**
     * 获取树的高度（递归方式）
     * @param node
     * @return 
     */    
    template<typename T>
    int BinaryTree<T>::height2(std::shared_ptr<TreeNode<T>> node) const
    {
        if (node == nullptr) return 0;
        return 1 + std::max(height2(node->left), height2(node->right));
    }

    /**
     * 判断是否为完全二叉树
     * @return 
     */    
    template<typename T>
    bool BinaryTree<T>::isComplete() const
    {
        if (root == nullptr) return false;
        
        std::queue<decltype(root)> qp;
        qp.push(root);

        bool leaf = false;
        while (!qp.empty())
        {
            auto node = qp.front();
            qp.pop();

            if (leaf && !node->isLeaf())
                return false;

            if (node->left != nullptr) {
                qp.push(node->left);
            } else if (node->right != nullptr) {
                // 左边为空，但是右边不为空
                return false;
            }

            if (node->right != nullptr) {
                qp.push(node->right);
            } else {
                // 只要右边为空，后面的节点都必须是叶子节点才是完全二叉树
                leaf = true;
            }
        }

        return true;
    }

    /**
     * 寻找某个节点的前驱节点
     * @param node
     * @return
     */
    template<typename T>
    std::shared_ptr<TreeNode<T>> BinaryTree<T>::predecessor(std::shared_ptr<TreeNode<T>> node)
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
     * 寻找某个节点的后继节点
     * @param node
     * @return
     */
    template<typename T>
    std::shared_ptr<TreeNode<T>> BinaryTree<T>::successor(std::shared_ptr<TreeNode<T>> node)
    {
        if (node == nullptr) return node;

        // 后继节点在左子树当中(right.left.left....)
        auto p = node->right;
        if (p != nullptr) {
            while (p->left != nullptr)
            {
                p = p->left;
            }

            return p;
        }

        // 从父节点、祖父节点中寻找后继节点
        while (node->parent.lock() && node == node->parent.lock()->right)
        {
            node = node->parent.lock();
        }

        return node->parent.lock();
    }

    /**
     * 打印二叉树
     */    
    template<typename T>
    void BinaryTree<T>::to_string() const
    {
        if (root == nullptr) return;

        int levelRowSize = 1;  // 每一层的元素个数
        std::queue<decltype(root)> qp;
        qp.push(root);
        while (!qp.empty())
        {
            auto node = qp.front();
            qp.pop();

            levelRowSize--;
            
            std::cout << node->toString() << " ";

            if (node->left != nullptr) {
                qp.push(node->left);
            }

            if (node->right != nullptr) {
                qp.push(node->right);
            }

            if (levelRowSize == 0) {    // 意味着即将进入下一层
                std::cout << std::endl;
                levelRowSize = qp.size();
            }
        }
    }
} // mystd
