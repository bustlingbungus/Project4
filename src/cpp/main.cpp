#include <iostream>

#include "sys/systemcall.hpp"
#include "database/CafeDatabase.hpp"

int main(int argc, char** argv)
{
    // initialization protocol
    if (argc > 1)
    {
        if (std::string(argv[1]) == "init")
        {
            cafeDatabase.ResetSQLDatabase();
        }
    }

    cafeDatabase.RunSQLFile("cafe_queries.sql");
}