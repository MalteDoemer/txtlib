#include <stdlib.h>
#include <unistd.h>
#include <cstring>

#include <thread>
#include <iostream>

#include "TxtApplication.hpp"

// Common debugging stuff for RoboProLib
unsigned int DebugFlags;
FILE* DebugFile;

class App : public txt::application {

public:
    App() {}

    void setup() override
    {
        txt.configure_input(txt::I1, txt::input_mode::ultrasonic, txt::digital::no);
        printf("configuring...\n");
    }

    void update() override
    {
        usleep(100000);

        auto dist = txt.get_input(txt::I1);

        if (dist != last_dist) {
            printf("%d cm\n", dist);
            last_dist = dist;
        }
    }

private:
    i16 last_dist = -1;
};

int main()
{
    printf("starting app...\n");

    App app;
    app.start();

    return 0;
}