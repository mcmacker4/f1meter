#ifndef F1METER_RENDERINGCONTEXT_H
#define F1METER_RENDERINGCONTEXT_H

#include <exception>
#include <string>

class RenderingContext {

public:
    RenderingContext() = delete;

    static void Initialize();
    static void Terminate();

    static void PollEvents();
    static void NextFrame();

    static bool IsRunning();

private:
    static void InitializeGLFW();
    static void InitializeGLAD();
    static void InitializeImGui();

    static void TerminateImGui();
    static void TerminateGLFW();

};

class RenderingContextException : public std::exception {
    std::string msg;
public:
    explicit RenderingContextException(std::string msg);
    [[nodiscard]] const char * what() const override;
};

#endif //F1METER_RENDERINGCONTEXT_H
