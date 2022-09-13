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

enum CommandType : u32 {
    Motors = 0,
    Lights,
};


struct LightCommand {
    u32 enable_lights;
    u32 reserved1;
    u32 reserved2;
};

struct MotorCommand {
    Direction left_dir;
    Direction right_dir;
    u16 reserved;
    u32 left_dist;
    u32 right_dist;
};

struct Command {
    CommandType type;
    union {
        MotorCommand motor_command;
        LightCommand light_command;
    };
};

class App : public TxtApplication {

public:
    App() : l1(txt, OutputId::O5), m1(txt, MotorId::M1), m2(txt, MotorId::M2) { m1.link(m2); }

    void run()
    {
        const int port = 10000;

        TCPServer server(port);

        server.setRecvHandle([&](const Message& message) {
            Command cmd;

            auto* data = message.rawMsg.data();
            std::memcpy(&cmd, data, sizeof(Command));

            if (cmd.type == Motors)
                run_motor_command(cmd.motor_command);

            else if (cmd.type == Lights)
                run_light_command(cmd.light_command);
        });

        server.loop();
    }

    void run_light_command(LightCommand cmd)
    {
        if (cmd.enable_lights)
            l1.activate(512);
        else
            l1.deactivate();
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