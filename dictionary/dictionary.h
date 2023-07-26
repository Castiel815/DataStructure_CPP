//
// Created by CY815 on 2023/7/25.
//

#ifndef DATASTRUCTURE_DICTIONARY_H
#define DATASTRUCTURE_DICTIONARY_H

#include <utility>

template<typename K, typename E>
class dictionary {
public:
    virtual ~dictionary() = default;

    virtual bool empty() const = 0;

    virtual int size() const = 0;

    virtual std::pair<const K, E> *find(const K &) const = 0;

    virtual void erase(const K &) = 0;

    virtual void insert(const std::pair<const K, E> &) = 0;
};

#endif //DATASTRUCTURE_DICTIONARY_H
