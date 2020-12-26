cmake_minimum_required(VERSION 3.15)
project(practice)

set(CMAKE_CXX_STANDARD 14)
set(Boost_USE_STATIC_LIBS        ON) # only find static libs
set(Boost_USE_MULTITHREADED      ON)
set(Boost_INCLUDE_DIR C:/Users/anshu/Downloads/boost_1_75_0/boost_1_75_0/)

set(Boost_LIBRARY_DIR C:/Users/anshu/Downloads/boost_1_75_0/boost_1_75_0/stage/libs/)
find_package(Boost REQUIRED COMPONENTS thread)
IF (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIR})
endif()
include_directories(${Boost_INCLUDE_DIR})

add_executable(practice main.cpp graph-set.cpp transitive-closure.cpp dfs-iterative.cpp reinterpret-cast.cpp iterative-inorder.cpp prims-algorithm.cpp priority-queue.cpp perfect-sum.cpp weird-algo.cpp reverse-pint.cpp hour_glass.cpp perfect-sum-v1.cpp connected-components.cpp shortest-path.cpp maze.cpp topological-sort-v1.cpp single-source-shortest-path.cpp Dijkstras-shortest-path-algo.cpp priority-queue-v1.cpp dynamic-priority-queue.cpp multi-threading-basic.cpp)
if(WIN32)
    target_link_libraries(practice wsock32 ws2_32)
endif()
target_link_libraries(practice ${Boost_LIBRARIES})

