//
// Created by CY815 on 2023/7/18.
//

#ifndef DATASTRUCTURE_DERIVEDLINKEDSTACK_H
#define DATASTRUCTURE_DERIVEDLINKEDSTACK_H

#include "../chainLinear/chain.h"
#include "stack.h"
#include "myExceptions.h"

template<typename T>
class derivedLinkedStack : private chain<T>, public stack<T> {
public:
    explicit derivedLinkedStack(int initialCapacity = 10) : chain<T>(initialCapacity) {}

    bool empty() const override { return chain<T>::empty(); }

    int size() const override { return chain<T>::size(); }

    T &top() override {
        if (chain<T>::empty()) {
            throw stackEmpty();
        }
        return chain<T>::get(0);
    }

    void pop() override {
        if (chain<T>::empty()) {
            throw stackEmpty();
        }
        chain<T>::erase(0);
    }

    void push(const T &theElement) override {
        chain<T>::insert(0, theElement);
    }
};


#endif //DATASTRUCTURE_DERIVEDLINKEDSTACK_H
