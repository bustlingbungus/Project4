#include <iostream>

#include "terminal/Terminal.hpp"
#include "Init.hpp"


int main(int argc, char** argv)
{
    if (!Init(argc, argv)) return -1;


    bool quit = false;
    while (!quit && terminal != nullptr)
    {
        terminal->GetUserCommand();
        quit = terminal->HandleCommands();
    }

    return 0;
}