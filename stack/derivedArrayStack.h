//
// Created by CY815 on 2023/7/17.
//

#ifndef DATASTRUCTURE_DERIVEDARRAYSTACK_H
#define DATASTRUCTURE_DERIVEDARRAYSTACK_H

#include "../linear/arrayList.h"
#include "stack.h"
#include "myExceptions.h"

template<typename T>
class derivedArrayStack : private arrayList<T>, public stack<T> {
public:
    explicit derivedArrayStack(int initialCapacity = 10) : arrayList<T>(initialCapacity) {}

    bool empty() const override {
        return arrayList<T>::empty();
    }

    int size() const override {
        return arrayList<T>::size();
    }

    T &top() override {
        if (arrayList<T>::empty()) {
            throw stackEmpty();
        }

        return arrayList<T>::get(arrayList<T>::size() - 1);
    }

    void pop() override {
        if (arrayList<T>::empty()) {
            throw stackEmpty();
        }
        arrayList<T>::erase(arrayList<T>::size() - 1);
    }

    void push(const T &theElement) override {
        arrayList<T>::insert(arrayList<T>::size(), theElement);
    }
};


#endif //DATASTRUCTURE_DERIVEDARRAYSTACK_H
