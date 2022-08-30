#include <stdlib.h>
#include <unistd.h>

#include "TxtApplication.hpp"
#include "Motor.hpp"
#include "Lamp.hpp"

#include "TCPServer.h"

using namespace SocketPP;

// Common debugging stuff for RoboProLib
unsigned int DebugFlags;
FILE* DebugFile;

class App : public TxtApplication {

public:
    App() : l1(txt, OutputId::O5), m1(txt, MotorId::M1), m2(txt, MotorId::M2) {}

    void run()
    {
        const int port = 10000;

        TCPServer server(port);

        server.setRecvHandle([&](const Message& message) { handle_msg(message.rawMsg.toString()); });

        server.loop();
    }

private:
    void handle_msg(const std::string msg)
    {
        if (msg.substr(0, 7) == "forward") {
            assert(m1.start(Direction::Forward, 512));
            assert(m2.start(Direction::Forward, 512));

        } else if (msg.substr(0, 4) == "left") {
            assert(m1.start(Direction::Backward, 512));
            assert(m2.start(Direction::Forward, 512));

        } else if (msg.substr(0, 5) == "right") {
            assert(m1.start(Direction::Forward, 512));
            assert(m2.start(Direction::Backward, 512));

        } else if (msg.substr(0, 4) == "back") {
            assert(m1.start(Direction::Backward, 512));
            assert(m2.start(Direction::Backward, 512));

        } else {
            LOGI("invalid command: %s", msg.c_str());
            return;
        }

        sleep(1);
        m1.stop();
        m2.stop();
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