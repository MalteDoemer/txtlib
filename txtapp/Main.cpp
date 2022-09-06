#include <stdlib.h>
#include <unistd.h>
#include <cstring>

#include "TxtApplication.hpp"
#include "Motor.hpp"
#include "Lamp.hpp"

#include "TCPServer.h"

using namespace SocketPP;

// Common debugging stuff for RoboProLib
unsigned int DebugFlags;
FILE* DebugFile;

struct MotorCommand {
    Direction left_dir;
    Direction right_dir;
    u16 reserved;
    u32 left_dist;
    u32 right_dist;
};

class App : public TxtApplication {

public:
    App() : l1(txt, OutputId::O5), m1(txt, MotorId::M1), m2(txt, MotorId::M2) { m1.link(m2); }

    void run()
    {
        const int port = 10000;

        TCPServer server(port);

        server.setRecvHandle([&](const Message& message) {

            MotorCommand cmd;

            auto* data = message.rawMsg.data();
            std::memcpy(&cmd, data, sizeof(MotorCommand));
            
            run_motor_command(cmd);
        });

        server.loop();
    }

    void run_motor_command(MotorCommand cmd)
    {
        m1.set(cmd.left_dir, 512);
        m2.set(cmd.right_dir, 512);

        m1.start(cmd.left_dist);
        m2.start(cmd.right_dist);
    }

private:
    Lamp l1;
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