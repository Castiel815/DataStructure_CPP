//
// Created by CY815 on 2023/5/24.
//

#ifndef DATASTRUCTURE_CIRCULARLISTWITHHEADER_H
#define DATASTRUCTURE_CIRCULARLISTWITHHEADER_H

#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>
#include "chainNode.h"

template<typename T>
class circularListWithHeader {
public:
    // constructor
    circularListWithHeader();

    // some methods
    int size() const { return listSize; }

    int indexOf(const T &theElement) const;

    void insert(int theIndex, const T &theElement);

    void output(std::ostream &out) const;

protected:
    void checkIndex(int theIndex) const;

    chainNode<T> *headerNode;
    int listSize;
};

/**
 * 构造函数
 * @tparam T
 */
template<typename T>
circularListWithHeader<T>::circularListWithHeader() {
    headerNode = new chainNode<T>();
    headerNode->next = headerNode;
    listSize = 0;
}

template<typename T>
void circularListWithHeader<T>::checkIndex(int theIndex) const {
    if (theIndex < 0 || theIndex >= listSize) {
        std::ostringstream s;
        s << "index = " << theIndex << "size = " << listSize;
        throw std::invalid_argument(s.str());
    }
}

/**
 * 返回元素theElement首次出现的索引，若该元素不存在，则返回-1
 * @tparam T
 * @param theIndex
 */
template<typename T>
int circularListWithHeader<T>::indexOf(const T &theElement) const {
    // 将元素theElement放入头节点
    headerNode->element = theElement;

    // 在链表中搜索元素theElement
    chainNode<T> *currentNode = headerNode->next;
    int index = 0;  // 当前节点的索引
    while (currentNode->element != theElement) {
        // 移动到下一个节点
        currentNode = currentNode->next;
        index++;
    }

    // 确定是否找到元素theElement
    if (currentNode == headerNode)
        return -1;
    else
        return index;
}

template<typename T>
void circularListWithHeader<T>::insert(int theIndex, const T &theElement) {
    if (theIndex < 0 || theIndex > listSize) {
        std::ostringstream s;
        s << "index = " << theIndex << " size = " << listSize;;
        throw std::invalid_argument(s.str());
    }

    chainNode<T> *p = headerNode;
    for (int i = 0; i < theIndex; i++)
        p = p->next;

    p->next = new chainNode<T>(theElement, p->next);

    listSize++;
}

template<typename T>
void circularListWithHeader<T>::output(std::ostream &out) const {
    for (chainNode<T> *currentNode = headerNode->next;
         currentNode != headerNode; currentNode = currentNode->next)
        out << currentNode->element << " ";
}

template<typename T>
std::ostream &operator<<(std::ostream &out, const circularListWithHeader<T> &x) {
    x.output(out);
    return out;
}

#endif //DATASTRUCTURE_CIRCULARLISTWITHHEADER_H
