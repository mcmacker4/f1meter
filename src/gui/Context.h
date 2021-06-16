#ifndef F1METER_CONTEXT_H
#define F1METER_CONTEXT_H

#include "Dockspace.h"

namespace Gui {

    class Context {

        Dockspace dockspace;

    public:
        bool showDemo;

    public:
        Context();

        Context(const Context&) = delete;
        Context(Context&&) = delete;

        void BeginFrame();
        void Draw();
        void EndFrame();

    };

}

#endif //F1METER_CONTEXT_H
