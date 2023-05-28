//
// Created by CY815 on 2023/5/28.
//

#ifndef DATASTRUCTURE_STUDENTRECORD_H
#define DATASTRUCTURE_STUDENTRECORD_H

#include <string>
#include <iostream>

struct studentRecord {
    int score;
    std::string *name;

    int operator!=(studentRecord x) const {
        return (score != x.score || name != x.name);
    }

    // 从studentRecord到int的类型转换
    operator int() const {
        return score;
    }

    friend std::ostream &operator<<(std::ostream &out, const studentRecord &x){
        out << x.score << ' ' << *x.name << std::endl;
        return out;
    }
};

//std::ostream &operator<<(std::ostream &out, const studentRecord &x) {
//    out << x.score << ' ' << *x.name << std::endl;
//    return out;
//}

#endif //DATASTRUCTURE_STUDENTRECORD_H
