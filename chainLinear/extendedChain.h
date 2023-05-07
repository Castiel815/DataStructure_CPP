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
class extendedChain : public extendedLinearList<T>, public chain<T>{
protected:
    chainNode<T> *lastNode;
};


#endif //DATASTRUCTURE_EXTENDEDCHAIN_H
