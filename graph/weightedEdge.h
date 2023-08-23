//
// Created by CY815 on 2023/8/22.
//

#ifndef DATASTRUCTURE_WEIGHTEDEDGE_H
#define DATASTRUCTURE_WEIGHTEDEDGE_H

#include "edge.h"
#include <iostream>

template<typename T>
class weightedEdge : public edge<T> {
public:
    weightedEdge() {
        v1 = 0;
        v2 = 0;
    };

    weightedEdge(int theV1, int theV2, T theW) {
        v1 = theV1;
        v2 = theV2;
        w = theW;
    }

    ~weightedEdge() override = default;

    int vertex1() const override { return v1; }

    int vertex2() const override { return v2; }

    T weight() const override { return w; }

    operator T() const { return w; }

    void output(std::ostream &out) const {// Put the edge into the stream out.
        out << "(" << v1 << ", " << v2 << ", " << w << ")";
    }

    friend std::ostream &operator<<(std::ostream &out, const weightedEdge<T> &x) {
        x.output(out);
        return out;
    }

private:
    int v1,
            v2;
    T w;
};

#endif //DATASTRUCTURE_WEIGHTEDEDGE_H
