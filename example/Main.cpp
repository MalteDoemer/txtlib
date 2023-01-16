#include <stdlib.h>
#include <unistd.h>

#include <iostream>

#include "Motor.hpp"
#include "Button.hpp"
#include "Counter.hpp"
#include "PwmOutput.hpp"
#include "Ultrasonic.hpp"
#include "TxtApplication.hpp"

// Common debugging stuff for RoboProLib
unsigned int DebugFlags;
FILE* DebugFile;

class App : public txt::application {

public:
    App() :
        button(txt, txt::I1),
        ultrasonic(txt, txt::I6),
        m1(txt, txt::M1),
        m2(txt, txt::M2),
        lamp1(txt, txt::O7),
        lamp2(txt, txt::O8)
    {
    }

    void setup() override {}

    void update() override
    {
        usleep(100000);

        button.update();
        ultrasonic.update();

        if (ultrasonic.has_changed()) {
            printf("d = %dcm\n", ultrasonic.distance());
        }

        if (button.has_released()) {
            toggle_lamps();
            test_motors(500);
        }
    }

    void toggle_lamps()
    {
        lamps_on = !lamps_on;

        if (lamps_on) {
            lamp1.on(512);
            lamp2.on(512);
        } else {
            lamp1.off();
            lamp2.off();
        }
    }

    void test_motors(int distance)
    {
        m1.enhanced_mode(distance, 0);
        m2.enhanced_mode(distance, 1);
        m1.start(512, txt::direction::forward);
        m2.start(512, txt::direction::forward);
        printf("started command...\n");

        while (!m1.has_stopped() && !m2.has_stopped()) {}

        printf("finished\n");
    }

private:
    bool lamps_on = false;

    txt::motor m1;
    txt::motor m2;
    txt::button button;
    txt::pwm_output lamp1;
    txt::pwm_output lamp2;
    txt::ultrasonic ultrasonic;
};

int main()
{
    printf("starting app...\n");

    App app;
    app.start();

    return 0;
}