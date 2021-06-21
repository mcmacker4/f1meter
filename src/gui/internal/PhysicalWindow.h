#ifndef F1METER_PHYSICALWINDOW_H
#define F1METER_PHYSICALWINDOW_H

#include <GLFW/glfw3.h>

class PhysicalWindow {
    GLFWwindow* handle;

private:
    explicit PhysicalWindow(GLFWwindow* handle);

public:
    bool ShouldClose();
    void SwapBuffers();

    GLFWwindow* GetHandle();

    static PhysicalWindow* Create(int width, int height, const char* title);

};


#endif //F1METER_PHYSICALWINDOW_H
