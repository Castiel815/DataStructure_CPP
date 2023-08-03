//
// Created by CY815 on 2023/7/31.
//

#ifndef DATASTRUCTURE_LINKEDBINARYTREE_H
#define DATASTRUCTURE_LINKEDBINARYTREE_H

#include <iostream>
#include "binaryTree.h"
#include "../queue/arrayQueue.h"
#include "binaryTreeNode.h"
#include "myExceptions.h"
#include "booster.h"
#include <stdexcept>

template<typename E>
class linkedBinaryTree : public binaryTree<binaryTreeNode<E>> {
public:
    linkedBinaryTree() {
        root = nullptr;
        treeSize = 0;
    }

    ~linkedBinaryTree() override { erase(); }

    bool empty() const override { return treeSize == 0; }

    int size() const override { return treeSize; }

    E *rootElement() const;

    void makeTree(const E &element, linkedBinaryTree<E> &left, linkedBinaryTree<E> &right);

    linkedBinaryTree<E> &removeLeftSubtree();

    linkedBinaryTree<E> &removeRightSubtree();

    void preOrder(void(*theVisit)(binaryTreeNode<E> *)) override {
        visit = theVisit;
        preOrder(root);
    }

    void inOrder(void(*theVisit)(binaryTreeNode<E> *)) override {
        visit = theVisit;
        inOrder(root);
    }

    void postOrder(void(*theVisit)(binaryTreeNode<E> *)) override {
        visit = theVisit;
        postOrder(root);
    }

    void levelOrder(void(*theVisit)(binaryTreeNode<E> *)) override;

    void preOrderOutput() {
        preOrder(output);
        std::cout << std::endl;
    }

    void inOrderOutput() {
        inOrder(output);
        std::cout << std::endl;
    }

    void postOrderOutput() {
        postOrder(output);
        std::cout << std::endl;
    }

    void levelOrderOutput() {
        levelOrder(output);
        std::cout << std::endl;
    }

    void erase() {
        postOrder(dispose);
        root = nullptr;
        treeSize = 0;
    }

    int height() const { return height(root); }

protected:
    binaryTreeNode<E> *root;                        // 指向根的指针
    int treeSize;                                   // 树的节点个数

    static void (*visit)(binaryTreeNode<E> *);      // 访问函数

    static int count;

    static void preOrder(binaryTreeNode<E> *t);

    static void inOrder(binaryTreeNode<E> *t);

    static void postOrder(binaryTreeNode<E> *t);

    static void countNodes(binaryTreeNode<E> *t) {
        visit = addToCount;
        count = 0;
        preOrder(t);
    }

    static void dispose(binaryTreeNode<E> *t) { delete t; }

    static void output(binaryTreeNode<E> *t) { std::cout << t->element << ' '; }

    static void addToCount(binaryTreeNode<E> *t) {
        count++;
    }

    static int height(binaryTreeNode<E> *t);
};

template<>
void (*linkedBinaryTree<int>::visit)(binaryTreeNode<int> *) = nullptr;

template<>
void (*linkedBinaryTree<booster>::visit)(binaryTreeNode<booster> *) = nullptr;

template<>
void (*linkedBinaryTree<std::pair<int, int> >::visit)(binaryTreeNode<std::pair<int, int> > *) = nullptr;

template<>
void (*linkedBinaryTree<std::pair<const int, char> >::visit)(binaryTreeNode<std::pair<const int, char> > *) = nullptr;

template<>
void (*linkedBinaryTree<std::pair<const int, int> >::visit)(binaryTreeNode<std::pair<const int, int> > *) = nullptr;

template<typename E>
E *linkedBinaryTree<E>::rootElement() const {
    if (treeSize == 0) {
        return nullptr;
    } else {
        return &root->element;
    }
}

template<typename E>
void linkedBinaryTree<E>::makeTree(const E &element, linkedBinaryTree<E> &left, linkedBinaryTree<E> &right) {
    root = new binaryTreeNode<E>(element, left.root, right.root);
    treeSize = left.treeSize + right.treeSize + 1;

    left.root = right.root = nullptr;
    left.treeSize = right.treeSize = 0;
}

template<typename E>
linkedBinaryTree<E> &linkedBinaryTree<E>::removeLeftSubtree() {
    if (treeSize == 0) {
        throw std::exception();
    }

    linkedBinaryTree<E> leftSubtree;
    leftSubtree.root = root->leftChild;
    count = 0;
    leftSubtree.treeSize = countNodes(leftSubtree.root);
    root->leftChild = nullptr;
    treeSize -= leftSubtree.treeSize;

    return leftSubtree;
}

template<typename E>
linkedBinaryTree<E> &linkedBinaryTree<E>::removeRightSubtree() {
    if (treeSize == 0) {
        throw std::exception();
    }

    linkedBinaryTree<E> rightSubtree;
    rightSubtree.root = root->rightChild;
    count = 0;
    rightSubtree.treeSize = countNodes(rightSubtree.root);
    root->rightChild = nullptr;
    treeSize -= rightSubtree.treeSize;

    return rightSubtree;
}

/**
 * 前序遍历
 * @tparam E
 * @param t
 */
template<typename E>
void linkedBinaryTree<E>::preOrder(binaryTreeNode<E> *t) {
    if (t != nullptr) {
        linkedBinaryTree<E>::visit(t);
        preOrder(t->leftChild);
        preOrder(t->rightChild);
    }
}

template<typename E>
void linkedBinaryTree<E>::inOrder(binaryTreeNode<E> *t) {
    if (t != nullptr) {
        inOrder(t->leftChild);
        linkedBinaryTree<E>::visit(t);
        inOrder(t->rightChild);
    }
}

template<typename E>
void linkedBinaryTree<E>::postOrder(binaryTreeNode<E> *t) {
    if (t != nullptr) {
        postOrder(t->leftChild);
        postOrder(t->rightChild);
        linkedBinaryTree<E>::visit(t);
    }
}

template<typename E>
void linkedBinaryTree<E>::levelOrder(void (*theVisit)(binaryTreeNode<E> *)) {
    arrayQueue<binaryTreeNode<E> *> q;
    binaryTreeNode<E> *t = root;
    while (t != nullptr) {
        theVisit(t);

        if (t->leftChild != nullptr) {
            q.push(t->leftChild);
        }
        if (t->rightChild != nullptr) {
            q.push(t->rightChild);
        }

        try {
            t = q.front();
        } catch (queueEmpty) {
            return;
        }
        q.pop();
    }
}

/**
 * 返回根为*t的树的高度
 * @tparam E
 * @param t
 * @return
 */
template<typename E>
int linkedBinaryTree<E>::height(binaryTreeNode<E> *t) {
    if (t == nullptr) {
        return 0;
    }
    int hl = height(t->leftChild);
    int hr = height(t->rightChild);
    if (hl > hr) {
        return ++hl;
    } else {
        return ++hr;
    }
}

#endif //DATASTRUCTURE_LINKEDBINARYTREE_H
