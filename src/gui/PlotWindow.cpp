#include "PlotWindow.h"

#include <imgui/imgui.h>
#include <cstdlib>

namespace Gui {

    PlotWindow::PlotWindow() {
#define LEN 32
        data = new float[32];
        for (int i = 0; i < LEN; i++) {
            data[i] = rand() % 32 / 32.0F;
        }
#undef LEN
    }

    void PlotWindow::Draw() {

        if (ImGui::Begin("PlotWindow")) {
            ImGui::Text("This is a plot!");
        }

        ImGui::End();

    }

}
