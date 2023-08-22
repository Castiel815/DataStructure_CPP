//
// Created by CY815 on 2023/8/22.
//

#ifndef DATASTRUCTURE_MINPRIORITYQUEUE_H
#define DATASTRUCTURE_MINPRIORITYQUEUE_H

template<typename T>
class minPriorityQueue {
public:
    virtual ~minPriorityQueue() = default;

    virtual bool empty() const = 0;

    // return true iff queue is empty
    virtual int size() const = 0;

    // return number of elements in queue
    virtual const T &top() = 0;

    // return reference to the min element
    virtual void pop() = 0;

    // remove the top element
    virtual void push(const T &theElement) = 0;
    // add theElement to the queue
};

#endif //DATASTRUCTURE_MINPRIORITYQUEUE_H
