//
// Created by CY815 on 2023/8/14.
//

#ifndef DATASTRUCTURE_WINNERTREE_H
#define DATASTRUCTURE_WINNERTREE_H

template<typename T>
class winnerTree {
public:
    virtual ~winnerTree() = default;

    virtual void initialize(T *thePlayer, int theNumberOfPlayers) = 0;  // 用数组thePlayer[1 : numberOfPlayers]生成赢者树

    virtual int winner() const = 0;         // 返回赢者的索引

    virtual void rePlay(int thePlayer) = 0;     // 在参赛者thePlayer的分数变化后重赛
};

#endif //DATASTRUCTURE_WINNERTREE_H
