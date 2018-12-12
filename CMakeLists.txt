cmake_minimum_required(VERSION 2.6.3)

project(Playground3)
project(Playground)

find_package(FLTK REQUIRED NO_MODULE)
include(${FLTK_USE_FILE})

include_directories(${CMAKE_BINARY_DIR})
include_directories(${CMAKE_SOURCE_DIR})

file(GLOB files_to_copy index.jpeg)
file(COPY ${files_to_copy} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(Playground3 WIN32 playground3.cxx ${files_to_copy})
add_executable(Playground WIN32 playground.cxx ${files_to_copy})

target_link_libraries(Playground3 fltk fltk_gl fltk_images)
target_link_libraries(Playground fltk fltk_gl fltk_images)
