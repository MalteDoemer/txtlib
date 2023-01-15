#include <stdlib.h>
#include <unistd.h>

#include <iostream>

#include "Ultrasonic.hpp"
#include "TxtApplication.hpp"

// Common debugging stuff for RoboProLib
unsigned int DebugFlags;
FILE* DebugFile;

class App : public txt::application {

public:
    App() : ultrasonic(txt, txt::I1) {}

    void update() override
    {
        usleep(100000);

        ultrasonic.update();

        if (ultrasonic.has_changed()) {
            printf("%d cm\n", ultrasonic.distance());
        }
    }

private:
    txt::ultrasonic ultrasonic;
};

int main()
{
    printf("starting app...\n");

    App app;
    app.start();

    return 0;
}