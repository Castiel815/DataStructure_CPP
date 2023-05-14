//
// Created by CY815 on 2023/4/5.
//

#ifndef DATASTRUCTURE_COMMON_H
#define DATASTRUCTURE_COMMON_H

#include <stdexcept>

/**
 * 改变一个一维数组长度
 * @tparam T
 * @param a
 * @param oldLength
 * @param newLength
 */
template<typename T>
void changeLength1D(T *&a, int oldLength, int newLength) {
    if (newLength < 0) {
        throw std::invalid_argument("new length must be >= 0");
    }

    T *temp = new T[newLength];     // 新数组
    int number = std::min(oldLength, newLength);    // 需要复制的元素个数
    std::copy(a, a + number, temp);
    delete[] a;     // 释放老数组的内存空间
    a = temp;
}

#endif //DATASTRUCTURE_COMMON_H
