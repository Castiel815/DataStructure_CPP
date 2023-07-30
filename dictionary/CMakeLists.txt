include_directories(../base)

project(dictionary)

add_executable(dictionary main.cpp pairNode.h dictionary.h sortedChain.cpp sortedChain.h
        skipNode.h
        skipList.cpp
        skipList.h
        hash.h
        hashTable.cpp
        hashTable.h)
