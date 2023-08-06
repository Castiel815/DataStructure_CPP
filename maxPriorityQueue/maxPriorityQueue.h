//
// Created by CY815 on 2023/8/6.
//

#ifndef DATASTRUCTURE_MAXPRIORITYQUEUE_H
#define DATASTRUCTURE_MAXPRIORITYQUEUE_H

template<typename T>
class maxPriorityQueue {
public:
    virtual ~maxPriorityQueue() = default;

    virtual bool empty() const = 0;     // 返回true。当且仅当队列为空
    virtual int size() const = 0;       // 返回队列的元素个数
    virtual const T &top() = 0;         // 返回优先级最大的元素的引用
    virtual void pop() = 0;             // 删除队首元素
    virtual void push(const T &theElement) = 0;     // 插入元素theElement
};

#endif //DATASTRUCTURE_MAXPRIORITYQUEUE_H
