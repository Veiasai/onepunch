PROJECT(CTP)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -std=c++14")
set(CTP_LIB_VERSION "v_info_6.3.15_P2_20190403_exec_6.3.15_20190220")

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

add_subdirectory(CTP_API)

add_subdirectory(simulation)

AUX_SOURCE_DIRECTORY(. DIR_SRCS)

ADD_EXECUTABLE(ctp ${DIR_SRCS})

TARGET_LINK_LIBRARIES(ctp ctp_exec_lib_${CTP_LIB_VERSION} ctp_info_lib_${CTP_LIB_VERSION})

add_subdirectory(config)

target_link_libraries(ctp simulation)
target_link_libraries(ctp libconfig.so)
target_link_libraries(ctp libconfig++.so)