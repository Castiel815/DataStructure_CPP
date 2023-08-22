//
// Created by CY815 on 2023/8/16.
//

#ifndef DATASTRUCTURE_BSTREE_H
#define DATASTRUCTURE_BSTREE_H

#include "../dictionary/dictionary.h"

template<typename K, typename E>
class bsTree : public dictionary<K, E> {
public:
    virtual void ascend() = 0;  // 按关键字升序输出
};

#endif //DATASTRUCTURE_BSTREE_H
