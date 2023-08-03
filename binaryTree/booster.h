//
// Created by CY815 on 2023/7/31.
//

#ifndef DATASTRUCTURE_BOOSTER_H
#define DATASTRUCTURE_BOOSTER_H

#include <iostream>

struct booster {
    int degradeToLeaf,          // 到达叶子时的衰减量
            degradeFromParent;  // 从父节点出发的衰减量
    bool boosterHere;           // 当且仅当放置了放大器时，值为真

    void output(std::ostream &out) const {
        out << boosterHere << ' ' << degradeToLeaf << ' '
            << degradeFromParent << ' ';
    }

    // 重载操作符
    friend std::ostream &operator<<(std::ostream &out, booster x) {
        x.output(out);
        return out;
    }
};




#endif //DATASTRUCTURE_BOOSTER_H
