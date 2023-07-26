include_directories(../base)

project(dictionary)

add_executable(dictionary main.cpp pairNode.h dictionary.h sortedChain.cpp sortedChain.h)
