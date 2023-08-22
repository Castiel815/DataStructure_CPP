//
// Created by CY815 on 2023/8/16.
//

#ifndef DATASTRUCTURE_BINARYSEARCHTREE_H
#define DATASTRUCTURE_BINARYSEARCHTREE_H

#include "bsTree.h"
#include "../binaryTree/linkedBinaryTree.h"

template<typename K, typename E>
class binarySearchTree : public bsTree<K, E>,
                         public linkedBinaryTree<std::pair<const K, E>> {
public:
    bool empty() const override { return this->treeSize == 0; }

    int size() const override { return this->treeSize; }

    std::pair<const K, E> *find(const K &theKey) const override;

    void insert(const std::pair<const K, E> &thePair) override;

    void erase(const K &theKey) override;

    void ascend() override { this->inOrderOutput(); }

    friend std::ostream &operator<<(std::ostream &out, const std::pair<const K, E> &x) {
        out << x.first << ' ' << x.second;
        return out;
    }
};

/**
 * 返回值是匹配数对的指针，如果没有匹配的数对，返回值为NULL
 * @tparam K
 * @tparam E
 * @param theKey
 * @return
 */
template<typename K, typename E>
std::pair<const K, E> *binarySearchTree<K, E>::find(const K &theKey) const {
    // P从根节点开始搜索，寻找关键字等于theKey的一个元素
    binaryTreeNode<std::pair<const K, E>> *p = this->root;
    while (p != nullptr) {
        // 检查元素p->element
        if (theKey < p->element.first)
            p = p->leftChild;
        else {
            if (theKey > p->element.first)
                p = p->rightChild;
            else                        // 找到匹配的元素
                return &p->element;
        }
    }

    return nullptr;
}

/**
 * 插入thePair，如果存在与其关键字相同的数对，则覆盖
 * @tparam K
 * @tparam E
 * @param thePair
 */
template<typename K, typename E>
void binarySearchTree<K, E>::insert(const std::pair<const K, E> &thePair) {
    // 寻找插入位置
    binaryTreeNode<std::pair<const K, E>> *p = this->root, *pp = nullptr;
    while (p != nullptr) {  // 检查元素p->element
        pp = p;
        // p移到它的一个孩子节点
        if (thePair.first < p->element.first) {
            p = p->leftChild;
        } else {
            if (thePair.first > p->element.first) {
                p = p->rightChild;
            } else {                // 覆盖旧的值
                p->element.second = thePair.second;
                return;
            }
        }
    }

    // 为thePair建立一个节点，然后与pp链接
    binaryTreeNode<std::pair<const K, E>> *newNode = new binaryTreeNode<std::pair<const K, E>>(thePair);
    if (this->root != nullptr) {
        if (thePair.first < pp->element.first) {
            pp->leftChild = newNode;
        } else {
            pp->rightChild = newNode;
        }
    } else {
        this->root = newNode;
    }
    this->treeSize++;
}

/**
 * 删除其关键字等于theKey的数对
 * @tparam K
 * @tparam E
 * @param theKey
 */
template<typename K, typename E>
void binarySearchTree<K, E>::erase(const K &theKey) {
    // 查找关键字为theKey的节点
    binaryTreeNode<std::pair<const K, E>> *p = this->root, *pp = nullptr;
    while (p != nullptr && p->element.first != theKey) {    // p移到它的一个孩子节点
        pp = p;
        if (theKey < p->element.first) {
            p = p->leftChild;
        } else {
            p = p->rightChild;
        }
    }
    if (p == nullptr) {
        return;     // 不存在与关键字theKey匹配的数对
    }

    // 重新组织树结构
    // 当P有两个孩子时的处理
    if (p->leftChild != nullptr && p->rightChild != nullptr) {  // 两个孩子
        // 转化为空或只有一个孩子
        // 在p的左子树中寻找最大元素
        binaryTreeNode<std::pair<const K, E>> *s = p->leftChild, *ps = p;   // s的双亲
        while (s->rightChild != nullptr) {  // 移到最大的元素
            ps = s;
            s = s->rightChild;
        }

        // 将最大元素s移到p，但不是简单的移动
        binaryTreeNode<std::pair<const K, E>> *q = new binaryTreeNode<std::pair<const K, E>>(s->element, p->leftChild,
                                                                                             p->rightChild);
        if (pp == nullptr) {
            this->root = q;
        } else {
            if (p == pp->leftChild) {
                pp->leftChild = q;
            } else {
                pp->rightChild = q;
            }
        }
        if (ps == p) {
            pp = q;
        } else {
            pp = ps;
        }
        delete p;
        p = s;
    }

    // p最多有一个孩子
    // 把孩子指针存放在c
    binaryTreeNode<std::pair<const K, E>> *c;
    if (p->leftChild != nullptr) {
        c = p->leftChild;
    } else {
        c = p->rightChild;
    }

    // 删除p
    if (p == this->root) {
        this->root = c;
    } else {    // p是pp的左孩子还是右孩子？
        if (p == pp->leftChild) {
            pp->leftChild = c;
        } else {
            pp->rightChild = c;
        }
    }
    this->treeSize--;
    delete p;
}

#endif //DATASTRUCTURE_BINARYSEARCHTREE_H
