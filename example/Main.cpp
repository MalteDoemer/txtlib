#include <stdlib.h>
#include <unistd.h>
#include <cstring>

#include "TxtApplication.hpp"

// Common debugging stuff for RoboProLib
unsigned int DebugFlags;
FILE* DebugFile;

class App : public txt::application {

public:
    App() {}

    void run()
    {

        printf("resetting counter...\n");
        txt.reset_counter(txt::C1);
        while (!txt.is_counter_resetted(txt::C1)) {}

        while (true) {
            usleep(10000);

            auto val = txt.get_counter_value(txt::C1);

            if (val != last_counter_value) {
                printf("%d\n", val);
                last_counter_value = val;
            }
        }
    }

private:
    i16 last_counter_value = -1;
};

int main()
{
    printf("starting app...\n");

    App app;
    app.run();
    return 0;
}