//
// Created by CY815 on 2023/8/22.
//

#ifndef DATASTRUCTURE_VERTEXITERATOR_H
#define DATASTRUCTURE_VERTEXITERATOR_H

template<typename T>
class vertexIterator {
public:
    virtual ~vertexIterator() = default;

    virtual int next() = 0;

    virtual int next(T &) = 0;
};

#endif //DATASTRUCTURE_VERTEXITERATOR_H
