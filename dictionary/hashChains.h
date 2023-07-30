//
// Created by CY815 on 2023/7/30.
//

#ifndef DATASTRUCTURE_HASHCHAINS_H
#define DATASTRUCTURE_HASHCHAINS_H

#include "hash.h"
#include "dictionary.h"
#include "sortedChain.h"

template<typename K, typename E>
class hashChains : public dictionary<K, E> {
public:
    explicit hashChains(int theDivisor = 11) {
        divisor = theDivisor;
        dSize = 0;

        table = new sortedChain<K, E>[divisor];
    }

    ~hashChains() override {
        delete[] table;
        table = nullptr;
    }

    bool empty() const override { return dSize == 0; }

    int size() const override { return dSize; }

    std::pair<const K, E> *find(const K &theKey) const override {
        return table[hash(theKey) % divisor].find(theKey);
    }

    void insert(const std::pair<const K, E> &thePair) override {
        int homeBucket = (int) hash(thePair.first) % divisor;
        int homeSize = table[homeBucket].size();
        table[homeBucket].insert(thePair);
        if (table[homeBucket].size() > homeSize) {
            dSize++;
        }
    }

    void erase(const K &theKey) override {
        table[hash(theKey) % divisor].erase(theKey);
    }

    void output(std::ostream &out) const {
        for (int i = 0; i < divisor; ++i) {
            if (table[i].size() == 0) {
                out << "NULL" << std::endl;
            } else {
                out << table[i] << std::endl;
            }
        }
    }

protected:
    sortedChain<K, E> *table;
    hash<K> hash;
    int dSize;
    int divisor;
};

template<typename K, typename E>
std::ostream &operator<<(std::ostream &out, const hashChains<K, E> &x) {
    x.output(out);
    return out;
}

#endif //DATASTRUCTURE_HASHCHAINS_H
