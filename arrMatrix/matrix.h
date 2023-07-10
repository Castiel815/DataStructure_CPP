//
// Created by CY815 on 2023/7/4.
//

#ifndef DATASTRUCTURE_MATRIX_H
#define DATASTRUCTURE_MATRIX_H

#include "myExceptions.h"
#include <algorithm>

template<typename T>
class matrix {
    friend std::ostream &operator<<(std::ostream &, const matrix<T> &);

public:
    explicit matrix(int theRows = 0, int theColumns = 0);

    matrix(const matrix<T> &m);

    virtual ~matrix() {
        delete[] element;
        element = nullptr;
    }

    int rows() const { return theRows; }

    int columns() const { return theColumns; }

    T &operator()(int i, int j) const;

    matrix<T> &operator=(const matrix<T> &m);

    matrix<T> operator+() const;

    matrix<T> operator+(const matrix<T> &m) const;

    matrix<T> operator-() const;

    matrix<T> operator-(const matrix<T> &m) const;

    matrix<T> operator*(const matrix<T> &m) const;

    matrix<T> &operator+=(const T &x);

private:
    int theRows, theColumns;    // 矩阵的行数和矩阵的列数
    T *element;                 // 数组element
};


/**
 * 矩阵构造函数
 * @tparam T
 * @param theRows
 * @param theColumns
 */
template<typename T>
matrix<T>::matrix(int theRows, int theColumns) {
    // 检验行数和列数的有效性
    if (theRows < 0 || theColumns < 0) { throw illegalParameterValue("Rows and columns must be >= 0"); }
    if ((theRows == 0 || theColumns == 0) && (theRows != 0 || theColumns != 0)) {
        throw illegalParameterValue("Either both or neither rows and columns should be zero");
    }

    // 创建矩阵
    this->theRows = theRows;
    this->theColumns = theColumns;
    element = new T[theRows * theColumns];
}

/**
 * 矩阵的复制构造函数
 * @tparam T
 * @param m
 */
template<typename T>
matrix<T>::matrix(const matrix<T> &m) {
    // 创建矩阵
    theRows = m.theRows;
    theColumns = m.theColumns;
    element = new T[theRows * theColumns];

    // 复制m的每一个元素
    std::copy(m.element, m.element + theRows * theColumns, element);
}

/**
 * 重载复制操作符
 * @tparam T
 * @param m
 * @return
 */
template<typename T>
matrix<T> &matrix<T>::operator=(const matrix<T> &m) {
    // 不能自己复制自己
    if (this != &m) {
        delete[] element;
        element = nullptr;
        theRows = m.theRows;
        theColumns = m.theColumns;
        element = new T[theRows * theColumns];

        // 复制每一个元素
        std::copy(m.element, m.element + theRows * theColumns, element);
    }

    return *this;
}

/**
 * 重载()操作符，返回对元素element(i, j)的引用
 * @tparam T
 * @param i
 * @param j
 * @return
 */
template<typename T>
T &matrix<T>::operator()(int i, int j) const {
    if (i < 1 || i > theRows || j < 1 || j > theColumns) { throw matrixIndexOutOfBounds(); }
    return element[(i - 1) * theColumns + j - 1];
}

/**
 * 矩阵加法，返回矩阵 w = (*this) + m
 * @tparam T
 * @param m
 * @return
 */
template<typename T>
matrix<T> matrix<T>::operator+(const matrix<T> &m) const {
    if (theRows != m.theRows || theColumns != m.theColumns) { throw matrixSizeMismatch(); }

    // 生成结果矩阵
    matrix<T> w(theRows, theColumns);
    for (int i = 0; i < theRows * theColumns; ++i) {
        w.element[i] = element[i] + m.element[i];
    }

    return w;
}

template<typename T>
matrix<T> matrix<T>::operator+() const {
    matrix<T> w(theRows, theColumns);
    for (int i = 0; i < theRows * theColumns; ++i) {
        w.element[i] = +element[i];
    }
}

template<typename T>
matrix<T> matrix<T>::operator-(const matrix<T> &m) const {
    if (theRows != m.theRows || theColumns != m.theColumns) {
        throw matrixSizeMismatch();
    }

    matrix<T> w(theRows, theColumns);
    for (int i = 0; i < theRows * theColumns; ++i) {
        w.element[i] = element[i] - m.element[i];
    }

    return w;
}

template<typename T>
matrix<T> matrix<T>::operator-() const {
    matrix<T> w(theRows, theColumns);
    for (int i = 0; i < theRows * theColumns; ++i) {
        w.element[i] = -element[i];
    }

    return w;
}

/**
 * 矩阵乘法，返回结果矩阵 w = (*this) * m
 * @tparam T
 * @param m
 * @return
 */
template<typename T>
matrix<T> matrix<T>::operator*(const matrix<T> &m) const {
    if (theColumns != m.theRows) {
        throw matrixSizeMismatch();
    }

    matrix<T> w(theRows, m.theColumns); // 结果矩阵

    // 定义矩阵*this,m和w的游标且初始化以为(1,1)元素定位
    int ct = 0, cm = 0, cw = 0;

    // 对所有i和j计算w(i, j)
    for (int i = 1; i <= theRows; ++i) {
        // 计算结果矩阵的第i行
        for (int j = 1; j <= m.theColumns; ++j) {
            // 计算w(i, j)第一项
            T sum = element[ct] * m.element[cm];

            // 累加其余所有项
            for (int k = 2; k <= theColumns; ++k) {
                ct++;                               // *this中第i行的下一项
                cm += m.theColumns;                 // m中第j列的下一项
                sum += element[ct] * m.element[cm];
            }

            w.element[cw++] = sum;  // 存储在w(i,j)

            // 从行的起点和下一列开始
            ct -= theColumns - 1;
            cm = j;
        }

        // 从下一行和第一列重新开始
        ct += theColumns;
        cm = 0;
    }

    return w;
}

template<typename T>
matrix<T> &matrix<T>::operator+=(const T &x) {
    for (int i = 0; i < theRows * theColumns; ++i) {
        element[i] += x;
    }

    return *this;
}

template<typename T>
std::ostream &operator<<(std::ostream &out, const matrix<T> &m) {
    int k = 0;
    for (int i = 0; i < m.theRows; ++i) {
        for (int j = 0; j < m.theColumns; ++j) {
            out << m.element[k++] << "  ";
        }

        out << std::endl;
    }

    return out;
}

std::ostream &operator<<(std::ostream &out, const matrix<int> &m) {
    int k = 0;
    for (int i = 0; i < m.theRows; ++i) {
        for (int j = 0; j < m.theColumns; ++j) {
            out << m.element[k++] << "  ";
        }

        out << std::endl;
    }

    return out;
}

#endif //DATASTRUCTURE_MATRIX_H
