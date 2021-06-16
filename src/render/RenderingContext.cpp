#include "RenderingContext.h"

#include <iostream>
#include <utility>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include "PhysicalWindow.h"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720


void RenderingContext::Initialize() {
    InitializeGLFW();
    InitializeGLAD();

    InitializeImGui();
}

void RenderingContext::Terminate() {
    TerminateImGui();

    TerminateGLFW();
}

void RenderingContext::PollEvents() {
    glfwPollEvents();
}

void RenderingContext::NextFrame() {
    PhysicalWindow::SwapBuffers();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void glfw_error_callback(int code, const char* desc) {
    std::cerr << "[GLFW ERROR] " << desc << std::endl;
}

void RenderingContext::InitializeGLFW() {

    glfwSetErrorCallback(glfw_error_callback);

    if (glfwInit() != GLFW_TRUE) {
        throw RenderingContextException("Could not initialize GLFW");
    }

    PhysicalWindow::Create(WINDOW_WIDTH, WINDOW_HEIGHT, "Hello F1 2020");

    glfwMakeContextCurrent(PhysicalWindow::GetHandle());

}

void RenderingContext::InitializeGLAD() {
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        throw RenderingContextException("Could not initialize GLAD.");
    }
}

void RenderingContext::InitializeImGui() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGui_ImplGlfw_InitForOpenGL(PhysicalWindow::GetHandle(), true);
    ImGui_ImplOpenGL3_Init("#version 150");
}

void RenderingContext::TerminateImGui() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void RenderingContext::TerminateGLFW() {
    PhysicalWindow::Destroy();
    glfwTerminate();
}

bool RenderingContext::IsRunning() {
    return !PhysicalWindow::ShouldClose();
}


RenderingContextException::RenderingContextException(std::string msg)
    : msg(std::move(msg)) {}

const char * RenderingContextException::what() const {
    return msg.c_str();
}