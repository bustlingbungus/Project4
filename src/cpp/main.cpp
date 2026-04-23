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
            RunSQLFile("Initialization/cafe_db.sql", "cafe_db");
            RunSQLFile("Initialization/cafe_add_init_items.sql", "cafe_db");
        }
    }

    RunSQLFile("Queries/cafe_queries.sql", "cafe_db");
}