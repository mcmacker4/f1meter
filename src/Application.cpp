#include "Application.h"

#include "render/RenderingContext.h"

#include <imgui/imgui.h>

void Application::Start() {

    RenderingContext::Initialize();

    while(IsRunning()) {
        RenderingContext::PollEvents();

        RenderingContext::NextFrame();
    }

    RenderingContext::Terminate();

}

bool Application::IsRunning() {
    return RenderingContext::IsRunning();
}