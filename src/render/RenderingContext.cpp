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

void InitializeGLFW();
void InitializeGLAD();
void InitializeImGui();

void TerminateImGui();
void TerminateGLFW();


void RenderingContext::Initialize() {
    InitializeGLFW();
    InitializeGLAD();

    InitializeImGui();
}

void RenderingContext::Terminate() {
    TerminateImGui();

    TerminateGLFW();
}

void RenderingContext::StartFrame() {
    glfwPollEvents();
}

void RenderingContext::FinishFrame() {
    PhysicalWindow::SwapBuffers();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

bool RenderingContext::IsRunning() {
    return !PhysicalWindow::ShouldClose();
}

void GlfwErrorCallback(int code, const char* desc) {
    std::cerr << "[GLFW ERROR] " << desc << std::endl;
}

void InitializeGLFW() {

    glfwSetErrorCallback(GlfwErrorCallback);

    if (glfwInit() != GLFW_TRUE) {
        throw RenderingContextException("Could not initialize GLFW");
    }

    PhysicalWindow::Create(WINDOW_WIDTH, WINDOW_HEIGHT, "Hello F1 2020");

    glfwMakeContextCurrent(PhysicalWindow::GetHandle());

}

void InitializeGLAD() {
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        throw RenderingContextException("Could not initialize GLAD.");
    }
}

void InitializeImGui() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGui_ImplGlfw_InitForOpenGL(PhysicalWindow::GetHandle(), true);
    ImGui_ImplOpenGL3_Init("#version 150");

    ImGuiIO& io = ImGui::GetIO();
    io.IniFilename = nullptr;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
}

void TerminateImGui() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void TerminateGLFW() {
    PhysicalWindow::Destroy();
    glfwTerminate();
}

RenderingContextException::RenderingContextException(std::string msg)
    : msg(std::move(msg)) {}

const char * RenderingContextException::what() const {
    return msg.c_str();
}