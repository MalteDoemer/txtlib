#include <stdlib.h>
#include <unistd.h>
#include <cstring>

#include <thread>
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

        auto dist = ultrasonic.get_distance();

        if (dist != last_dist) {
            printf("%d cm\n", dist);
            last_dist = dist;
        }
    }

private:
    i16 last_dist = -1;
    txt::ultrasonic ultrasonic;
};

int main()
{
    printf("starting app...\n");

    App app;
    app.start();

    return 0;
}