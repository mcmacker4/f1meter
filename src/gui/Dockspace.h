#ifndef F1METER_DOCKSPACE_H
#define F1METER_DOCKSPACE_H

#include <imgui/imgui.h>

namespace Gui {

    class Dockspace {

        ImGuiWindowFlags windowFlags;
        ImGuiDockNodeFlags dockNodeFlags;

    public:
        Dockspace();

        void Draw() const;

    };

}

#endif //F1METER_DOCKSPACE_H
