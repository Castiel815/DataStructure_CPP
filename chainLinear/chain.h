//
// Created by CY815 on 2023/5/7.
//

#ifndef DATASTRUCTURE_CHAIN_H
#define DATASTRUCTURE_CHAIN_H

#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>
#include "linearList.h"
#include "chainNode.h"


class linkedDigraph;

template<typename T>
class linkedWDigraph;

/**
 * 用单向链表实现线性表
 * @tparam T
 */
template<typename T>
class chain : public linearList<T> {
    friend linkedDigraph;
    friend linkedWDigraph<int>;
    friend linkedWDigraph<float>;
    friend linkedWDigraph<double>;

public:
    // 构造函数、复制构造函数和析构函数
    chain(int initialCapacity = 10);

    chain(const chain<T> &theList);

    ~chain() override;

    // ADT methods
    bool empty() const override { return listSize == 0; }

    int size() const override { return listSize; }

    T &get(int theIndex) const override;

    int indexOf(const T &theElement) const override;

    void erase(int theIndex) override;

    void insert(int theIndex, const T &theElement) override;

    void output(std::ostream &out) const override;

    class iterator;

    iterator begin() { return iterator(firstNode); }

    iterator end() { return iterator(nullptr); }

    class iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = ptrdiff_t;
        using pointer = T *;
        using reference = T &;

        // 构造函数
        explicit iterator(chainNode<T> *theNode = nullptr) {
            node = theNode;
        }

        // 解引用操作符
        T &operator*() const { return node->element; }

        T *operator->() const { return &node->element; }

        // 迭代器加法操作
        iterator &operator++() {    // 前加
            node = node->next;
            return *this;
        }

        iterator operator++(int) {  // 后加
            iterator old = *this;
            node = node->next;
            return old;
        }

        // 相等检验
        bool operator!=(const iterator right) const {
            return node != right.node;
        }

        bool operator==(const iterator right) const {
            return node == right.node;
        }

    protected:
        chainNode<T> *node;
    };

protected:
    // 如果索引无效，抛出异常
    void checkIndex(int theIndex) const;

    chainNode<T> *firstNode;    // 指向链表第一个节点的指针
    int listSize;               // 线性表的元素个数
};

/**
 * 构造函数
 * @tparam T
 * @param initialCapacity
 */
template<typename T>
chain<T>::chain(int initialCapacity) {
    if (initialCapacity < 1) {
        std::ostringstream s;
        s << "Initial capacity = " << initialCapacity << " Must be > 0";
        throw std::invalid_argument(s.str());
    }

    firstNode = nullptr;
    listSize = 0;
}

/**
 * 复制构造函数
 * @tparam T
 * @param theList
 */
template<typename T>
chain<T>::chain(const chain<T> &theList) {
    listSize = theList.listSize;

    // theList为空时
    if (listSize == 0) {
        firstNode = nullptr;
        return;
    }

    // 非空
    chainNode<T> *sourceNode = theList.firstNode;   // 要复制链表theList的节点
    firstNode = new chainNode<T>(sourceNode->element);  // 复制链表theList的首元素
    sourceNode = sourceNode->next;
    chainNode<T> *targetNode = firstNode;   // 当前链表*this的最后一个节点

    // 复制剩余元素
    while (sourceNode != nullptr) {
        targetNode->next = new chainNode<T>(sourceNode->element);
        targetNode = targetNode->next;
        sourceNode = sourceNode->next;
    }

    // 链表结束
    targetNode->next = nullptr;
}

/**
 * 链表析构函数，删除链表的所有节点
 * @tparam T
 */
template<typename T>
chain<T>::~chain() {
    // 删除首节点
    while (firstNode != nullptr) {
        chainNode<T> *nextNode = firstNode->next;
        delete firstNode;
        firstNode = nextNode;
    }
}

template<typename T>
void chain<T>::checkIndex(int theIndex) const {
    if (theIndex < 0 || theIndex >= listSize) {
        std::ostringstream s;
        s << "index = " << theIndex << " size = " << listSize;
        throw std::invalid_argument(s.str());
    }
}

/**
 * 返回索引为theIndex的元素，若该元素不存在，则抛出异常
 * @tparam T
 * @param theIndex
 * @return
 */
template<typename T>
T &chain<T>::get(int theIndex) const {
    checkIndex(theIndex);

    // 移向所需要的节点
    chainNode<T> *currentNode = firstNode;
    for (int i = 0; i < theIndex; ++i) {
        currentNode = currentNode->next;
    }

    return currentNode->element;
}

/**
 * 返回元素theElement首次出现时的索引，若该元素不存在，则返回-1
 * @tparam T
 * @param theElement
 * @return
 */
template<typename T>
int chain<T>::indexOf(const T &theElement) const {

    // 搜索链表寻找元素theElement
    chainNode<T> *currentNode = firstNode;
    int index = 0;      // 当前节点的索引
    while (currentNode != nullptr && currentNode->element != theElement) {
        // 移向下一个节点
        currentNode = currentNode->next;
        index++;
    }

    // 确定是否找到所需的元素
    if (currentNode == nullptr) {
        return -1;
    } else {
        return index;
    }
}

/**
 * 删除索引为theIndex的元素。若该元素不存在，则抛出异常
 * @tparam T
 * @param theIndex
 */
template<typename T>
void chain<T>::erase(int theIndex) {
    checkIndex(theIndex);

    // 索引有效，需找要删除的元素节点
    chainNode<T> *deleteNode;
    if (theIndex == 0) {    // 删除链表的首节点
        deleteNode = firstNode;
        firstNode = firstNode->next;
    } else {
        // 用指针p指向要删除节点的前驱节点
        chainNode<T> *p = firstNode;
        for (int i = 0; i < theIndex; ++i) {
            p = p->next;
        }

        deleteNode = p->next;
        p->next = p->next->next;
    }

    listSize--;
    delete deleteNode;      // 删除deleteNode指向的节点
}

/**
 * 在索引为theIndex的位置上插入元素theElement
 * @tparam T
 * @param theIndex
 * @param theElement
 */
template<typename T>
void chain<T>::insert(int theIndex, const T &theElement) {
    if (theIndex < 0 || theIndex > listSize) {  // 无效索引
        std::ostringstream s;
        s << "index = " << theIndex << " size = " << listSize;
        throw std::invalid_argument(s.str());
    }

    if (theIndex == 0) {
        // 在链表头插入
        firstNode = new chainNode<T>(theElement, firstNode);
    } else {
        // 寻找新元素的前驱
        chainNode<T> *p = firstNode;
        for (int i = 0; i < theIndex - 1; ++i) {
            p = p->next;
        }

        p->next = new chainNode<T>(theElement, p->next);
    }
    listSize++;
}

/**
 * 输出链表，把链表放入输出流
 * @tparam T
 * @param out
 */
template<typename T>
void chain<T>::output(std::ostream &out) const {
    for (chainNode<T> *currentNode = firstNode; currentNode != nullptr; currentNode = currentNode->next) {
        out << currentNode->element << " ";
    }
}

/**
 * 重载<<
 * @tparam T
 * @param out
 * @param x
 * @return
 */
template<typename T>
std::ostream &operator<<(std::ostream &out, const chain<T> &x) {
    x.output(out);
    return out;
}

#endif //DATASTRUCTURE_CHAIN_H
