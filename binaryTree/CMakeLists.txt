include_directories(../base)

project(binaryTree)

add_executable(binaryTree main.cpp
        binaryTreeNode.h
        binaryTree.h
        linkedBinaryTree.cpp
        linkedBinaryTree.h
        booster.h)
