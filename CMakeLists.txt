cmake_minimum_required(VERSION 3.5)

project(s3dvami LANGUAGES CXX)

set(CMAKE_INSTALL_RPATH ".")
set(CMAKE_BUILD_WITH_INSTALL_RPATH y)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#make externals
#add_subdirectory(externals)

include_directories(include)

file(GLOB_RECURSE SOURCES src/*.*)
file(GLOB_RECURSE INCLUDES include/*.*)

add_executable(s3dvami ${SOURCES})

find_package(OpenGL REQUIRED)
target_link_libraries(s3dvami OpenGL::GL)

find_package(GLU REQUIRED)
target_link_libraries(s3dvami GLU)

find_package(glfw3 3.3 REQUIRED)
target_link_libraries(s3dvami glfw)

#find_package(assimp REQUIRED)
#target_link_libraries(Animation3D assimp)
