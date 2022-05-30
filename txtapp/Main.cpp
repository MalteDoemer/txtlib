
#include <cstdio>

#include "TXTApplication.hpp"

// Common debugging stuff for RoboProLib
unsigned int DebugFlags;
FILE* DebugFile;

class App : public TXTApplication {
public:
    App() {}

protected:
    void init() override { printf("hey\n"); }

    bool loop() override 
    {
        return false;
    }
};

int main()
{
    App app;
    app.run();
    return 0;
}