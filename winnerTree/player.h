//
// Created by CY815 on 2023/8/15.
//

#ifndef DATASTRUCTURE_PLAYER_H
#define DATASTRUCTURE_PLAYER_H

struct player {
    int id, key;

    explicit operator int() const { return key; }

    bool operator<=(const player &player) const {
        return key <= player.key;
    }
};

#endif //DATASTRUCTURE_PLAYER_H
