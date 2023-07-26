//
// Created by CY815 on 2023/7/25.
//

#ifndef DATASTRUCTURE_SORTEDCHAIN_H
#define DATASTRUCTURE_SORTEDCHAIN_H

#include <iostream>
#include "dictionary.h"
#include "pairNode.h"

template<typename K, typename E>
class sortedChain : public dictionary<K, E> {
public:
    sortedChain() {
        firstNode = nullptr;
        dSize = 0;
    }

    ~sortedChain() override;

    bool empty() const override { return dSize == 0; }

    int size() const override { return dSize; }

    std::pair<const K, E> *find(const K &theKey) const override;

    void erase(const K &theKey) override;

    void insert(const std::pair<const K, E> &thePair) override;

    void output(std::ostream &out) const;

protected:
    pairNode<K, E> *firstNode;
    int dSize;
};

template<typename K, typename E>
sortedChain<K, E>::~sortedChain() {
    while (firstNode != nullptr) {
        pairNode<K, E> *nextNode = firstNode->next;
        delete firstNode;
        firstNode = nextNode;
    }
}

/**
 * 返回匹配的数对的指针，如果不存在匹配的数对，则返回nullptr
 * @tparam K
 * @tparam E
 * @param theKey
 * @return
 */
template<typename K, typename E>
std::pair<const K, E> *sortedChain<K, E>::find(const K &theKey) const {
    pairNode<K, E> *currentMode = firstNode;

    // 搜索关键字为theKey的数对
    while (currentMode != nullptr && currentMode->element.first != theKey) {
        currentMode = currentMode->next;
    }

    // 判断是否匹配
    if (currentMode != nullptr && currentMode->element.first == theKey) {
        // 找到匹配数对
        return &currentMode->element;
    }

    // 无匹配的数对
    return nullptr;
}

/**
 * 往字典中插入thePair，覆盖已经存在的匹配的数对
 * @tparam K
 * @tparam E
 * @param thePair
 */
template<typename K, typename E>
void sortedChain<K, E>::insert(const std::pair<const K, E> &thePair) {
    pairNode<K, E> *p = firstNode, *tp = nullptr;

    // 移动指针tp，使thePair可以插在tp的后面
    while (p != nullptr && p->element.first < thePair.first) {
        tp = p;
        p = p->next;
    }

    // 检查是否有匹配的数对
    if (p != nullptr && p->element.first == thePair.first) {
        // 替换旧值
        p->element.second = thePair.second;
        return;
    }

    // 无匹配的数对，为thePair建立新节点
    pairNode<K, E> *newNode = new pairNode<K, E>(thePair, p);

    // 在tp之后插入新节点
    if (tp == nullptr) {
        firstNode = newNode;
    } else {
        tp->next = newNode;
    }

    dSize++;
}

/**
 * 删除关键字为theKey的数对
 * @tparam K
 * @tparam E
 * @param theKey
 */
template<typename K, typename E>
void sortedChain<K, E>::erase(const K &theKey) {
    pairNode<K, E> *p = firstNode, *tp = nullptr;

    // 搜索关键字为theKey的数对
    while (p != nullptr && p->element.first < theKey) {
        tp = p;
        p = p->next;
    }

    // 确定是否匹配
    // 找到一个匹配的数对
    if (p != nullptr && p->element.first == theKey) {
        // 从链表中删除p
        if (tp == nullptr) {
            firstNode = p->next;    // p是第一个节点
        } else {
            tp->next = p->next;
        }

        delete p;
        dSize--;
    }
}

template<typename K, typename E>
void sortedChain<K, E>::output(std::ostream &out) const {
    for (pairNode<K, E> *currentNode = firstNode;
         currentNode != nullptr; currentNode = currentNode->next) {
        out << currentNode->element.first << " "
            << currentNode->element.second << " ";
    }
}

template<typename K, typename E>
std::ostream &operator<<(std::ostream &out, const sortedChain<K, E> &x) {
    x.output(out);
    return out;
}

#endif //DATASTRUCTURE_SORTEDCHAIN_H
