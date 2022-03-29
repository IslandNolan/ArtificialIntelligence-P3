cmake_minimum_required(VERSION 3.21)
project(Project3)
set(CMAKE_CXX_STANDARD 11)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})

add_definitions(${GTK3_CFLAGS_OTHER})

find_library(LIB1 clasp ${CMAKE_SOURCE_DIR}/lib)
find_library(LIB2 potassco ${CMAKE_SOURCE_DIR}/lib)
find_path(LIB_INCLUDE clasp/config.h potassco/platform.h ${CMAKE_SOURCE_DIR}/include)
include_directories(${LIB_INCLUDE})

add_executable(Project3 src/main.cpp)
target_link_libraries(Project3 PUBLIC ${GTK3_LIBRARIES} ${LIB1} ${LIB2})
