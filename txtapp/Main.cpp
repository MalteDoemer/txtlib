
#include "SocketPP.h"
#include "TXTApplication.hpp"

// Common debugging stuff for RoboProLib
unsigned int DebugFlags;
FILE* DebugFile;

using namespace SocketPP;

constexpr int PORT = 5000;

class App : public TxtApplication {

private:
    TCPServer server;

public:
    App() : server(PORT)
    {
        server.setRecvHandle([&](const Message& message) { server.send(message); });
    }

    void run() { server.loop(); }
};

int main()
{
    App app;
    app.run();
    return 0;
}