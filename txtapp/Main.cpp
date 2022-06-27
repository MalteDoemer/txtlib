
#include "TxtApplication.hpp"

// Common debugging stuff for RoboProLib
unsigned int DebugFlags;
FILE* DebugFile;

class App : public TxtApplication {

public:
    App()
    {
    }

    void run() 
    {

    }
};

int main()
{
    printf("Starting App\n");

    App app;
    app.run();
    return 0;
}