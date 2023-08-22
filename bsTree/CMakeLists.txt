include_directories(../base)

project(bsTree)

add_executable(bsTree main.cpp
        bsTree.h
        indexedBSTree.h
        binarySearchTree.cpp
        binarySearchTree.h)
