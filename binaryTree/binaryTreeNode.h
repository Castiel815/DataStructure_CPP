//
// Created by CY815 on 2023/7/31.
//

#ifndef DATASTRUCTURE_BINARYTREENODE_H
#define DATASTRUCTURE_BINARYTREENODE_H

template<typename T>
struct binaryTreeNode {
    T element;
    binaryTreeNode<T> *leftChild,   // 左子树
    *rightChild;                // 右子树

    binaryTreeNode() { leftChild = rightChild = nullptr; }

    explicit binaryTreeNode(const T &theElement) : element(theElement) {
        leftChild = rightChild = nullptr;
    }

    binaryTreeNode(const T &theElement, binaryTreeNode *theLeftChild, binaryTreeNode *theRightChild) : element(
            theElement) {
        leftChild = theLeftChild;
        rightChild = theRightChild;
    }
};

#endif //DATASTRUCTURE_BINARYTREENODE_H
