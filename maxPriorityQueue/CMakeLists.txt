include_directories(../base)

project(maxPriorityQueue)

add_executable(maxPriorityQueue main.cpp
        maxPriorityQueue.h
        maxHeap.cpp
        maxHeap.h
        maxHblt.cpp
        maxHblt.h
        minPriorityQueue.h
        minHeap.cpp
        minHeap.h)
