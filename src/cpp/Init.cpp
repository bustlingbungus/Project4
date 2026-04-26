#include "Init.hpp"

#include <iostream>

#include "database/CafeDatabase.hpp"
#include "terminal/HomePage.hpp"
#include "terminal/RegisterPage.hpp"
#include "terminal/InventoryPage.hpp"
#include "terminal/OwnerPage.hpp"

std::shared_ptr<Terminal> terminal;



bool Init(int argc, char** argv)
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
    trm_homepage = std::make_shared<HomePage>();
    if (trm_homepage == nullptr) {
        std::cerr << "Failed to create homepage terminal.\n";
        return false;
    }
    
    trm_register = std::make_shared<RegisterPage>();
    if (trm_register == nullptr) {
        std::cerr << "Failed to create register terminal.\n";
        return false;
    }
    
    trm_inventory = std::make_shared<InventoryPage>();
    if (trm_inventory == nullptr) {
        std::cerr << "Failed to create inventory terminal.\n";
        return false;
    }
    
    trm_owner = std::make_shared<OwnerPage>();
    if (trm_owner == nullptr) {
        std::cerr << "Failed to create owner terminal.\n";
        return false;
    }

    terminal = trm_homepage;

    return true;
}