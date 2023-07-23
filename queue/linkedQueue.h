//
// Created by CY815 on 2023/7/23.
//

#ifndef DATASTRUCTURE_LINKEDQUEUE_H
#define DATASTRUCTURE_LINKEDQUEUE_H

#include "queue.h"
#include "../chainLinear/chainNode.h"
#include "myExceptions.h"
#include <sstream>

template<typename T>
class linkedQueue : public queue<T> {
public:
    explicit linkedQueue(int initialCapacity = 10) {
        queueFront = nullptr;
        queueSize = 0;
    }

    ~linkedQueue() override;

    bool empty() const override {
        return queueSize == 0;
    }

    int size() const override {
        return queueSize;
    }

    T &front() override {
        if (queueSize == 0) {
            throw queueEmpty();
        }
        return queueFront->element;
    }

    T &back() override {
        if (queueSize == 0) {
            throw queueEmpty();
        }

        return queueBack->element;
    }

    void pop() override;

    void push(const T &theElement) override;

private:
    chainNode<T> *queueFront;
    chainNode<T> *queueBack;
    int queueSize;
};

template<typename T>
linkedQueue<T>::~linkedQueue() {
    while (queueFront != nullptr) {
        chainNode<T> *nextNode = queueFront->next;
        delete queueFront;
        queueFront = nextNode;
    }
}

/**
 * 删除首元素
 * @tparam T
 */
template<typename T>
void linkedQueue<T>::pop() {
    if (queueFront == nullptr) {
        throw queueEmpty();
    }

    chainNode<T> *nextNode = queueFront->next;
    delete queueFront;
    queueFront = nextNode;
    queueSize--;
}

/**
 * 把元素theElement插到队尾
 * @tparam T
 * @param theElement
 */
template<typename T>
void linkedQueue<T>::push(const T &theElement) {

    // 申请新元素节点
    chainNode<T> *newNode = new chainNode<T>(theElement, nullptr);

    // 把新节点插到队尾
    if (queueSize == 0) {       // 队列空
        queueFront = newNode;
    } else {
        queueBack->next = newNode;      // 队列不空
    }

    queueBack = newNode;

    queueSize++;
}

#endif //DATASTRUCTURE_LINKEDQUEUE_H
