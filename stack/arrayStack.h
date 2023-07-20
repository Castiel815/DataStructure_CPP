//
// Created by CY815 on 2023/7/18.
//

#ifndef DATASTRUCTURE_ARRAYSTACK_H
#define DATASTRUCTURE_ARRAYSTACK_H

#include "stack.h"
#include "myExceptions.h"
#include "common.h"
#include <sstream>

template<typename T>
class arrayStack : public stack<T> {
public:
    explicit arrayStack(int initialCapacity = 10);

    ~arrayStack() override {
        delete[] stack;
        stack = nullptr;
    }

    bool empty() const override { return stackTop == -1; }

    int size() const override { return stackTop + 1; }

    T &top() override {
        if (stackTop == -1) {
            throw stackEmpty();
        }
        return stack[stackTop];
    }

    void pop() override {
        if (stackTop == -1) {
            throw stackEmpty();
        }
        stack[stackTop--].~T();     // T的析构函数
    }

    void push(const T &theElement) override;

private:
    int stackTop;       // 当前栈顶
    int arrayLength;    // 栈容量
    T *stack;           // 元素数组
};

/**
 * 构造函数
 * @tparam T
 * @param initialCapacity
 */
template<typename T>
arrayStack<T>::arrayStack(int initialCapacity) {
    if (initialCapacity < 1) {
        std::ostringstream s;
        s << "Initial capacity = " << initialCapacity << " Must be > 0";
        throw illegalParameterValue(s.str());
    }

    arrayLength = initialCapacity;
    stack = new T[arrayLength];
    stackTop = -1;
}

/**
 * 将元素theElement压入栈
 * @tparam T
 * @param theElement
 */
template<typename T>
void arrayStack<T>::push(const T &theElement) {
    if (stackTop == arrayLength - 1) {  // 空间已满，容量加倍
        changeLength1D(stack, arrayLength, 2 * arrayLength);
        arrayLength *= 2;
    }

    // 在栈顶插入
    stack[++stackTop] = theElement;
}

#endif //DATASTRUCTURE_ARRAYSTACK_H
