//
// Created by CY815 on 2023/7/12.
//

#ifndef DATASTRUCTURE_LOWERTRIANGULARMATRIX_H
#define DATASTRUCTURE_LOWERTRIANGULARMATRIX_H

#include "myExceptions.h"

template<typename T>
class lowerTriangularMatrix {
public:
    explicit lowerTriangularMatrix(int theN = 10);

    virtual ~lowerTriangularMatrix() {
        delete[] element;
        element = nullptr;
    }

    T get(int i, int j) const;

    void set(int, int, const T &);

private:
    int n;
    T *element;
};

template<typename T>
lowerTriangularMatrix<T>::lowerTriangularMatrix(int theN) {
    if (theN < 1) {
        throw illegalParameterValue("Matrix size must be > 0");
    }

    n = theN;
    element = new T[n * (n + 1) / 2];
}

template<typename T>
T lowerTriangularMatrix<T>::get(int i, int j) const {
    if (i < 1 || j < 1 || i > n || j > n) {
        throw matrixIndexOutOfBounds();
    }

    if (i >= j) {
        return element[i * (i - 1) / 2 + j - 1];
    } else
        return 0;
}

/**
 * 给(i, j)元素赋新值
 * @tparam T
 * @param i
 * @param j
 * @param newValue
 */
template<typename T>
void lowerTriangularMatrix<T>::set(int i, int j, const T &newValue) {
    // 检查i和j的值是否合法
    if (i < 1 || j < 1 || i > n || j > n) {
        throw matrixIndexOutOfBounds();
    }

    // (i, j)在下三角，当且仅当i >= j
    if (i >= j) {
        element[i * (i - 1) / 2 + j - 1] = newValue;
    } else {
        if (newValue != 0) {
            throw illegalParameterValue("elements not in lower triangle must be zero");
        }
    }
}

#endif //DATASTRUCTURE_LOWERTRIANGULARMATRIX_H
