
#include <iostream>

// #include <JsonRPCServer.hpp>

#include "Explorer.hpp"

// Necessary debugging stuff for RoboProLib
unsigned int DebugFlags;
FILE* DebugFile;

int test(int a)
{
    std::cout << "test() called...\n";
    return a + 1;
}

int main()
{
    std::cout << "starting app...\n";

    // txt::net::jsonrpc_server server(8484, "/test");

    // server.add("test", jsonrpccxx::GetHandle(test), { "t" });

    // server.start_listening();

    explorer::app app;
    app.start();

    return 0;
}
