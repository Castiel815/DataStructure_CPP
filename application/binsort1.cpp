//
// Created by CY815 on 2023/5/28.
//

#include <iostream>
#include "studentRecord.h"
#include "chain.h"
#include <stdexcept>

using namespace std;

/**
 * 按分数排序
 * @param theChain
 * @param range
 */
void binSort(chain<studentRecord> &theChain, int range) {

    // 对箱子初始化
    chain<studentRecord> *bin;
    bin = new chain<studentRecord>[range + 1];

    // 把学生记录从链表取出，然后分配到箱子里
    int numberOfElements = theChain.size();
    for (int i = 1; i <= numberOfElements; i++) {
        studentRecord x = theChain.get(0);
        theChain.erase(0);
        bin[x.score].insert(0, x);
    }

    // 从箱子中收集元素
    for (int j = range; j >= 0; --j) {
        while (!bin[j].empty()) {
            studentRecord x = bin[j].get(0);
            bin[j].erase(0);
            theChain.insert(0, x);
        }
    }

    delete[]bin;
}

void testBinSort() {
    studentRecord s{};
    chain<studentRecord> c;
    for (int i = 1; i <= 20; i++) {
        s.score = i / 2;
        s.name = new string(s.score, 'a');
        c.insert(0, s);
    }
    cout << "The unsorted chain is" << endl;
    cout << "  " << c << endl;
    binSort(c, 10);
    cout << "The sorted chain is" << endl;
    cout << "  " << c << endl;
}
