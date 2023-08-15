include_directories(../base)

project(winnerTree)

add_executable(winnerTree main.cpp
        winnerTree.h
        completeWinnerTree.cpp
        completeWinnerTree.h
        player.h)
