#ifndef F1METER_APPLICATION_H
#define F1METER_APPLICATION_H

#include "gui/Context.h"

namespace Application {

    void Start();

    void Stop();

    bool IsRunning();
    Gui::Context* GetGuiContext();

}


#endif //F1METER_APPLICATION_H
