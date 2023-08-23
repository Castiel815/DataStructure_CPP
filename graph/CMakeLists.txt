include_directories(../base)

project(graph)

add_executable(graph main.cpp
        edge.h
        graph.h
        vertexIterator.h
        binNode.h
        weightedEdge.h
        unionFindNode.h
        fastUnionFind.h)
