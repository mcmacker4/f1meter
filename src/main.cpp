#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_impl_glfw.h>

int main() {

    if (glfwInit() != GLFW_TRUE) {
        std::cerr << "Could not initialize GLFW." << std::endl;
        return 1;
    }

    GLFWwindow* window = glfwCreateWindow(1280, 720, "Hello F1 2020!", nullptr, nullptr);
    if (window == nullptr) {
        std::cerr << "Could not create GLFW window." << std::endl;
    }

    glfwMakeContextCurrent(window);

    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

    glClearColor(0.3f, 0.6f, 0.9f, 1.0f);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 150");

    glfwSwapInterval(0);

    bool open = true;

    while (glfwWindowShouldClose(window) != GLFW_TRUE) {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        ImGui::ShowDemoWindow(&open);
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
