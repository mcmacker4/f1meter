#include "Context.h"

#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include <implot/implot.h>

namespace Gui {

#ifdef F1_DEBUG
    Context::Context() : showImGuiDemo(false), showImPlotDemo(false), plotWindow(), dockspace() {}
#else
    Context::Context() : plotWindow(), dockspace() {}
#endif

    void Context::BeginFrame() {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void Context::Draw() {
        dockspace.Draw();
#ifdef F1_DEBUG
        if (showImGuiDemo)
            ImGui::ShowDemoWindow(&showImGuiDemo);
        if (showImPlotDemo)
            ImPlot::ShowDemoWindow(&showImPlotDemo);
#endif
        plotWindow.Draw();
    }

    void Context::EndFrame() {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

}