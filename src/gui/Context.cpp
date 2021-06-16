#include "Context.h"

#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

namespace Gui {

    Context::Context() : showDemo(false) {}


    void Context::BeginFrame() {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void Context::Draw() {
        dockspace.Draw();
        if (showDemo) {
            ImGui::ShowDemoWindow(&showDemo);
        }
    }

    void Context::EndFrame() {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

}