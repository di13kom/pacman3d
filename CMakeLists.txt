cmake_minimum_required(VERSION 2.6.3)

project(Pacman3d)
if(UNIX)
	set(OpenGL_GL_PREFERENCE "LEGACY")
endif(UNIX)

find_package(OpenGL REQUIRED)
find_package(FLTK REQUIRED)
#if(NOT MSYS)
	include_directories(${FLTK_INCLUDE_DIRS})
#endif()

find_package(OpenAL REQUIRED)

include_directories(${CMAKE_BINARY_DIR})
include_directories(${CMAKE_SOURCE_DIR})
include_directories(${OPENAL_INCLUDE_DIR})

set (Sources playground.cxx readfile.cxx)
set (Headers playground.h readfile.h)

file(GLOB files_to_copy index.jpeg level1.mf sounds)
file(COPY ${files_to_copy} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

#add_executable(Pacman3d WIN32 ${Sources} ${Headers} ${files_to_copy})
add_executable(Pacman3d ${Sources} ${Headers})

if(MSYS)
	target_link_libraries(Pacman3d fltk fltk_gl fltk_images glu32 opengl32 alut openal)
elseif(WIN32)
	target_link_libraries(Pacman3d fltk fltk_gl fltk_images opengl32 glu32 ${OPENAL_LIBRARY})
else()
	target_link_libraries(Pacman3d fltk fltk_gl fltk_images GLU GL alut openal)
endif()
