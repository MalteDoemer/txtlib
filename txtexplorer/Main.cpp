
#include <iostream>

// #include <JsonRPCServer.hpp>

#include "Explorer.hpp"

// Necessary debugging stuff for RoboProLib
unsigned int DebugFlags;
FILE* DebugFile;


int main()
{
    std::cout << "starting app...\n";

    explorer::app app;
    app.start();

    return 0;
}
