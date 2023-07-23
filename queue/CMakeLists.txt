include_directories(../base)

project(queue)

add_executable(queue main.cpp queue.h arrayQueue.cpp arrayQueue.h linkedQueue.cpp linkedQueue.h)
