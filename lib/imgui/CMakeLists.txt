cmake_minimum_required(VERSION 3.16)
project(imgui)

add_compile_definitions(IMGUI_IMPL_OPENGL_LOADER_GLAD)

add_library(imgui
        include/imgui/imgui.h
        include/imgui/imconfig.h
        include/imgui/imgui_impl_glfw.h
        include/imgui/imgui_impl_opengl3.h
        include/imgui/imgui_internal.h
        include/imgui/imstb_rectpack.h
        include/imgui/imstb_textedit.h
        include/imgui/imstb_truetype.h
        imgui.cpp
        imgui_demo.cpp
        imgui_draw.cpp
        imgui_widgets.cpp
        imgui_impl_glfw.cpp
        imgui_impl_opengl3.cpp)

target_link_libraries(imgui LINK_PUBLIC glfw)
target_link_libraries(imgui LINK_PUBLIC glad)

target_include_directories(imgui PUBLIC include/)