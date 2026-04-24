#include <iostream>

#include "sys/systemcall.hpp"
#include "misc.hpp"
#include "UserSettings.hpp"

int main(int argc, char** argv)
{
    userSettings.LoadSettings();

    // initialization protocol
    if (argc > 1)
    {
        if (std::string(argv[1]) == "init")
        {
            std::cout << "Performing initialization procedure...\n";
            // create database
            RunSQLFile("Initialization/cafe_db.sql", "cafe_db");

            // add procedures
            RunSQLFile("Tools/procedures.sql", "cafe_db");

            // add items to database
            RunSQLFile("Initialization/cafe_add_init_items.sql", "cafe_db");
            std::cout << "Database initialization complete.\n";
        }
    }

    RunSQLFile("Queries/cafe_queries.sql", "cafe_db");
}