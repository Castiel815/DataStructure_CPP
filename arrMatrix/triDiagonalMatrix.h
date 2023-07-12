//
// Created by CY815 on 2023/7/11.
//

#ifndef DATASTRUCTURE_TRIDIAGONALMATRIX_H
#define DATASTRUCTURE_TRIDIAGONALMATRIX_H

#include "myExceptions.h"

template<typename T>
class triDiagonalMatrix {
public:
    explicit triDiagonalMatrix(int theN = 10);

    virtual ~triDiagonalMatrix() { delete[] element; }

    T get(int i, int j) const;

    void set(int i, int j, const T &newValue);

private:
    int n;
    T *element;
};

template<typename T>
triDiagonalMatrix<T>::triDiagonalMatrix(int theN) {
    if (theN < 1) {
        throw illegalParameterValue("Matrix size must be > 0");
    }

    n = theN;
    element = new T[3 * n - 2];
}

/**
 * 返回矩阵中(i, j)位置上的元素
 * @tparam T
 * @param i
 * @param j
 * @return
 */
template<typename T>
T triDiagonalMatrix<T>::get(int i, int j) const {
    // 检验i和j的值是否有效
    if (i < 1 || j < 1 || i > n || j > n) {
        throw matrixIndexOutOfBounds();
    }

    // 确定要返回的元素
    switch (i - j) {
        case 1:     // 下对角线
            return element[i - 2];
        case 0:     // 主对角线
            return element[n + i - 2];
        case -1:    // 上对角线
            return element[2 * n + i - 2];
        default:
            return 0;
    }
}

template<typename T>
void triDiagonalMatrix<T>::set(int i, int j, const T &newValue) {
    if (i < 1 || j < 1 || i > n || j > n) {
        throw matrixIndexOutOfBounds();
    }

    switch (i - j) {
        case 1:
            element[i - 2] = newValue;
            break;
        case 0:
            element[n + i - 2] = newValue;
            break;
        case -1:
            element[2 * n + i - 2] = newValue;
            break;
        default:
            if (newValue != 0) {
                throw illegalParameterValue("non-triDiagonal elements must be zero");
            }
    }
}

#endif //DATASTRUCTURE_TRIDIAGONALMATRIX_H
