cmake_minimum_required(VERSION 3.19)
project(f1meter CXX)

if (NOT WIN32)
    message(FATAL_ERROR "We only support Windows for now.")
endif()

set(CMAKE_CXX_STANDARD 17)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(lib/glfw)
add_subdirectory(lib/glad)
add_subdirectory(lib/imgui)

add_executable(f1meter
        src/main.cpp
        src/Application.cpp
        src/render/PhysicalWindow.cpp
        src/render/RenderingContext.cpp)

target_link_libraries(f1meter glfw glad imgui)