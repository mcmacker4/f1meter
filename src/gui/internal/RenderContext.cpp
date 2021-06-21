#include "RenderContext.h"

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include <implot/implot.h>

#include <iostream>

RenderContext* RenderContext::instance = nullptr;

RenderContext::RenderContext() : window(nullptr) {}

void RenderContext::Initialize() {
    InitializeGlfw();
    InitializeGlad();
    InitializeImGui();
}

void RenderContext::StartFrame() {
    glfwPollEvents();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void RenderContext::EndFrame() {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    window->SwapBuffers();
}

bool RenderContext::IsRunning() {
    return !window->ShouldClose();
}

void RenderContext::CleanUp() {
    CleanUpImGui();
    CleanUpGlfw();
}

void RenderContext::InitializeGlfw() {
    glfwSetErrorCallback([](int err, const char* desc) { std::cout << "[GLFW Error " << err << "] " << std::endl; });
    if (!glfwInit())
        throw std::exception("Could not initialize GLFW.");
    window = PhysicalWindow::Create(1280, 720, "Hello World");
}

void RenderContext::InitializeGlad() {
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        throw std::exception("Could not initialize GLAD.");
    }
    glClearColor(0.3F, 0.6F, 0.9F, 1.0F);
}

void RenderContext::InitializeImGui() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window->GetHandle(), true);
    ImGui_ImplOpenGL3_Init("#version 150");

    ImPlot::CreateContext();

    ConfigureImGui();
}

void RenderContext::ConfigureImGui() const {
    ImGuiIO& io = ImGui::GetIO();
    io.IniFilename = nullptr;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags &= ~ImGuiConfigFlags_NavEnableGamepad;

    ImFontConfig fontConfig;
    fontConfig.SizePixels = 16;

    io.Fonts->AddFontDefault(&fontConfig);
}

void RenderContext::CleanUpImGui() {
    ImPlot::DestroyContext();

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void RenderContext::CleanUpGlfw() {
    delete window;
    glfwTerminate();
}

RenderContext& RenderContext::GetInstance() {
    if (instance == nullptr) {
        instance = new RenderContext;
    }
    return *instance;
}

void RenderContext::DeleteInstance() {
    delete instance;
    instance = nullptr;
}