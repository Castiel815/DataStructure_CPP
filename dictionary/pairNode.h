//
// Created by CY815 on 2023/7/25.
//

#ifndef DATASTRUCTURE_PAIRNODE_H
#define DATASTRUCTURE_PAIRNODE_H

#include <utility>

template<typename K, typename E>
struct pairNode {
    using pairType = std::pair<const K, E>;
    pairType element;
    pairNode<K, E> *next;

    explicit pairNode(const pairType &thePair) : element(thePair) {}

    pairNode(const pairType &thePair, pairNode<K, E> *theNext) : element(thePair) { next = theNext; }
};

#endif //DATASTRUCTURE_PAIRNODE_H
