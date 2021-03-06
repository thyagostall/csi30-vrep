cmake_minimum_required(VERSION 2.6)
project(cppremoteapi)

INCLUDE(FindPkgConfig)



IF(CMAKE_COMPILER_IS_GNUCC)
SET(CMAKE_CXX_FLAGS
"${CMAKE_CXX_FLAGS} -Wall -std=c++11 -DBUILD_SHARED_LIBS=OFF -lrt")
ENDIF(CMAKE_COMPILER_IS_GNUCC)

# definicoes da remoteAPI para CPP
add_definitions(-DNON_MATLAB_PARSING)
add_definitions(-DMAX_EXT_API_CONNECTIONS=255)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCES
        remoteApi/extApi.c
        remoteApi/extApiPlatform.c
        DepthFirstSearch.cpp
        State.cpp
        Path.cpp
        AStarSearch.cpp
        GeneticAlgorithm.cpp
        Map.cpp
        )

set(HEADERS
        remoteApi/extApi.h
        remoteApi/extApiInternal.h
        remoteApi/extApiPlatform.h
        include/v_repConst.h
        include/v_repLib.h
        DepthFirstSearch.hpp
        State.hpp
        Path.hpp
        PathFinder.hpp
        AStarSearch.hpp
        GeneticAlgorithm.hpp
        Map.hpp
        )

include_directories("include/")
include_directories("remoteApi/")


find_package(Threads REQUIRED)

add_executable(cppremoteapi 
               main.cpp 
               ${SOURCES})

if(THREADS_HAVE_PTHREAD_ARG)
  target_compile_options(cppremoteapi PUBLIC "-pthread")
endif()
if(CMAKE_THREAD_LIBS_INIT)
  target_link_libraries(cppremoteapi "${CMAKE_THREAD_LIBS_INIT}")
endif()

TARGET_LINK_LIBRARIES(cppremoteapi ${Boost_LIBRARIES} -lm)
target_link_libraries (cppremoteapi ${CMAKE_THREAD_LIBS_INIT})

install(TARGETS cppremoteapi RUNTIME DESTINATION bin)
