//
// Created by CY815 on 2023/8/22.
//

#ifndef DATASTRUCTURE_UNIONFINDNODE_H
#define DATASTRUCTURE_UNIONFINDNODE_H

struct unionFindNode {
    int parent;  // if true then tree weight
    // otherwise pointer to parent in tree
    bool root;   // true iff root

    unionFindNode() {
        parent = 1;
        root = true;
    }
};

#endif //DATASTRUCTURE_UNIONFINDNODE_H
