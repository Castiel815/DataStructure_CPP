include_directories(../base)
include_directories(../chainLinear)

project(application)

add_executable(application main.cpp binsort1.cpp chainWithBinSort.cpp)
