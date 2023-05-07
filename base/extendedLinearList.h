//
// Created by CY815 on 2023/5/7.
//

#ifndef DATASTRUCTURE_EXTENDEDLINEARLIST_H
#define DATASTRUCTURE_EXTENDEDLINEARLIST_H

#include "linearList.h"

template<typename T>
class extendedLinearList : linearList<T> {
public:
    virtual ~extendedLinearList() {}

    virtual void clear() = 0;

    virtual void push_back(const T &theElement) = 0;
};

#endif //DATASTRUCTURE_EXTENDEDLINEARLIST_H
