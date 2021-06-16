#ifndef F1METER_PHYSICALWINDOW_H
#define F1METER_PHYSICALWINDOW_H

#include <GLFW/glfw3.h>

class PhysicalWindow {

    static GLFWwindow* handle;

public:
    PhysicalWindow() = delete;

    static void Create(int width, int height, const char* title);
    static void Destroy();

    static void SwapBuffers();

    static void Close();

    static bool ShouldClose();
    static GLFWwindow* GetHandle();

};


#endif //F1METER_PHYSICALWINDOW_H
