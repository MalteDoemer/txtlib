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
    App() : button(txt, txt::I1), motor(txt, txt::motor_id::M1), lamp(txt, txt::output_id::O7) {}

    void update() override
    {
        usleep(100000);

        button.update();
        // counter.update();
        // ultrasonic.update();

        // if (counter.has_changed()) {
        //     printf("%d\n", counter.count());

        //     if (counter.count() >= 11) {
        //         counter.reset();
        //     }
        // }

        // if (button.has_changed()) {
        //     auto val = button.state();
        //     printf("%s\n", val ? "on" : "off");
        // }

        if (button.has_released()) {
            printf("toggle lamp\n");

            is_lamp_on = !is_lamp_on;
            if (is_lamp_on) {
                printf("off\n");
                lamp.off();
            }
            else {
                lamp.on(512);
                printf("on\n");
            }
        }

        // if (ultrasonic.has_changed()) {
        //     printf("%d cm\n", ultrasonic.distance());
        // }
    }

private:
    txt::button button;
    txt::motor motor;
    txt::pwm_output lamp;

    bool is_lamp_on = true;

    // txt::ultrasonic ultrasonic;
};

int main()
{
    printf("starting app...\n");

    App app;
    app.start();

    return 0;
}