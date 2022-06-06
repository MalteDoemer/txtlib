
#include <cstdio>

#include "TXTApplication.hpp"

#include "SocketPP.h"

// Common debugging stuff for RoboProLib
unsigned int DebugFlags;
FILE* DebugFile;

class App : public TxtApplication {

protected:
    void init() override 
    {
    }

    bool loop() override { return false; }
};

int main()
{
    App app;
    app.run();
    return 0;
}