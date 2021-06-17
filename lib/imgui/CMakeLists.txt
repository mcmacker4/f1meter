cmake_minimum_required(VERSION 3.16)
project(imgui)

add_compile_definitions(IMGUI_IMPL_OPENGL_LOADER_GLAD)

set(IMGUI_SOURCES
        imgui.cpp
        imgui_draw.cpp
        imgui_tables.cpp
        imgui_widgets.cpp
        imgui_impl_glfw.cpp
        imgui_impl_opengl3.cpp)

if (F1_DEBUG)
    set(IMGUI_SOURCES ${IMGUI_SOURCES} imgui_demo.cpp)
endif()

add_library(imgui ${IMGUI_SOURCES})

target_link_libraries(imgui LINK_PUBLIC glfw)
target_link_libraries(imgui LINK_PUBLIC glad)

target_include_directories(imgui PUBLIC include/)
target_include_directories(imgui PUBLIC include/imgui)