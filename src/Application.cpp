#include "Application.h"

#include "render/RenderingContext.h"
#include "render/PhysicalWindow.h"

namespace Application {

    static Gui::Context* guiContext = nullptr;

    void Start() {

        RenderingContext::Initialize();

        guiContext = new Gui::Context;

        while (IsRunning()) {
            RenderingContext::StartFrame();

            guiContext->BeginFrame();
            guiContext->Draw();
            guiContext->EndFrame();

            RenderingContext::FinishFrame();
        }

        RenderingContext::Terminate();

    }

    void Stop() {
        PhysicalWindow::Close();
    }

    bool IsRunning() {
        return RenderingContext::IsRunning();
    }

    Gui::Context* GetGuiContext() {
        if (guiContext == nullptr) {
            throw std::exception("Trying to fetch Gui::Context before it is created.");
        }
        return guiContext;
    }

}