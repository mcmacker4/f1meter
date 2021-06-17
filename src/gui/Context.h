#ifndef F1METER_CONTEXT_H
#define F1METER_CONTEXT_H

#include "Dockspace.h"
#include "PlotWindow.h"

namespace Gui {

    class Context {

        Dockspace dockspace;
        PlotWindow plotWindow;

    public:
#ifdef F1_DEBUG
        bool showImGuiDemo;
        bool showImPlotDemo;
#endif

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
