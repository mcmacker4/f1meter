cmake_minimum_required(VERSION 3.16)
project(implot)

set(IMPLOT_SOURCES
        implot.cpp
        implot_internal.h
        implot_items.cpp)

if (F1_DEBUG)
    set(IMPLOT_SOURCES ${IMPLOT_SOURCES} implot_demo.cpp)
endif()

add_library(implot ${IMPLOT_SOURCES})

target_link_libraries(implot LINK_PUBLIC imgui)

target_include_directories(implot PUBLIC include/)
target_include_directories(implot PRIVATE include/implot)
