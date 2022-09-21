cmake_minimum_required(VERSION 3.21)
project(Project3 C CXX)
set(CMAKE_CXX_STANDARD 11)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
message(STATUS "----- GTK3_INCLUDE_DIRS: ${GTK3_INCLUDE_DIRS}")
message(STATUS "----- GKT3_LIBRARIES: ${GTK3_LIBRARIES}")
message(STATUS "----- GTK3_LINK_LIBRARIES: ${GTK3_LINK_LIBRARIES}")
include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})
list(APPEND FC_DEP_LIBS ${GTK3_LIBRARIES})

include_directories(${GTKMM_INCLUDE_DIRS})
link_directories(${GTKMM_LIBRARY_DIRS})

add_definitions(${GTKMM_CFLAGS_OTHER})

find_path(LIB_INCLUDE  p3/p3.h p3/App.h ${CMAKE_SOURCE_DIR}/include)
include_directories(${LIB_INCLUDE})

add_executable(Project3
  src/sources/main.cpp
  src/sources/utility.cpp
  src/sources/File.cpp
  src/sources/Wigets.cpp
  src/sources/App.cpp
  src/sources/resources.c
  include/p3/p3.h
        include/p3/gtkmmconfig.h)

target_link_libraries(Project3 PUBLIC ${GTKMM_LIBRARIES})
