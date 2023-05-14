//
// Created by CY815 on 2023/4/11.
//

#ifndef DATASTRUCTURE_VECTORLIST_H
#define DATASTRUCTURE_VECTORLIST_H

#include "linearList.h"
#include <stdexcept>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>

template<typename T>
class vectorList : public linearList<T> {
public:
    // constructor, copy constructor and destructor
    explicit vectorList(int initialCapacity = 10);

    vectorList(const vectorList<T> &theList);

    ~vectorList() { delete element; }

    // ADT methods
    bool empty() const { return element->empty(); }

    int size() const { return (int) element->size(); }

    T &get(int theIndex) const;

    int indexOf(const T &theElement) const;

    void erase(int theIndex);

    void insert(int theIndex, const T &theElement);

    void output(std::ostream &out) const;

    // additional method
    int capacity() const { return (int) element->capacity(); }

    // iterators to start and end of list
    using iterator = typename std::vector<T>::iterator;

    iterator begin() { return element->begin(); }

    iterator end() { return element->end(); }

protected:
    void checkIndex(int theIndex) const;

    std::vector<T> *element;    // 存储线性表元素的向量
};

/**
 * 构造函数
 * @tparam T
 * @param initialCapacity
 */
template<typename T>
vectorList<T>::vectorList(int initialCapacity) {
    if (initialCapacity < 1) {
        std::ostringstream s;
        s << "Initial capacity = " << initialCapacity << " must be > 0";
        throw std::invalid_argument(s.str());
    }

    // 创建容量为0的空向量
    element = new std::vector<T>;

    // vector容量从0增加到initialCapacity
    element->reserve(initialCapacity);
}

/**
 * 复制构造函数
 * @tparam T
 * @param theList
 */
template<typename T>
vectorList<T>::vectorList(const vectorList<T> &theList) {
    element = new std::vector<T>(*theList.element);
}

template<typename T>
void vectorList<T>::checkIndex(int theIndex) const {
    if (theIndex < 0 || theIndex >= size()) {
        std::ostringstream s;
        s << "index = " << theIndex << " size = " << size();
        throw std::invalid_argument(s.str());
    }
}

template<typename T>
T &vectorList<T>::get(int theIndex) const {
    checkIndex(theIndex);
    return (*element)[theIndex];
}

template<typename T>
int vectorList<T>::indexOf(const T &theElement) const {
    int theIndex = (int) (std::find(element->begin(), element->end(), theElement) - element->begin());

    if (theIndex == size())
        return -1;
    else
        return theIndex;
}

/**
 * 删除索引为theIndex的元素，如果没有这个元素，则抛出异常
 * @tparam T
 * @param theIndex
 */
template<typename T>
void vectorList<T>::erase(int theIndex) {
    checkIndex(theIndex);
    element->erase(begin() + theIndex);
}

/**
 * 在索引为theIndex处插入元素theElement
 * @tparam T
 * @param theIndex
 * @param theElement
 */
template<typename T>
void vectorList<T>::insert(int theIndex, const T &theElement) {
    if (theIndex < 0 || theIndex > size()) {    // 无效索引
        std::ostringstream s;
        s << "index = " << theIndex << " size = " << size();
        throw std::invalid_argument(s.str());
    }

    // 如果在重定向量长度时空间不足，那么可以抛出没有捕捉的异常
    element->insert(element->begin() + theIndex, theElement);
}

template<typename T>
void vectorList<T>::output(std::ostream &out) const {
    std::copy(element->begin(), element->end(), std::ostream_iterator<T>(out, " "));
}

template<typename T>
std::ostream &operator<<(std::ostream &out, const vectorList<T> &x) {
    x.output(out);
    return out;
}

#endif //DATASTRUCTURE_VECTORLIST_H
