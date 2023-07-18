//
// Created by CY815 on 2023/7/17.
//

#ifndef DATASTRUCTURE_STACK_H
#define DATASTRUCTURE_STACK_H

template<typename T>
class stack {
public:
    virtual ~stack() = default;

    virtual bool empty() const = 0; // 返回true，当且仅当栈为空
    virtual int size() const = 0;   // 返回栈中元素个数
    virtual T &top() = 0;           // 返回栈顶元素的引用
    virtual void pop() = 0;         // 删除栈顶元素
    virtual void push(const T &theElement) = 0;  // 将元素theElement压入栈顶
};

#endif //DATASTRUCTURE_STACK_H
