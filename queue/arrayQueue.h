//
// Created by CY815 on 2023/7/23.
//

#ifndef DATASTRUCTURE_ARRAYQUEUE_H
#define DATASTRUCTURE_ARRAYQUEUE_H

#include "queue.h"
#include "myExceptions.h"
#include <sstream>

template<typename T>
class arrayQueue : public queue<T> {
public:
    explicit arrayQueue(int initialCapacity = 10);

    ~arrayQueue() override {
        delete[] queue;
        queue = nullptr;
    }

    bool empty() const override { return theFront == theBack; }

    int size() const override { return (theBack - theFront + arrayLength) % arrayLength; }

    T &front() override {
        if (theFront == theBack) {
            throw queueEmpty();
        }
        return queue[(theFront + 1) % arrayLength];
    }

    T &back() override {
        if (theFront == theBack) {
            throw queueEmpty();
        }
        return queue[theBack];
    }

    /**
     * 删除队列首元素
     */
    void pop() override {
        if (theFront == theBack) {
            throw queueEmpty();
        }
        theFront = (theFront + 1) % arrayLength;
        queue[theFront].~T();       // 给T析构
    }

    void push(const T &theElement) override;

private:
    int theFront;
    int theBack;
    int arrayLength;
    T *queue;
};

template<typename T>
arrayQueue<T>::arrayQueue(int initialCapacity) {
    if (initialCapacity < 1) {
        std::ostringstream s;
        s << "Initial capacity = " << initialCapacity << "Must be > 0";
        throw illegalParameterValue(s.str());
    }

    arrayLength = initialCapacity;
    queue = new T[arrayLength];
    theFront = 0;
    theBack = 0;
}


/**
 * 把元素theElement加入队列
 * @tparam T
 * @param theElement
 */
template<typename T>
void arrayQueue<T>::push(const T &theElement) {
    // 如果需要，则增加数组长度
    if ((theBack + 1) % arrayLength == theFront) {
        // 加倍数组长度

        // 分配新的数组空间
        T *newQueue = new T[2 * arrayLength];

        // 把原数组元素复制到新数组
        int start = (theFront + 1) % arrayLength;
        if (start < 2) {
            // 没有形成环
            std::copy(queue + start, queue + start + arrayLength - 1, newQueue);
        } else {
            // 队列形成环
            std::copy(queue + start, queue + arrayLength, newQueue);
            std::copy(queue, queue + theBack + 1, newQueue + arrayLength - start);
        }

        // 设置新队列的首和尾的元素位置
        theFront = 2 * arrayLength - 1;
        theBack = arrayLength - 2;      // 队列长度-1
        arrayLength *= 2;
        queue = newQueue;
    }

    // 把元素theElement插入队列的尾部
    theBack = (theBack + 1) % arrayLength;
    queue[theBack] = theElement;
}

#endif //DATASTRUCTURE_ARRAYQUEUE_H
