//
// Created by CY815 on 2023/7/10.
//

#ifndef DATASTRUCTURE_DIAGONALMATRIX_H
#define DATASTRUCTURE_DIAGONALMATRIX_H

#include "myExceptions.h"

template<typename T>
class diagonalMatrix {
public:
    explicit diagonalMatrix(int theN = 10);

    virtual ~diagonalMatrix() { delete[] element; }

    T get(int i, int j) const;

    void set(int i, int j, const T &newValue);

private:
    int n;      // 矩阵维数
    T *element; // 存储对角矩阵的一维数组
};

/**
 * 构造函数
 * @tparam T
 * @param theN
 */
template<typename T>
diagonalMatrix<T>::diagonalMatrix(int theN) {
    // 检验theN的值是否有效
    if (theN < 1) {
        throw illegalParameterValue("Matrix size must be > 0");
    }

    n = theN;
    element = new T[n];
}

/**
 * 返回矩阵中(i, j)位置上的元素
 * @tparam T
 * @param i
 * @param j
 * @return
 */
template<typename T>
T diagonalMatrix<T>::get(int i, int j) const {
    // 检验i和j的值是否有效
    if (i < 1 || j < 1 || i > n || j > n) {
        throw matrixIndexOutOfBounds();
    }

    if (i == j) {
        return element[i - 1];  // 对角线上的元素
    } else {
        return 0;   // 非对角线上的元素
    }
}

/**
 * 存储(i, j)项的新值
 * @tparam T
 * @param i
 * @param j
 * @param newValue
 */
template<typename T>
void diagonalMatrix<T>::set(int i, int j, const T &newValue) {
    // 检验i和j的值是否有效
    if (i < 1 || j < 1 || i > n || j > n) {
        throw matrixIndexOutOfBounds();
    }

    if (i == j) {
        element[i - 1] = newValue;      // 存储对焦元素的值
    } else {
        if (newValue != 0) {    // 非对角元素的值必须是0
            throw illegalParameterValue("nondiagonal elements must be zero");
        }
    }
}

#endif //DATASTRUCTURE_DIAGONALMATRIX_H
