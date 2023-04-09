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

    T *temp = new T[newLength];
    int number = std::min(oldLength, newLength);
    std::copy(a, a + number, temp);
    delete[] a;
    a = temp;
}

#endif //DATASTRUCTURE_COMMON_H
