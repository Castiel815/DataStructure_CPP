include_directories(../base)

project(stack)

add_executable(stack main.cpp stack.h derivedArrayStack.cpp derivedArrayStack.h arrayStack.cpp arrayStack.h derivedLinkedStack.cpp derivedLinkedStack.h)
