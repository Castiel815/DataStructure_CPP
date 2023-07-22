//
// Created by CY815 on 2023/7/22.
//

#ifndef DATASTRUCTURE_QUEUE_H
#define DATASTRUCTURE_QUEUE_H

template<typename T>
class queue {
public:
    virtual ~queue() = default;

    virtual bool empty() const = 0; // 返回true, 当且仅当队列为空

    virtual int size() const = 0;   // 返回队列中元素个数

    virtual T &front() = 0;     // 返回头元素的引用

    virtual T &back() = 0;      // 返回尾元素的引用

    virtual void pop() = 0;     // 删除首元素

    virtual void push(const T &theElement) = 0;     // 把元素theElement加入队尾

};

#endif //DATASTRUCTURE_QUEUE_H
