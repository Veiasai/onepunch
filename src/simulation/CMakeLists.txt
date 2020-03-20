PROJECT(SIMULATION)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -std=c++14")
set(CMAKE_BUILD_TYPE "Debug")

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)


AUX_SOURCE_DIRECTORY(. DIR)

set(simulation ${DIR})

add_library(simulation ${simulation})