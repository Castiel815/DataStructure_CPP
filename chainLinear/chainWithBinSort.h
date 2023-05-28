//
// Created by CY815 on 2023/5/28.
//

#ifndef DATASTRUCTURE_CHAINWITHBINSORT_H
#define DATASTRUCTURE_CHAINWITHBINSORT_H

#include <iostream>
#include <sstream>
#include <string>
#include "linearList.h"
#include "chainNode.h"
#include <stdexcept>
#include "studentRecord.h"

template<typename T>
class chainWithBinSort : public linearList<T> {
public:
    explicit chainWithBinSort(int initialCapacity = 10);

    chainWithBinSort(const chainWithBinSort<T> &theList);

    ~chainWithBinSort();

    bool empty() const { return listSize == 0; }

    int size() const { return listSize; }

    T &get(int theIndex) const;

    int indexOf(const T &theElement) const;

    void erase(int theIndex);

    void insert(int theIndex, const T &theElement);

    void output(std::ostream &out) const;

    void binSort(int range);

    void binSort(int range, int (*value)(T &x));

    friend std::ostream &operator<<(std::ostream &out, const chainWithBinSort<T> &x) {
        x.output(out);
        return out;
    }

protected:
    void checkIndex(int theIndex) const;

    chainNode<T> *firstNode;
    int listSize;
};

template<typename T>
chainWithBinSort<T>::chainWithBinSort(int initialCapacity) {
    if (initialCapacity < 1) {
        std::ostringstream s;
        s << "Initial capacity = " << initialCapacity << " Must be > 0";
        throw std::invalid_argument(s.str());
    }

    firstNode = nullptr;
    listSize = 0;
}

template<typename T>
chainWithBinSort<T>::chainWithBinSort(const chainWithBinSort<T> &theList) {
    listSize = theList.listSize;

    if (listSize == 0) {
        firstNode = nullptr;
        return;
    }

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
chainWithBinSort<T>::~chainWithBinSort() {
    chainNode<T> *nextNode;
    while (firstNode != nullptr) {
        nextNode = firstNode->next;
        delete firstNode;
        firstNode = nextNode;
    }
}

template<typename T>
void chainWithBinSort<T>::checkIndex(int theIndex) const {
    if (theIndex < 0 || theIndex >= listSize) {
        std::ostringstream s;
        s << "index = " << theIndex << " size = " << listSize;
        throw std::invalid_argument(s.str());
    }
}

template<typename T>
T &chainWithBinSort<T>::get(int theIndex) const {
    checkIndex(theIndex);

    chainNode<T> *currentNode = firstNode;
    for (int i = 0; i < theIndex; i++) {
        currentNode = currentNode->next;
    }

    return currentNode->element;
}

template<typename T>
int chainWithBinSort<T>::indexOf(const T &theElement) const {
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
void chainWithBinSort<T>::erase(int theIndex) {
    checkIndex(theIndex);

    chainNode<T> *deleteNode;
    if (theIndex == 0) {
        deleteNode = firstNode;
        firstNode = firstNode->next;
    } else {
        chainNode<T> *p = firstNode;
        for (int i = 0; i < theIndex - 1; i++) {
            p = p->next;
        }

        deleteNode = p->next;
        p->next = p->next->next;
    }

    listSize--;
    delete deleteNode;
}

template<typename T>
void chainWithBinSort<T>::insert(int theIndex, const T &theElement) {
    if (theIndex < 0 || theIndex > listSize) {
        std::ostringstream s;
        s << "index = " << theIndex << " size = " << listSize;
        throw std::invalid_argument(s.str());
    }

    if (theIndex == 0) {
        firstNode = new chainNode<T>(theElement, firstNode);
    } else {
        chainNode<T> *p = firstNode;
        for (int i = 0; i < theIndex - 1; i++) {
            p = p->next;
        }

        p->next = new chainNode<T>(theElement, p->next);
    }

    listSize++;
}

template<typename T>
void chainWithBinSort<T>::output(std::ostream &out) const {
    for (chainNode<T> *currentNode = firstNode; currentNode != nullptr; currentNode = currentNode->next) {
        out << currentNode->element << " ";
    }
}

//template<typename T>
//std::ostream &operator<<(std::ostream &out, const chainWithBinSort<T> &x) {
//    x.output(out);
//    return out;
//}

/**
 * 对链表中的节点排序
 * @tparam T
 * @param range
 */
template<typename T>
void chainWithBinSort<T>::binSort(int range) {
    // 创建并初始化箱子
    chainNode<T> **bottom, **top;
    bottom = new chainNode<T> *[range + 1];
    top = new chainNode<T> *[range + 1];

    for (int b = 0; b <= range; ++b) {
        bottom[b] = nullptr;
    }

    // 把链表的节点分配到箱子
    for (; firstNode != nullptr; firstNode = firstNode->next) {
        // 把首节点firstNode加到箱子中
        int theBegin = firstNode->element;  // 元素类型转换到整型int
        if (bottom[theBegin] == nullptr) {  // 箱子为空
            bottom[theBegin] = top[theBegin] = firstNode;
        } else {    // 箱子不空
            top[theBegin]->next = firstNode;
            top[theBegin] = firstNode;
        }
    }

    // 把箱子中的节点收集到有序链表
    chainNode<T> *y = nullptr;
    for (int theBin = 0; theBin <= range; theBin++) {
        if (bottom[theBin] != nullptr) {    // 箱子不空
            if (y == nullptr) { // 第一个非空箱子
                firstNode = bottom[theBin];
            } else {    // 不是第一个非空箱子
                y->next = bottom[theBin];
            }
            y = top[theBin];
        }
    }

    if (y != nullptr) {
        y->next = nullptr;
    }

    delete[] bottom;
    delete[] top;
}

template<typename T>
void chainWithBinSort<T>::binSort(int range, int (*value)(T &)) {
    chainNode<T> **bottom, **top;
    bottom = new chainNode<T> *[range + 1];
    top = new chainNode<T> *[range + 1];

    for (int b = 0; b <= range; b++) {
        bottom[b] = nullptr;
    }

    for (; firstNode != nullptr; firstNode = firstNode->next) {
        int theBin = value(firstNode->element);

        if (bottom[theBin] == nullptr) {
            bottom[theBin] = top[theBin] = firstNode;
        } else {
            top[theBin]->next = firstNode;
            top[theBin] = firstNode;
        }
    }

    chainNode<T> *y = nullptr;
    for (int theBin = 0; theBin <= range; theBin++) {
        if (bottom[theBin] != nullptr) {
            if (y == nullptr) {
                firstNode = bottom[theBin];
            } else {
                y->next = bottom[theBin];
            }
            y = top[theBin];
        }
    }

    if (y != nullptr) {
        y->next = nullptr;
    }

    delete[] bottom;
    delete[] top;
}

#endif //DATASTRUCTURE_CHAINWITHBINSORT_H
