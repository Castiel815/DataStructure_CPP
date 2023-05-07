//
// Created by CY815 on 2023/5/7.
//

#ifndef DATASTRUCTURE_CHAINNODE_H
#define DATASTRUCTURE_CHAINNODE_H

/**
 * 链表节点的结构定义
 * @tparam T
 */
template<typename T>
struct chainNode {
    // 数据成员
    T element;
    chainNode<T> *next;

    // 方法
    chainNode() = default;

    explicit chainNode(const T &element) {
        this->element = element;
    }

    chainNode(const T &element, chainNode<T> *next) {
        this->element = element;
        this->next = next;
    }
};

#endif //DATASTRUCTURE_CHAINNODE_H
