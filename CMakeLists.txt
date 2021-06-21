cmake_minimum_required(VERSION 3.19)
project(f1meter CXX)

if (NOT WIN32)
    message(FATAL_ERROR "We only support Windows for now.")
endif()

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(F1_DEBUG TRUE)
endif()

set(CMAKE_CXX_STANDARD 17)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(lib/glfw)
add_subdirectory(lib/glad)
add_subdirectory(lib/imgui)
add_subdirectory(lib/implot)

add_executable(f1meter
        src/main.cpp
        src/Application.cpp
        src/gui/internal/RenderContext.cpp
        src/gui/internal/PhysicalWindow.cpp
        src/telemetry/Telemetry.cpp
        src/telemetry/udp/PacketProcessing.cpp
        src/telemetry/udp/UdpServer.cpp
        src/telemetry/udp/UdpSocket.cpp
        src/telemetry/udp/platform/UdpSocketWindows.cpp
)

target_link_libraries(f1meter glfw glad imgui implot wsock32 ws2_32)

if (F1_DEBUG)
    target_compile_definitions(f1meter PUBLIC F1_DEBUG)
endif()
