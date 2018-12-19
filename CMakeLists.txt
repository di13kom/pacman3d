cmake_minimum_required(VERSION 2.6.3)

project(Pacman3d)
if(UNIX)
	set(OpenGL_GL_PREFERENCE "LEGACY")
endif(UNIX)

find_package(OpenGL REQUIRED)
find_package(FLTK REQUIRED NO_MODULE)
include_directories(${FLTK_INCLUDE_DIRS})
find_package(OpenAL REQUIRED)

include_directories(${CMAKE_BINARY_DIR})
include_directories(${CMAKE_SOURCE_DIR})

set (Sources playground.cxx readfile.cxx)
set (Headers playground.h readfile.h)

file(GLOB files_to_copy index.jpeg level1.mf sounds)
file(COPY ${files_to_copy} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

#add_executable(Pacman3d WIN32 ${Sources} ${Headers} ${files_to_copy})
add_executable(Pacman3d ${Sources} ${Headers})

target_link_libraries(Pacman3d fltk fltk_gl fltk_images GLU GL alut openal)
