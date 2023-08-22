//
// Created by CY815 on 2023/8/16.
//

#ifndef DATASTRUCTURE_INDEXEDBSTREE_H
#define DATASTRUCTURE_INDEXEDBSTREE_H

#include "bsTree.h"

template<typename K, typename E>
class indexedBSTree : public bsTree<K, E> {
public:
    virtual std::pair<const K, E> *get(int) const = 0;  // 根据给定的索引，返回其数对的指针

    virtual void deletePair(int) = 0;   // 根据给定的索引，删除其数对
};

#endif //DATASTRUCTURE_INDEXEDBSTREE_H
