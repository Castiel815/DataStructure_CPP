//
// Created by CY815 on 2023/8/14.
//

#include "completeWinnerTree.h"
#include "player.h"

void testCompleteWinnerTree() {
    using namespace std;

    int n;
    cout << "Enter number of players, >= 2" << endl;
    cin >> n;
    if (n < 2) {
        cout << "Bad input" << endl;
        exit(1);
    }


    player *thePlayer = new player[n + 1];

    cout << "Enter players values" << endl;
    for (int i = 1; i <= n; i++) {
        cin >> thePlayer[i].key;
        thePlayer[i].id = i;
    }

    completeWinnerTree<player> *w =
            new completeWinnerTree<player>(thePlayer, n);
    cout << "The winner tree is" << endl;
    w->output();

    thePlayer[2].key = 0;
    w->rePlay(2);
    cout << "Changed players 2 to zero, new tree is" << endl;
    w->output();

    thePlayer[3].key = -1;
    w->rePlay(3);
    cout << "Changed players 3 to -1, new tree is" << endl;
    w->output();

    thePlayer[7].key = 2;
    w->rePlay(7);
    cout << "Changed players 7 to 2, new tree is" << endl;
    w->output();
}
