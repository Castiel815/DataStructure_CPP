//
// Created by CY815 on 2023/8/7.
//

#ifndef DATASTRUCTURE_MAXHBLT_H
#define DATASTRUCTURE_MAXHBLT_H

#include "maxPriorityQueue.h"
#include "../binaryTree/linkedBinaryTree.h"
#include "../binaryTree/binaryTreeNode.h"
#include "myExceptions.h"
#include <sstream>

template<typename T>
class maxHblt : public maxPriorityQueue<T>, public linkedBinaryTree<std::pair<int, T>> {
public:
    bool empty() const override { return linkedBinaryTree<std::pair<int, T>>::treeSize == 0; }

    int size() const override { return linkedBinaryTree<std::pair<int, T>>::treeSize; }

    const T &top() override {
        if (linkedBinaryTree<std::pair<int, T>>::treeSize == 0) {
            throw queueEmpty();
        }
        return linkedBinaryTree<std::pair<int, T>>::root->element.second;
    }

    void pop() override;

    void push(const T &) override;

    void initialize(T *theElements, int theSize);

    /**
     * 把左高树*this和theHblt合并
     * @param theHblt
     */
    void meld(maxHblt<T> &theHblt) {
        meld(linkedBinaryTree<std::pair<int, T>>::root, theHblt.root);
        linkedBinaryTree<std::pair<int, T>>::treeSize += theHblt.treeSize;
        theHblt.root = nullptr;
        theHblt.treeSize = 0;
    }

    void output() {
        linkedBinaryTree<std::pair<int, T>>::postOrder(hbltOutput);
        std::cout << std::endl;
    }

private:
    void meld(binaryTreeNode<std::pair<int, T>> *&x, binaryTreeNode<std::pair<int, T>> *&y);

    static void hbltOutput(binaryTreeNode<std::pair<int, T>> *t) {
        std::cout << t->element.second << ' ';
    }
};

/**
 * 合并分别以*x和*y为根的两棵左高树，合并后的左高树以x为根，返回x的指针
 * @tparam T
 * @param x
 * @param y
 */
template<typename T>
void maxHblt<T>::meld(binaryTreeNode<std::pair<int, T>> *&x, binaryTreeNode<std::pair<int, T>> *&y) {
    if (y == nullptr) {         // y为空
        return;
    }
    if (x == nullptr) {         // x为空
        x = y;
        return;
    }

    // x和y都不空，必要时交换x和y
    if (x->element.second < y->element.second) {
        swap(x, y);
    }

    meld(x->rightChild, y);

    // 如果需要，交换x的子树，然后设置x->element.first的值
    if (x->leftChild == nullptr) {      // 左子树为空，交换子树
        x->leftChild = x->rightChild;
        x->rightChild = nullptr;
        x->element.first = 1;
    } else {    // 只有左子树的s值较小时才交换
        if (x->leftChild->element.first < x->rightChild->element.first) {
            swap(x->leftChild, x->rightChild);
        }
        // 更新x的s值
        x->element.first = x->rightChild->element.first + 1;
    }
}

/**
 * 把元素theElement插入左高树，建立只有一个节点的左高树
 * @tparam T
 * @param theElement
 */
template<typename T>
void maxHblt<T>::push(const T &theElement) {
    auto *q = new binaryTreeNode<std::pair<int, T>>(std::pair<int, T>(1, theElement));

    // 将左高树q和原树合并
    meld(linkedBinaryTree<std::pair<int, T>>::root, q);
    linkedBinaryTree<std::pair<int, T>>::treeSize++;
}

/**
 * 删除最大元素
 * @tparam T
 */
template<typename T>
void maxHblt<T>::pop() {
    if (linkedBinaryTree<std::pair<int, T>>::root == nullptr) {
        throw queueEmpty();
    }

    // 树不空
    binaryTreeNode<std::pair<int, T>> *left = linkedBinaryTree<std::pair<int, T>>::root->leftChild,
            *right = linkedBinaryTree<std::pair<int, T>>::root->rightChild;
    delete linkedBinaryTree<std::pair<int, T>>::root;
    linkedBinaryTree<std::pair<int, T>>::root = left;
    meld(linkedBinaryTree<std::pair<int, T>>::root, right);
    linkedBinaryTree<std::pair<int, T>>::treeSize--;
}

/**
 * 用数组theElements[1: theSize]建立左高树
 * @tparam T
 * @param theElements
 * @param theSize
 */
template<typename T>
void maxHblt<T>::initialize(T *theElements, int theSize) {
    arrayQueue<binaryTreeNode<std::pair<int, T>> *> q(theSize);
    linkedBinaryTree<std::pair<int, T>>::erase();       // 使*this为空

    // 初始化树的队列
    for (int i = 1; i <= theSize; ++i) {
        // 建立只有一个节点的树
        q.push(new binaryTreeNode<std::pair<int, T>>(std::pair<int, T>(1, theElements[i])));
    }

    // 从队列中重复取出两棵树合并
    for (int i = 1; i <= theSize - 1; ++i) {
        // 从队列中删除两棵树合并
        binaryTreeNode<std::pair<int, T>> *b = q.front();
        q.pop();
        binaryTreeNode<std::pair<int, T>> *c = q.front();
        q.pop();
        meld(b, c);
        // 把合并后的树插入队列
        q.push(b);
    }

    if (theSize > 0) {
        linkedBinaryTree<std::pair<int, T>>::root = q.front();
    }
    linkedBinaryTree<std::pair<int, T>>::treeSize = theSize;
}

#endif //DATASTRUCTURE_MAXHBLT_H
