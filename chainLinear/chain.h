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

protected:
    void checkIndex(int theIndex) const;

    chainNode<T> *firstNode;
    int listSize;
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
    chainNode<T> *sourceNode = theList.firstNode;
    firstNode = new chainNode<T>(sourceNode->element);
    sourceNode = sourceNode->next;
    chainNode<T> *targetNode = firstNode;

    while (sourceNode != nullptr) {
        targetNode->next = new chainNode<T>(sourceNode->element);
        targetNode = targetNode->next;
        sourceNode = sourceNode->next;
    }

    targetNode->next = nullptr;
}

template<typename T>
chain<T>::~chain() {
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

template<typename T>
T &chain<T>::get(int theIndex) const {
    checkIndex(theIndex);

    chainNode<T> *currentNode = firstNode;
    for (int i = 0; i < theIndex; ++i) {
        currentNode = currentNode->next;
    }

    return currentNode->element;
}

template<typename T>
int chain<T>::indexOf(const T &theElement) const {
    chainNode<T> *currentNode = firstNode;
    int index = 0;
    while (currentNode != nullptr && currentNode->element != theElement) {
        currentNode = currentNode->next;
        index++;
    }

    if (currentNode == nullptr) {
        return -1;
    } else {
        return index;
    }
}

template<typename T>
void chain<T>::erase(int theIndex) {
    checkIndex(theIndex);

    chainNode<T> *deleteNode;
    if (theIndex == 0) {
        deleteNode = firstNode;
        firstNode = firstNode->next;
    } else {
        chainNode<T> *p = firstNode;
        for (int i = 0; i < theIndex; ++i) {
            p = p->next;
        }

        deleteNode = p->next;
        p->next = p->next->next;
    }

    listSize--;
    delete deleteNode;
}

template<typename T>
void chain<T>::insert(int theIndex, const T &theElement) {
    if (theIndex < 0 || theIndex > listSize) {
        std::ostringstream s;
        s << "index = " << theIndex << " size = " << listSize;
        throw std::invalid_argument(s.str());
    }

    if (theIndex == 0) {
        firstNode = new chainNode<T>(theElement, firstNode);
    } else {
        chainNode<T> *p = firstNode;
        for (int i = 0; i < theIndex - 1; ++i) {
            p = p->next;
        }

        p->next = new chainNode<T>(theElement, p->next);
    }
    listSize++;
}

template<typename T>
void chain<T>::output(std::ostream &out) const {
    for (chainNode<T> *currentNode = firstNode; currentNode != nullptr; currentNode = currentNode->next) {
        out << currentNode->element << " ";
    }
}

template<typename T>
std::ostream &operator<<(std::ostream &out, const chain<T> &x) {
    x.output(out);
    return out;
}

#endif //DATASTRUCTURE_CHAIN_H
