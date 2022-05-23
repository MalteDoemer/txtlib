
#include <iostream>

#include "TXTApplication.hpp"

class App : public TXTApplication {
public:
    App() { std::cout << "Starting ...\n"; }
};

int main()
{
    App app;
    return 0;
}