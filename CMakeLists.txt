cmake_minimum_required(VERSION 3.21)
project(Project3)
set(CMAKE_CXX_STANDARD 11)

find_package(PkgConfig REQUIRED)
if (CMAKE_SYSTEM_NAME MATCHES "Linux")
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
    message(STATUS "----- GTK3_INCLUDE_DIRS: ${GTK3_INCLUDE_DIRS}")
    message(STATUS "----- GKT3_LIBRARIES: ${GTK3_LIBRARIES}")
    message(STATUS "----- GTK3_LINK_LIBRARIES: ${GTK3_LINK_LIBRARIES}")
    include_directories(${GTK3_INCLUDE_DIRS})
    link_directories(${GTK3_LIBRARY_DIRS})
    list(APPEND FC_DEP_LIBS ${GTK3_LIBRARIES})
elseif (CMAKE_SYSTEM_NAME MATCHES "Darwin")
    #export PKG_CONFIG_PATH="$(brew --prefix libffi)/lib/pkgconfig/"
    set(ENV{PKG_CONFIG_PATH} /usr/local/opt/libffi/lib/pkgconfig)
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
    message(STATUS "----- GKT3_LIBRARIES: ${GTK3_LIBRARIES}")
    message(STATUS "----- GTK3_LINK_LIBRARIES: ${GTK3_LINK_LIBRARIES}")
    include_directories(${GTK3_INCLUDE_DIRS})
    list(APPEND FC_DEP_LIBS ${GTK3_LINK_LIBRARIES})
endif()

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
)

target_link_libraries(Project3 PUBLIC ${GTKMM_LIBRARIES})
