cmake_minimum_required(VERSION 3.21)
project(Project3 C CXX)
set(CMAKE_CXX_STANDARD 17)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0 glibmm-2.4 gtkmm-3.0 glib-2.0 gio-2.0)

list(APPEND FC_DEP_LIBS ${GTK3_LIBRARIES})
include_directories(${GTK3_INCLUDE_DIRS} ${GTKMM_INCLUDE_DIRS})
find_path(LIB_INCLUDE  p3/p3.h p3/App.h ${CMAKE_SOURCE_DIR}/include )
include_directories(${LIB_INCLUDE})

add_executable(ArtificialIntelligenceP3
  src/sources/main.cpp
  src/sources/utility.cpp
  src/sources/File.cpp
  src/sources/Wigets.cpp
  src/sources/App.cpp
  src/sources/resources.c
  include/p3/p3.h
        include/p3/gtkmmconfig.h)

target_link_libraries(ArtificialIntelligenceP3 PUBLIC ${GTKMM_LIBRARIES} ${GLIB_LIBRARIES} ${GTK3_LIBRARIES})
