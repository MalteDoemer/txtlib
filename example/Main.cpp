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
    App() : button(txt, txt::I1), m1(txt, txt::M1), m2(txt, txt::M2)
    {
        // txt.configure_motor_output(txt::M1, true);
        // txt.configure_motor_output(txt::M2, true);
    }

    void setup() override
    {
        // txt.set_motor_distance(txt::M1, 250);
        // txt.set_motor_distance(txt::M2, 250);
        // txt.set_motor_master(txt::M1, 0);
        // txt.set_motor_master(txt::M2, 1);

        // txt.set_motor(txt::M1, 512, txt::direction::forward);
        // txt.set_motor(txt::M2, 512, txt::direction::forward);

        // txt.start_motor_command(txt::M1);
        // txt.start_motor_command(txt::M2);

        // printf("started command...\n");

        // while (!txt.is_motor_command_finished(txt::M1) && !txt.is_motor_command_finished(txt::M2)) {
        //     printf("not finished\n");
        //     usleep(500000);
        // }

        // printf("finished\n");
    }

    void update() override
    {
        usleep(100000);

        button.update();

        if (button.has_released()) {
            m1.enhanced_mode(250, 0);
            m2.enhanced_mode(250, 1);
            m1.start(256, txt::direction::forward);
            m2.start(256, txt::direction::forward);
            printf("started command...\n");

            while (!m1.has_stopped() && !m2.has_stopped()) {
                printf("not finished\n");
                usleep(500000);
            }
        }
    }

private:
    txt::button button;
    txt::motor m1;
    txt::motor m2;
};

int main()
{
    printf("starting app...\n");

    App app;
    app.start();

    return 0;
}