#include <stdlib.h>
#include <unistd.h>

#include "TxtApplication.hpp"
#include "Motor.hpp"

// Common debugging stuff for RoboProLib
unsigned int DebugFlags;
FILE* DebugFile;

class App : public TxtApplication {

public:
    App() : m1(txt, MotorId::M1), m2(txt, MotorId::M2) {}

    void run()
    {
        m1.start(Direction::Left, 512);
        m2.start(Direction::Right, 512);

        sleep(4);

        m1.stop();
        m2.stop();
    }

private:
    Motor m1;
    Motor m2;
};

int main()
{
    printf("Starting App\n");

    App app;
    app.run();
    return 0;
}