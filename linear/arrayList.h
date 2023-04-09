//
// Created by CY815 on 2023/4/5.
//

#ifndef DATASTRUCTURE_ARRAYLIST_H
#define DATASTRUCTURE_ARRAYLIST_H

#include "linearList.h"
#include "common.h"
#include <sstream>
#include <algorithm>
#include <iostream>
#include <iterator>

template<typename T>
class arrayList : public linearList<T> {
public:
    // 构造函数、复制构造函数和析构函数
    explicit arrayList(int initialCapacity = 10);

    arrayList(const arrayList<T> &theList);

    ~arrayList() { delete[] element; }

    // ADT方法
    bool empty() const { return listSize == 0; }

    int size() const { return listSize; }

    T &get(int theIndex) const;

    int indexOf(const T &theElement) const;

    void erase(int theIndex);

    void insert(int theIndex, const T &theElement);

    void output(std::ostream &out) const;

    // 其他方法
    int capacity() const { return arrayLength; }

protected:
    // 若索引theIndex无效，则抛出异常
    void checkIndex(int theIndex) const;

    T *element;         // 存储线性表元素的一维数组
    int arrayLength;    // 一维数组的容量
    int listSize;       // 线性表的元素个数
};

template<typename T>
arrayList<T>::arrayList(int initialCapacity) {
    if (initialCapacity < 1) {
        std::ostringstream s;
        s << "Initial capacity = " << initialCapacity << "must be > 0";
        throw std::invalid_argument(s.str());
    }

    element = new T[initialCapacity];
    arrayLength = initialCapacity;
    listSize = 0;
}

template<typename T>
arrayList<T>::arrayList(const arrayList<T> &theList) {
    arrayLength = theList.arrayLength;
    element = new T[arrayLength];
    listSize = theList.listSize;
    std::copy(theList.element, theList.element + listSize, element);
}

template<typename T>
T &arrayList<T>::get(int theIndex) const {
    checkIndex(theIndex);
    return element[theIndex];
}

template<typename T>
int arrayList<T>::indexOf(const T &theElement) const {
    int theIndex = static_cast<int>(std::find(element, element + listSize, theElement) - element);

    if (theIndex == listSize) {
        return -1;
    } else {
        return theIndex;
    }
}

template<typename T>
void arrayList<T>::erase(int theIndex) {
    checkIndex(theIndex);

    std::copy(element + theIndex + 1, element + listSize, element + theIndex);

    element[--listSize].~T();
}

template<typename T>
void arrayList<T>::insert(int theIndex, const T &theElement) {
    if (theIndex < 0 || theIndex > listSize) {
        std::ostringstream s;
        s << "index = " << theIndex << " size = " << listSize;
        throw std::invalid_argument(s.str());
    }

    if (listSize == arrayLength) {
        changeLength1D(element, arrayLength, 2 * arrayLength);
        arrayLength *= 2;
    }

    std::copy_backward(element + theIndex, element + listSize, element + listSize + 1);

    element[theIndex] = theElement;

    listSize++;
}

template<typename T>
void arrayList<T>::output(std::ostream &out) const {
    std::copy(element, element + listSize, std::ostream_iterator<T>(out, " "));
}

template<typename T>
void arrayList<T>::checkIndex(int theIndex) const {
    if (theIndex < 0 || theIndex >= listSize) {
        std::ostringstream s;
        s << "index = " << theIndex << " size = " << listSize;
        throw std::invalid_argument(s.str());
    }
}

template<typename T>
std::ostream &operator<<(std::ostream &out, const arrayList<T> &x) {
    x.output(out);
    return out;
}

#endif //DATASTRUCTURE_ARRAYLIST_H
