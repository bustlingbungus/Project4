#pragma once

#include <iostream>

#include "database/CafeDatabase.hpp"
#include "terminal/Terminal.hpp"



inline bool Init(int argc, char** argv)
{
    // initialize database if requested by command line
    if (argc > 1)
    {
        if (std::string(argv[1]) == "init" && argc == 2) {
            cafeDatabase.ResetSQLDatabase();
        }
        else { // there exists a command line argument that is not 'init'
            std::cerr << "Unrecognized command line argument.\n";
            return false;
        }
    }

    // initialize terminals
    if (!Terminal::InitTerminals()) return false;

    return true;
}