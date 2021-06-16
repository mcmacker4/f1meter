#ifndef F1METER_RENDERINGCONTEXT_H
#define F1METER_RENDERINGCONTEXT_H

#include <exception>
#include <string>

namespace RenderingContext {

    void Initialize();
    void Terminate();

    void StartFrame();
    void FinishFrame();

    bool IsRunning();

}

class RenderingContextException : public std::exception {
    std::string msg;
public:
    explicit RenderingContextException(std::string msg);
    [[nodiscard]] const char * what() const override;
};

#endif //F1METER_RENDERINGCONTEXT_H
