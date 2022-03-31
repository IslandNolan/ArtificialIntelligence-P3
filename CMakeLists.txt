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
find_path(LIB_INCLUDE clasp/config.h potassco/platform.h p3/p3.h ${CMAKE_SOURCE_DIR}/include)
include_directories(${LIB_INCLUDE})

#glib-compile-resource command
#find_program(GLIB_COMPILE_RESOURCES NAMES glib-compile-resources REQUIRED)

#set(GRESOURCE_C src/sources/intelliapp.gresource.cpp)
#set(GRESOURCE_XML intelliapp.gresource.xml)

#add_custom_command(
#  OUTPUT ${GRESOURCE_C}
#  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src/sources
#  COMMAND ${GLIB_COMPILE_RESOURCES}
#  ARGS
#    --target=${CMAKE_CURRENT_BINARY_DIR}/${GRESOURCE_C}
#    ${GRESOURCE_XML}
#  VERBATIM
#  MAIN_DEPENDENCY
#  DEPENDS
#    src/sources/Project3.glade
#  )

#add_custom_target(
#  Project3-resource
#  DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/${GRESOURCE_C}
#  )

add_executable(Project3
  src/sources/main.cpp
  src/sources/utility.cpp
  src/sources/intelliapp.cpp
  src/sources/intelliappwin.cpp
  src/sources/resources.c
  include/p3/p3.h
  include/p3/intelliapp.h
  include/p3/intelliappwin.h
#  ${CMAKE_CURRENT_BINARY_DIR}/${GRESOURCE_C}
)
#set_source_files_properties(
#  ${CMAKE_CURRENT_BINARY_DIR}/${GRESOURCE_C}
#  PROPERTIES GENERATED TRUE
#  )

#add_dependencies(${PROJECT_NAME} Project3-resource)

target_link_libraries(Project3 PUBLIC ${GTK3_LIBRARIES} ${LIB1} ${LIB2})
