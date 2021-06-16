#ifndef F1METER_PHYSICALWINDOW_H
#define F1METER_PHYSICALWINDOW_H

#include <GLFW/glfw3.h>

namespace PhysicalWindow {

    void Create(int width, int height, const char* title);
    void Destroy();

    void SwapBuffers();

    void Close();

    bool ShouldClose();
    GLFWwindow* GetHandle();

}


#endif //F1METER_PHYSICALWINDOW_H
