
// #include <iostream>

#include <stdio.h>

#include "TXTApplication.hpp"

// Common debugging stuff for RoboProLib
unsigned int DebugFlags;
FILE* DebugFile;

class App : public TXTApplication {
public:
    App() { printf("hey"); }
};

int main()
{
    App app;
    return 0;
}