//
// Created by CY815 on 2023/7/30.
//

#ifndef DATASTRUCTURE_HASHTABLE_H
#define DATASTRUCTURE_HASHTABLE_H

#include "hash.h"
#include "myExceptions.h"

template<typename K, typename E>
class hashTable {
public:
    explicit hashTable(int theDivisor = 11);

    virtual ~hashTable() {
        delete[]table;
        table = nullptr;
    }

    bool empty() const { return dSize == 0; }

    int size() const { return dSize; }

    std::pair<const K, E> *find(const K &theKey) const;

    void insert(const std::pair<const K, E> &thePair);

    void output(std::ostream &out) const;

protected:
    int search(const K &theKey) const;

    std::pair<const K, E> **table;      // 散列表
    hash<K> hash;                       // 把类型K映射到一个非整数
    int dSize;                          // 字典中数对个数
    int divisor;                        // 散列函数除数
};

/**
 * 构造函数
 * @tparam K
 * @tparam E
 * @param theDivisor
 */
template<typename K, typename E>
hashTable<K, E>::hashTable(int theDivisor) {
    divisor = theDivisor;
    dSize = 0;

    // 分配和初始化散列表数组
    table = new std::pair<const K, E> *[divisor];
    for (int i = 0; i < divisor; ++i) {
        table[i] = nullptr;
    }
}

/**
 * 搜索一个公开地址散列表，查找关键字为theKey的数对。如果匹配的数对存在，返回它的位置，否则，如果
 * 散列表不满，则返回关键字为theKey的数对可以插入的位置
 * @tparam K
 * @tparam E
 * @param theKey
 * @return
 */
template<typename K, typename E>
int hashTable<K, E>::search(const K &theKey) const {
    int i = (int) hash(theKey) % divisor;        // 起始桶
    int j = i;                                  // 从起始桶开始
    do {
        if (table[j] == nullptr || table[j]->first == theKey) {
            return j;
        }
        j = (j + 1) % divisor;                  // 下一个桶
    } while (j != i);                           // 是否返回到起始桶

    return j;                                   // 表满
}

/**
 * 返回匹配数对的指针，如果匹配数对不存在，返回nullptr
 * @tparam K
 * @tparam E
 * @param theKey
 * @return
 */
template<typename K, typename E>
std::pair<const K, E> *hashTable<K, E>::find(const K &theKey) const {
    // 搜索散列表
    int b = search(theKey);

    // 判断table[b]是否是匹配数对
    if (table[b] == nullptr || table[b]->first != theKey) {
        return nullptr;     // 没有找到
    }

    return table[b];    // 找到匹配数对
}

/**
 * 把数对thePair插入字典，若存在关键字相同的数对，则覆盖
 * 若表满，则抛出异常
 * @tparam K
 * @tparam E
 * @param thePair
 */
template<typename K, typename E>
void hashTable<K, E>::insert(const std::pair<const K, E> &thePair) {
    // 搜索散列表，查找匹配的数对
    int b = search(thePair.first);

    // 检查匹配的数对是否存在
    if (table[b] == nullptr) {
        // 没有匹配的数对，而且表不满
        table[b] = new std::pair<const K, E>(thePair);
        dSize++;
    } else {  // 检查是否有重复的关键字数对或是否表满
        if (table[b]->first == thePair.first) {
            // 有重复的关键字数对，修改table[b].second
            table[b]->second = thePair.second;
        } else {  // 表满
            throw hashTableFull();
        }
    }
}

template<typename K, typename E>
void hashTable<K, E>::output(std::ostream &out) const {
    for (int i = 0; i < divisor; ++i) {
        if (table[i] == nullptr) {
            out << "NULL" << std::endl;
        } else {
            out << table[i]->first << " "
                << table[i]->second << std::endl;
        }
    }
}

template<typename K, typename E>
std::ostream &operator<<(std::ostream &out, const hashTable<K, E> &x) {
    x.output(out);
    return out;
}

#endif //DATASTRUCTURE_HASHTABLE_H
