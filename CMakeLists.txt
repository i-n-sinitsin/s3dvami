cmake_minimum_required(VERSION 3.5)

project(s3dvami LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

file(GLOB_RECURSE SOURCES src/*.*)
add_executable(s3dvami ${SOURCES})
target_compile_options(s3dvami PRIVATE -Wall)

find_package(OpenGL REQUIRED)
target_link_libraries(s3dvami
    PUBLIC
        OpenGL::GL
        GLU
)

add_subdirectory(external)

target_link_libraries(s3dvami
  PRIVATE
      glm
      imgui
      stb
      glfw
)
