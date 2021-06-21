#ifndef F1METER_RENDERCONTEXT_H
#define F1METER_RENDERCONTEXT_H

#include <glad/glad.h>
#include "PhysicalWindow.h"

#include <memory>

class RenderContext {

    PhysicalWindow* window;

private:
    RenderContext();

public:

    void Initialize();

    void StartFrame();
    void EndFrame();

    bool IsRunning();

    void CleanUp();

private:
    void InitializeGlfw();
    void InitializeGlad();
    void InitializeImGui();

    void ConfigureImGui() const;

    void CleanUpImGui();
    void CleanUpGlfw();

public:
    static RenderContext& GetInstance();
private:
    static RenderContext* instance;
    static void DeleteInstance();

    friend class Application;
};

#endif //F1METER_RENDERCONTEXT_H
