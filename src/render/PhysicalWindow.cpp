#include "PhysicalWindow.h"

#include <exception>

namespace PhysicalWindow {

    static GLFWwindow *handle = nullptr;

    void Create(int width, int height, const char *title) {

        glfwDefaultWindowHints();

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        handle = glfwCreateWindow(width, height, title, nullptr, nullptr);
        if (handle == nullptr) {
            throw std::exception();
        }

    }

    void Destroy() {
        glfwDestroyWindow(handle);
    }

    void SwapBuffers() {
        glfwSwapBuffers(handle);
    }

    void Close() {
        glfwSetWindowShouldClose(handle, GLFW_TRUE);
    }

    bool ShouldClose() {
        return glfwWindowShouldClose(handle) == GLFW_TRUE;
    }

    GLFWwindow* GetHandle() {
        return handle;
    }

}