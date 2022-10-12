cmake_minimum_required(VERSION 3.14)
project(CleverAlgorithm)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE "Release")

find_package(Eigen3 REQUIRED NO_MODULE)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src SRCS)
list(APPEND LIB_SRCS ${SRCS})

add_library(${PROJECT_NAME} SHARED ${LIB_SRCS})

target_include_directories(${PROJECT_NAME}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME}
    Eigen3::Eigen
)
