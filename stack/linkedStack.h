//
// Created by CY815 on 2023/7/20.
//

#ifndef DATASTRUCTURE_LINKEDSTACK_H
#define DATASTRUCTURE_LINKEDSTACK_H

#include "stack.h"
#include "../chainLinear/chainNode.h"
#include "myExceptions.h"
#include <sstream>

template<typename T>
class linkedStack : public stack<T> {
public:
    explicit linkedStack(int initialCapacity = 10) {
        stackTop = nullptr;
        stackSize = 0;
    }

    ~linkedStack() override;

    bool empty() const override {
        return stackSize == 0;
    }

    int size() const override {
        return stackSize;
    }

    T &top() override {
        if (stackSize == 0) {
            throw stackEmpty();
        }
        return stackTop->element;
    }

    void pop() override;

    void push(const T &theElement) override {
        stackTop = new chainNode<T>(theElement, stackTop);
        stackSize++;
    }

private:
    chainNode<T> *stackTop;     // 栈顶指针
    int stackSize;              // 栈中元素个数
};

/**
 * 析构函数
 * @tparam T
 */
template<typename T>
linkedStack<T>::~linkedStack() {
    while (stackTop != nullptr) {   // 删除栈顶节点
        chainNode<T> *nextNode = stackTop->next;
        delete stackTop;
        stackTop = nextNode;
    }
}

/**
 * 删除栈顶节点
 * @tparam T
 */
template<typename T>
void linkedStack<T>::pop() {
    if (stackSize == 0) {
        throw stackEmpty();
    }

    chainNode<T> *nextNode = stackTop->next;
    delete stackTop;
    stackTop = nextNode;
    stackSize--;
}

#endif //DATASTRUCTURE_LINKEDSTACK_H
