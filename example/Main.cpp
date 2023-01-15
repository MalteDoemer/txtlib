#include <stdlib.h>
#include <unistd.h>

#include <iostream>

#include "Button.hpp"
#include "Counter.hpp"
#include "Ultrasonic.hpp"
#include "TxtApplication.hpp"

// Common debugging stuff for RoboProLib
unsigned int DebugFlags;
FILE* DebugFile;

class App : public txt::application {

public:
    App() : counter(txt, txt::C1) {}

    void update() override
    {
        // usleep(100000);

        counter.update();

        // button.update();
        // ultrasonic.update();

        if (counter.has_changed()) {
            printf("%d\n", counter.count());

            if (counter.count() >= 11) {
                counter.reset();
            }
        }

        // if (button.has_changed()) {
        //     auto val = button.state();
        //     printf("%s\n", val ? "on" : "off");
        // }

        // if (button.has_released()) {
        //     printf("released!\n");
        // }

        // if (ultrasonic.has_changed()) {
        //     printf("%d cm\n", ultrasonic.distance());
        // }
    }

private:
    txt::counter counter;

    // txt::ultrasonic ultrasonic;
};

int main()
{
    printf("starting app...\n");

    App app;
    app.start();

    return 0;
}