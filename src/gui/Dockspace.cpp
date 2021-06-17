#include "Dockspace.h"

#include "../Application.h"

namespace Gui {

    Dockspace::Dockspace() {
        windowFlags =
                ImGuiWindowFlags_MenuBar |
                ImGuiWindowFlags_NoDocking |
                ImGuiWindowFlags_NoTitleBar |
                ImGuiWindowFlags_NoCollapse |
                ImGuiTableColumnFlags_NoResize |
                ImGuiWindowFlags_NoMove |
                ImGuiWindowFlags_NoBringToFrontOnFocus |
                ImGuiWindowFlags_NoNavFocus;
        dockNodeFlags = ImGuiDockNodeFlags_None;
    }

    void Dockspace::Draw() const {

        ImGuiViewport* viewport = ImGui::GetMainViewport();

        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0F, 0.0F));

        ImGui::Begin("Dockspace", nullptr, windowFlags);

        ImGuiID dockspaceId = ImGui::GetID("Dockspace");
        ImGui::DockSpace(dockspaceId, ImVec2(0.0F, 0.0F), dockNodeFlags);

        ImGui::PopStyleVar();

        if (ImGui::BeginMenuBar()) {

            if (ImGui::BeginMenu("File")) {
                if (ImGui::MenuItem("Exit")) {
                    Application::Stop();
                }
                ImGui::EndMenu();
            }

#ifdef F1_DEBUG
            if (ImGui::BeginMenu("Debug")) {
                ImGui::MenuItem("ImGui Demo", nullptr, &Application::GetGuiContext()->showImGuiDemo);
                ImGui::MenuItem("ImPlot Demo", nullptr, &Application::GetGuiContext()->showImPlotDemo);
                ImGui::EndMenu();
            }
#endif

            ImGui::EndMenuBar();
        }

        ImGui::End();
    }

}