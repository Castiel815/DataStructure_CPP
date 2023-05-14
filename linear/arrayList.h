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

    class iterator;

    iterator begin() { return iterator(element); }

    iterator end() { return iterator(element + listSize); }

    class iterator {
    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = T;
        using difference_type = ptrdiff_t;
        using pointer = T *;
        using reference = T &;

        // 构造函数
        explicit iterator(T *thePosition = 0) { position = thePosition; }

        // 解引用操作符
        T &operator*() const { return *position; }

        T *operator->() const { return &*position; }

        // 迭代器的值增加
        iterator &operator++() {    // 前加
            ++position;
            return *this;
        }

        iterator operator++(int) {  // 后加
            iterator old = *this;
            ++position;
            return old;
        }

        // 迭代器的值减少
        iterator &operator--() {
            --position;
            return *this;
        }

        iterator operator--(int) {
            iterator old = *this;
            --position;
            return old;
        }

        // 测试是否相等
        bool operator!=(const iterator right) const {
            return position != right.position;
        }

        bool operator==(const iterator right) const {
            return position == right.position;
        }

    protected:
        T *position;    // 指向表元素的指针
    };

protected:
    // 若索引theIndex无效，则抛出异常
    void checkIndex(int theIndex) const;

    T *element;         // 存储线性表元素的一维数组
    int arrayLength;    // 一维数组的容量
    int listSize;       // 线性表的元素个数
};

/**
 * 构造函数
 * @tparam T
 * @param initialCapacity
 */
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

/**
 * 复制构造函数
 * @tparam T
 * @param theList
 */
template<typename T>
arrayList<T>::arrayList(const arrayList<T> &theList) {
    arrayLength = theList.arrayLength;
    element = new T[arrayLength];
    listSize = theList.listSize;
    std::copy(theList.element, theList.element + listSize, element);
}

/**
 * 返回索引为theIndex的元素，若此元素不存在，则抛出异常
 * @tparam T
 * @param theIndex
 * @return
 */
template<typename T>
T &arrayList<T>::get(int theIndex) const {
    checkIndex(theIndex);
    return element[theIndex];
}

/**
 * 返回元素theElement第一次出现时的索引，若该元素不存在，则返回-1
 * @tparam T
 * @param theElement
 * @return
 */
template<typename T>
int arrayList<T>::indexOf(const T &theElement) const {
    // 查找元素theElement
    int theIndex = static_cast<int>(std::find(element, element + listSize, theElement) - element);

    // 确定元素theElement是否找到
    if (theIndex == listSize) {
        return -1;  // 没有找到
    } else {
        return theIndex;
    }
}

/**
 * 删除其索引为theIndex的元素，如果该元素不存在，则抛出异常
 * @tparam T
 * @param theIndex
 */
template<typename T>
void arrayList<T>::erase(int theIndex) {
    checkIndex(theIndex);

    // 有效索引，移动其索引大于theIndex的元素
    std::copy(element + theIndex + 1, element + listSize, element + theIndex);

    element[--listSize].~T();   // 调用析构函数

    if (listSize < arrayLength / 4) {
        int number = std::max(10, arrayLength / 2);
        T *temp = new T[number];
        std::copy(element, element + listSize, temp);
        delete[] element;
        element = temp;
    }
}

/**
 * 在索引theIndex处插入元素theElement
 * @tparam T
 * @param theIndex
 * @param theElement
 */
template<typename T>
void arrayList<T>::insert(int theIndex, const T &theElement) {
    if (theIndex < 0 || theIndex > listSize) {  // 无效索引
        std::ostringstream s;
        s << "index = " << theIndex << " size = " << listSize;
        throw std::invalid_argument(s.str());
    }

    // 有效索引，确定数组是否已满
    if (listSize == arrayLength) {
        // 数组空间已满，数组长度倍增
        changeLength1D(element, arrayLength, 2 * arrayLength);
        arrayLength *= 2;
    }

    // 把元素向右移动一个位置
    std::copy_backward(element + theIndex, element + listSize, element + listSize + 1);

    element[theIndex] = theElement;

    listSize++;
}

/**
 * 把一个线性表插入输出流
 * @tparam T
 * @param out
 */
template<typename T>
void arrayList<T>::output(std::ostream &out) const {
    std::copy(element, element + listSize, std::ostream_iterator<T>(out, " "));
}

/**
 * 确定索引theIndex在 0 和 listSize - 1 之间
 * @tparam T
 * @param theIndex
 */
template<typename T>
void arrayList<T>::checkIndex(int theIndex) const {
    if (theIndex < 0 || theIndex >= listSize) {
        std::ostringstream s;
        s << "index = " << theIndex << " size = " << listSize;
        throw std::invalid_argument(s.str());
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
std::ostream &operator<<(std::ostream &out, const arrayList<T> &x) {
    x.output(out);
    return out;
}

#endif //DATASTRUCTURE_ARRAYLIST_H
