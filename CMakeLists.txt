cmake_minimum_required(VERSION 3.29)

set(CMAKE_CXX_STANDARD 17)

set(OPTION 1)

file(GLOB LKTPSOURCES "./TaskQueue/src/*.cpp" "./ThreadPool/src/*.cpp")
file(GLOB LKTPHEADERS "./TaskQueue/include/*.h" "./ThreadPool/include/*.h")

if(OPTION EQUAL 1)
    project(lkthreadpool)
    add_executable(lkthreadpool main.cpp ${LKTPSOURCES} ${LKTPHEADERS})
    target_include_directories(lkthreadpool PRIVATE ./ThreadPool/include)
    target_include_directories(lkthreadpool PRIVATE ./TaskQueue/include)
    target_link_libraries(lkthreadpool PRIVATE pthread)
elseif (OPTION EQUAL 2)
    project(lkthreadpool)
    add_library(lkthreadpool SHARED ${LKTPSOURCES} ${LKTPHEADERS}
            ThreadPool/include/ThreadPoolManager.h)
    target_include_directories(lkthreadpool PRIVATE ./ThreadPool/include ./TaskQueue/include)
elseif (OPTION EQUAL 3)
    project(lkthreadpooluselib)
    add_executable(lkthreadpooluselib main.cpp)
    target_include_directories(lkthreadpooluselib PRIVATE ./ThreadPool/include)
    target_include_directories(lkthreadpooluselib PRIVATE ./TaskQueue/include)
    target_link_directories(lkthreadpooluselib PRIVATE ./cmake-build-debug)
    target_link_libraries(lkthreadpooluselib lkthreadpool)
    target_link_libraries(lkthreadpooluselib pthread)
endif ()