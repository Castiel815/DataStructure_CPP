//
// Created by CY815 on 2023/5/28.
//
#include <iostream>
#include "linearList.h"
#include "chainWithBinSort.h"

using namespace std;

void testChainWithBinSort() {
    studentRecord s{};
    chainWithBinSort<studentRecord> theChain;
    for (int i = 1; i <= 20; i++) {
        s.score = i / 2;
        s.name = new string(s.score, 'a');
        theChain.insert(0, s);
    }
    cout << "The unsorted chain is" << endl;
    cout << "  " << theChain << endl;
    theChain.binSort(10);
    cout << "The sorted chain is" << endl;
    cout << "  " << theChain << endl;
}
