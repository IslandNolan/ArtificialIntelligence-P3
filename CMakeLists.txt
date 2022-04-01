cmake_minimum_required(VERSION 3.21)
project(Project3)
set(CMAKE_CXX_STANDARD 11)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED gtkmm-3.0)

include_directories(${GTKMM_INCLUDE_DIRS})
link_directories(${GTKMM_LIBRARY_DIRS})

add_definitions(${GTKMM_CFLAGS_OTHER})

find_path(LIB_INCLUDE  p3/p3.h p3/App.h ${CMAKE_SOURCE_DIR}/include)
include_directories(${LIB_INCLUDE})

add_executable(Project3
  src/sources/main.cpp
  src/sources/utility.cpp
  src/sources/App.cpp
  include/p3/p3.h
)

target_link_libraries(Project3 PUBLIC ${GTKMM_LIBRARIES})
