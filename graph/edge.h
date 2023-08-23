//
// Created by CY815 on 2023/8/22.
//

#ifndef DATASTRUCTURE_EDGE_H
#define DATASTRUCTURE_EDGE_H

template<typename T>
class edge {
public:
    virtual ~edge() = default;

    virtual int vertex1() const = 0;

    virtual int vertex2() const = 0;

    virtual T weight() const = 0;
};

#endif //DATASTRUCTURE_EDGE_H
