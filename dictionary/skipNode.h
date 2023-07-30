//
// Created by CY815 on 2023/7/30.
//

#ifndef DATASTRUCTURE_SKIPNODE_H
#define DATASTRUCTURE_SKIPNODE_H

#include <utility>

template<typename K, typename E>
struct skipNode {
    using pairType = std::pair<const K, E>;
    pairType element;
    skipNode<K, E> **next;      // 指针数组

    skipNode(const pairType &thePair, int size) : element(thePair) {
        next = new skipNode<K, E> *[size];
    }
};

#endif //DATASTRUCTURE_SKIPNODE_H
