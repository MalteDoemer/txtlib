#include <iostream>

#include "explorer.hpp"

// Necessary debugging stuff for RoboProLib
unsigned int DebugFlags;
FILE* DebugFile;


int main()
{
    std::cout << "starting app...\n";

    txt::explorer explorer;
    explorer.start();

    return 0;
}
