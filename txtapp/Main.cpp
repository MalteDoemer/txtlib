#include <stdlib.h>
#include <unistd.h>

#include "TxtApplication.hpp"
#include "Motor.hpp"

// Common debugging stuff for RoboProLib
unsigned int DebugFlags;
FILE* DebugFile;

class App : public TxtApplication {

public:
    App() : m1(txt, MotorId::M1)
    {        
    }

    void run() 
    {
        m1.start(Direction::Left, 512);
        
        sleep(2);

        m1.stop();

    }

private:
    Motor m1;
};

int main()
{
    printf("Starting App\n");

    App app;
    app.run();
    return 0;
}