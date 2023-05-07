include_directories(../base)

project(chainLinear)

add_executable(chainLinear main.cpp chainNode.h chain.cpp chain.h extendedChain.cpp extendedChain.h)
