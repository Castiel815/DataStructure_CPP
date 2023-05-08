//
// Created by CY815 on 2023/5/7.
//

#ifndef DATASTRUCTURE_EXTENDEDCHAIN_H
#define DATASTRUCTURE_EXTENDEDCHAIN_H

#include <iostream>
#include <sstream>
#include <string>
#include "chain.h"
#include "extendedLinearList.h"

template<typename T>
class extendedChain : public extendedLinearList<T>, public chain<T> {
public:
    explicit extendedChain(int initialCapacity = 10) : chain<T>(initialCapacity) {}

    extendedChain(const extendedChain<T> &c) : chain<T>(c) {}

    bool empty() const { return chain<T>::listSize == 0; }

    int size() const { return chain<T>::listSize; }

    T &get(int theIndex) const {
        return chain<T>::get(theIndex);
    }

    int indexOf(const T &theElement) const {
        return chain<T>::indexOf(theElement);
    }

    void erase(int theIndex);

    void insert(int theIndex, const T &theElement);

    void clear() {
        while (chain<T>::firstNode != nullptr) {
            chainNode<T> *nextNode = chain<T>::firstNode->next;
            delete chain<T>::firstNode;
            chain<T>::firstNode = nextNode;
        }

        chain<T>::listSize = 0;
    }

    void push_back(const T &theElement);

    void output(std::ostream &out) const {
        chain<T>::output(out);
    }

    void zero() {
        chain<T>::firstNode = nullptr;
        chain<T>::listSize = 0;
    }

protected:
    chainNode<T> *lastNode;
};

template<typename T>
void extendedChain<T>::erase(int theIndex) {
    chain<T>::checkIndex(theIndex);

    chainNode<T> *deleteNode;
    if (theIndex == 0) {
        deleteNode = chain<T>::firstNode;
        chain<T>::firstNode = chain<T>::firstNode->next;
    } else {
        chainNode<T> *p = chain<T>::firstNode;
        for (int i = 0; i < theIndex - 1; ++i)
            p = p->next;

        deleteNode = p->next;
        p->next = p->next->next;
        if (deleteNode == lastNode) {
            lastNode = p;
        }
    }

    chain<T>::listSize--;
    delete deleteNode;
}

template<typename T>
void extendedChain<T>::insert(int theIndex, const T &theElement) {
    if (theIndex < 0 || theIndex > chain<T>::listSize) {
        std::ostringstream s;
        s << "index = " << theIndex << " size = " << chain<T>::listSize;
        throw std::invalid_argument(s.str());
    }

    if (theIndex == 0) {
        chain<T>::firstNode = new chainNode<T>(theElement, chain<T>::firstNode);
        if (chain<T>::listSize == 0)
            lastNode = chain<T>::firstNode;
    } else {
        chainNode<T> *p = chain<T>::firstNode;
        for (int i = 0; i < theIndex - 1; ++i) {
            p = p->next;
        }

        p->next = new chainNode<T>(theElement, p->next);
        if (chain<T>::listSize == theIndex)
            lastNode = p->next;
    }

    chain<T>::listSize++;
}

template<typename T>
void extendedChain<T>::push_back(const T &theElement) {
    auto *newNode = new chainNode<T>(theElement, nullptr);
    if (chain<T>::firstNode == nullptr) {
        chain<T>::firstNode = lastNode = newNode;
    } else {
        lastNode->next = newNode;
        lastNode = newNode;
    }
    chain<T>::listSize++;
}

#endif //DATASTRUCTURE_EXTENDEDCHAIN_H
