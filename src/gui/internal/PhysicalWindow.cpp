#include "PhysicalWindow.h"

#include <exception>

PhysicalWindow::PhysicalWindow(GLFWwindow* handle) : handle(handle) {}

bool PhysicalWindow::ShouldClose() {
    return glfwWindowShouldClose(handle) == GLFW_TRUE;
}

void PhysicalWindow::SwapBuffers() {
    return glfwSwapBuffers(handle);
}

GLFWwindow* PhysicalWindow::GetHandle() {
    return handle;
}

PhysicalWindow* PhysicalWindow::Create(int width, int height, const char* title) {

    glfwDefaultWindowHints();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    auto* handle = glfwCreateWindow(width, height, title, nullptr, nullptr);

    if (handle == nullptr) {
        throw std::exception("Could not create GLFW window.");
    }

    glfwMakeContextCurrent(handle);

    return new PhysicalWindow(handle);

}