#include <stdlib.h>
#include <unistd.h>
#include <cstring>

#include "TxtApplication.hpp"
#include "Motor.hpp"
#include "Lamp.hpp"

// Common debugging stuff for RoboProLib
unsigned int DebugFlags;
FILE* DebugFile;


class App : public TxtApplication {

public:
    App() {}


};

int main()
{
    printf("Starting App\n");

    App app;
    return 0;
}