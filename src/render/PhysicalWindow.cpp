#include "PhysicalWindow.h"

#include <exception>


GLFWwindow* PhysicalWindow::handle = nullptr;

void PhysicalWindow::Create(int width, int height, const char *title) {

    glfwDefaultWindowHints();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    handle = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (handle == nullptr) {
        throw std::exception();
    }

}

void PhysicalWindow::Destroy() {
    glfwDestroyWindow(handle);
}

void PhysicalWindow::SwapBuffers() {
    glfwSwapBuffers(handle);
}

void PhysicalWindow::Close() {
    glfwSetWindowShouldClose(handle, GLFW_TRUE);
}

bool PhysicalWindow::ShouldClose() {
    return glfwWindowShouldClose(handle) == GLFW_TRUE;
}

GLFWwindow* PhysicalWindow::GetHandle() {
    return handle;
}