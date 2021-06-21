#include "Application.h"

#include "gui/internal/RenderContext.h"
#include "telemetry/Telemetry.h"

#include <imgui/imgui.h>
#include <implot/implot.h>

#include <iostream>

Application* Application::instance = nullptr;

void Application::Start() {
    Initialize();
    Run();
    CleanUp();
}

void Application::Initialize() {
    RenderContext::GetInstance().Initialize();
}

void Application::Run() {

    auto& renderContext = RenderContext::GetInstance();
    auto& telemetry = Telemetry::GetInstance();

    telemetry.StartUdpServer();

    while (renderContext.IsRunning()) {
        renderContext.StartFrame();

        auto& carTelemetry = telemetry.GetCarTelemetryData();
        auto count = carTelemetry.Count();

        ImPlot::ShowDemoWindow();

        if (ImGui::Begin("Telemetry")) {

            ImPlot::SetNextPlotLimits(0, 1000, 0, 400);

            if (ImPlot::BeginPlot("Speed")) {

                ImPlotPoint (*speedGetter)(void*, int) = [](void* data, int idx) {
                    CarTelemetryDataPoint& point = (*reinterpret_cast<CarTelemetryData*>(data))[idx];
                    return ImPlotPoint(point.time, point.speed);
                };
                ImPlotPoint (*rpmGetter)(void*, int) = [](void* data, int idx) {
                    CarTelemetryDataPoint& point = (*reinterpret_cast<CarTelemetryData*>(data))[idx];
                    return ImPlotPoint(point.time, point.engineRPM / 10);
                };

                ImPlot::PlotLineG("speed", speedGetter, &carTelemetry, count);
                ImPlot::PlotLineG("rpm", rpmGetter, &carTelemetry, count);
                ImPlot::EndPlot();
            }
        }

        ImGui::End();

        renderContext.EndFrame();
    }

}

void Application::CleanUp() {
    RenderContext::GetInstance().CleanUp();
    RenderContext::DeleteInstance();
}

Application& Application::GetInstance() {
    if (instance == nullptr) {
        instance = new Application;
    }
    return *instance;
}

void Application::DeleteInstance() {
    delete instance;
}