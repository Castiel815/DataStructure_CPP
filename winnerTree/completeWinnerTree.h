//
// Created by CY815 on 2023/8/14.
//

#ifndef DATASTRUCTURE_COMPLETEWINNERTREE_H
#define DATASTRUCTURE_COMPLETEWINNERTREE_H

#include <iostream>
#include "winnerTree.h"
#include "myExceptions.h"

template<typename T>
class completeWinnerTree : public winnerTree<T> {
public:
    completeWinnerTree(T *thePlayer, int theNumberOfPlayer) {
        tree = nullptr;
        initialize(thePlayer, theNumberOfPlayer);
    }

    ~completeWinnerTree() override { delete[] tree; }

    void initialize(T *thePlayer, int theNumberOfPlayers) override;

    int winner() const override {
        return tree[1];
    }

    int winner(int i) const {
        return (i < numberOfPlayers) ? tree[i] : 0;
    }

    void rePlay(int thePlayer) override;

    void output() const;

private:
    int lowExt;
    int offset;
    int *tree;
    int numberOfPlayers;
    T *players;

    void play(int p, int leftChild, int rightChild);
};

template<typename T>
void completeWinnerTree<T>::initialize(T *thePlayer, int theNumberOfPlayers) {
    int n = theNumberOfPlayers;
    if (n < 2) {
        throw illegalParameterValue("must have at least 2 players");
    }

    players = thePlayer;
    numberOfPlayers = n;
    delete[] tree;
    tree = new int[n];

    int i, s;
    for (s = 1; 2 * s <= n - 1; s += s);

    lowExt = 2 * (n - s);
    offset = 2 * s - 1;

    for (i = 2; i <= lowExt; i += 2) {
        play((offset + i) / 2, i - 1, i);
    }

    if (n % 2 == 1) {
        play(n / 2, tree[n - 1], lowExt + 1);
        i = lowExt + 3;
    } else
        i = lowExt + 2;

    for (; i <= n; i += 2) {
        play((i - lowExt + n - 1) / 2, i - 1, i);
    }
}

template<typename T>
void completeWinnerTree<T>::play(int p, int leftChild, int rightChild) {
    tree[p] = (players[leftChild] <= players[rightChild]) ? leftChild : rightChild;

    while (p % 2 == 1 && p > 1) {
        tree[p / 2] = (players[tree[p - 1]] <= players[tree[p]]) ? tree[p - 1] : tree[p];
        p /= 2;
    }
}

template<typename T>
void completeWinnerTree<T>::rePlay(int thePlayer) {
    int n = numberOfPlayers;
    if (thePlayer <= 0 || thePlayer > n) {
        throw illegalParameterValue("Player index is illegal");
    }

    int matchNode,
            leftChild,
            rightChild;

    if (thePlayer <= lowExt) {
        matchNode = (offset + thePlayer) / 2;
        leftChild = 2 * matchNode - offset;
        rightChild = leftChild + 1;
    } else {
        matchNode = (thePlayer - lowExt + n - 1) / 2;
        if (2 * matchNode == n - 1) {
            leftChild = tree[2 * matchNode];
            rightChild = thePlayer;
        } else {
            leftChild = 2 * matchNode - n + 1 + lowExt;
            rightChild = leftChild + 1;
        }
    }

    tree[matchNode] = (players[leftChild] <= players[rightChild]) ? leftChild : rightChild;

    if (matchNode == n - 1 && n % 2 == 1) {
        matchNode /= 2;
        tree[matchNode] = (players[tree[n - 1]] <= players[lowExt + 1]) ? tree[n - 1] : lowExt + 1;
    }

    matchNode /= 2;
    for (; matchNode >= 1; matchNode /= 2) {
        tree[matchNode] = (players[tree[2 * matchNode]] <= players[tree[2 * matchNode + 1]]) ? tree[2 * matchNode] : tree[
                2 * matchNode + 1];
    }
}

template<typename T>
void completeWinnerTree<T>::output() const {
    std::cout << "number of players = " << numberOfPlayers
              << " lowExt = " << lowExt
              << " offset = " << offset << std::endl;
    std::cout << "complete winner tree pointers are" << std::endl;
    for (int i = 1; i < numberOfPlayers; ++i) {
        std::cout << tree[i] << ' ';
    }
    std::cout << std::endl;
}

#endif //DATASTRUCTURE_COMPLETEWINNERTREE_H
