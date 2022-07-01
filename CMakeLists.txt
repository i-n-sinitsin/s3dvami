cmake_minimum_required(VERSION 3.5)

project(s3dvami LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

file(GLOB_RECURSE SOURCES src/*.*)
file(GLOB_RECURSE INCLUDES include/*.*)

add_executable(s3dvami ${SOURCES})

#find_package(OpenGL REQUIRED)
#target_link_libraries(Animation3D OpenGL::GL)

#find_package(GLU REQUIRED)
#target_link_libraries(Animation3D GLU)

#find_package(assimp REQUIRED)
#target_link_libraries(Animation3D assimp)

#find_package(glfw3 3.3 REQUIRED)
#target_link_libraries(Animation3D glfw)
