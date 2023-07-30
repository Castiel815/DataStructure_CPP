//
// Created by CY815 on 2023/7/30.
//

#ifndef DATASTRUCTURE_SKIPLIST_H
#define DATASTRUCTURE_SKIPLIST_H

#include <iostream>
#include <cmath>
#include <sstream>
#include <string>
#include "dictionary.h"
#include "skipNode.h"
#include "myExceptions.h"

template<typename K, typename E>
class skipList : public dictionary<K, E> {
public:
    explicit skipList(K largeKey, int maxPairs = 10000, float prob = 0.5);

    ~skipList() override;

    bool empty() const override { return dSize == 0; }

    int size() const override { return dSize; }

    std::pair<const K, E> *find(const K &theKey) const override;

    void erase(const K &theKey) override;

    void insert(const std::pair<const K, E> &thePair) override;

    void output(std::ostream &out) const;

protected:
    float cutOff;           // 用来确定层数
    int level() const;

    int levels;             // 当前最大的飞空链表
    int dSize;              // 字典的数对个数
    int maxLevel;           // 允许的最大链表层数
    K tailKey;              // 最大关键字
    skipNode<K, E> *search(const K &theKey) const;

    skipNode<K, E> *headerNode;     // 头节点指针
    skipNode<K, E> *tailNode;       // 尾节点指针
    skipNode<K, E> **last;          // last[i]表示i层的最后节点
};

/**
 * 构造函数，关键字小于largeKey且数对个数size最多为maxPairs。0 < prob < 1
 * @tparam K
 * @tparam E
 * @param largeKey
 * @param maxPairs
 * @param prob
 */
template<typename K, typename E>
skipList<K, E>::skipList(K largeKey, int maxPairs, float prob) {
    cutOff = prob * RAND_MAX;
    maxLevel = (int) ceil(logf((float) maxPairs) / logf(1 / prob)) - 1;
    levels = 0;         // 初始化级数
    dSize = 0;
    tailKey = largeKey;

    // 生成头节点、尾节点和数组last
    std::pair<K, E> tailPair;
    tailPair.first = tailKey;
    headerNode = new skipNode<K, E>(tailPair, maxLevel + 1);
    tailNode = new skipNode<K, E>(tailPair, 0);
    last = new skipNode<K, E> *[maxLevel + 1];

    // 链表为空时，任意级链表中的头节点都指向尾节点
    for (int i = 0; i <= maxLevel; ++i) {
        headerNode->next[i] = tailNode;
    }
}

template<typename K, typename E>
skipList<K, E>::~skipList() {
    skipNode<K, E> *nextNode;

    while (headerNode != tailNode) {
        nextNode = headerNode->next[0];
        delete headerNode;
        headerNode = nextNode;
    }
    delete tailNode;

    delete[] last;
}

/**
 * 返回匹配的数对的指针，如果没有匹配的数对，返回nullptr
 * @tparam K
 * @tparam E
 * @param theKey
 * @return
 */
template<typename K, typename E>
std::pair<const K, E> *skipList<K, E>::find(const K &theKey) const {
    if (theKey >= tailKey) {
        return nullptr;         // 没有可能的匹配的数对
    }

    // 位置beforeNode是关键字为theKey的节点之前最右边的位置
    skipNode<K, E> *beforeNode = headerNode;
    for (int i = levels; i >= 0; --i) {         // 从上级链表到下级链表
        // 跟踪i级链表指针
        while (beforeNode->next[i]->element.first < theKey) {
            beforeNode = beforeNode->next[i];
        }
    }

    // 检查下一个节点的关键字是否是theKey
    if (beforeNode->next[0]->element.first == theKey) {
        return &beforeNode->next[0]->element;
    }

    return nullptr;     // 无匹配的数对
}

/**
 * 级的分配方法，返回一个表示链表级的随机数这个数不大于maxLevel
 * @tparam K
 * @tparam E
 * @return
 */
template<typename K, typename E>
int skipList<K, E>::level() const {
    int lev = 0;
    while (rand() <= cutOff) {
        lev++;
    }

    return (lev <= maxLevel) ? lev : maxLevel;
}

/**
 * 搜索关键字theKey，把每一级链表中要查看的最后一个节点存储在数组last中，返回包含关键字theKey的节点
 * @tparam K
 * @tparam E
 * @param theKey
 * @return
 */
template<typename K, typename E>
skipNode<K, E> *skipList<K, E>::search(const K &theKey) const {
    // 位置beforeNode是关键字为theKey的节点之前最右边的位置
    skipNode<K, E> *beforeNode = headerNode;
    for (int i = levels; i >= 0; --i) {
        while (beforeNode->next[i]->element.first < theKey) {
            beforeNode = beforeNode->next[i];
        }
        last[i] = beforeNode;       // 最后一级链表i的节点
    }

    return beforeNode->next[0];
}

/**
 * 把数对thePair插入字典，覆盖其关键字相同的已存在的数对
 * @tparam K
 * @tparam E
 * @param thePair
 */
template<typename K, typename E>
void skipList<K, E>::insert(const std::pair<const K, E> &thePair) {
    // 关键字太大
    if (thePair.first >= tailKey) {
        std::ostringstream s;
        s << "Key = " << thePair.first << " Must be < 0 " << tailKey;
        throw illegalParameterValue(s.str());
    }

    // 查看关键字为theKey的数对是否已经存在
    skipNode<K, E> *theNode = search(thePair.first);
    if (theNode->element.first == thePair.first) {      // 若存在，则更新该数对的值
        theNode->element.second = thePair.second;
        return;
    }

    // 若不存在，则确定新节点所在的级链表
    int theLevel = level();     // 新节点的级
    // 使级theLevel为 <= levels + 1
    if (theLevel > levels) {
        theLevel = ++levels;
        last[theLevel] = headerNode;
    }

    // 在节点theNode之后插入新节点
    skipNode<K, E> *newNode = new skipNode<K, E>(thePair, theLevel + 1);
    for (int i = 0; i <= theLevel; ++i) {
        // 插入i级链表
        newNode->next[i] = last[i]->next[i];
        last[i]->next[i] = newNode;
    }

    dSize++;
}

/**
 * 删除关键字等于theKey的数对
 * @tparam K
 * @tparam E
 * @param theKey
 */
template<typename K, typename E>
void skipList<K, E>::erase(const K &theKey) {
    if (theKey >= tailKey) {        // 关键字太大
        return;
    }

    // 查看是否有匹配的数对
    skipNode<K, E> *theNode = search(theKey);
    if (theNode->element.first != theKey) {     // 不存在
        return;
    }

    // 从跳表中删除节点
    for (int i = 0; i <= levels && last[i]->next[i] == theNode; ++i) {
        last[i]->next[i] = theNode->next[i];
    }

    // 更新链表级
    while (levels > 0 && headerNode->next[levels] == tailNode) {
        levels--;
    }

    delete theNode;
    dSize--;
}

template<typename K, typename E>
void skipList<K, E>::output(std::ostream &out) const {
    for (skipNode<K, E> *currentNode = headerNode->next[0];
         currentNode != tailNode;
         currentNode = currentNode->next[0]) {
        out << currentNode->element.first << " "
            << currentNode->element.second << " ";
    }
}

template<typename K, typename E>
std::ostream &operator<<(std::ostream &out, const skipList<K, E> &x) {
    x.output(out);
    return out;
}

#endif //DATASTRUCTURE_SKIPLIST_H
