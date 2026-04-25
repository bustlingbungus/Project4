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
            std::cout << "Initializing database...\n";
            cafeDatabase.ResetSQLDatabase();
            std::cout << "Initialization complete.\n";
        }
    }

    cafeDatabase.AddCustomer("Jane Doe", "janedoe@gmail.com", "8131231234");
    cafeDatabase.AddSale(
        "coffee", 
        (Date){9,11,2001},
        "8131231234"
    );
    cafeDatabase.AddSale(
        "coffee", 
        (Date){9,12,2001}
    );

    cafeDatabase.RunSQLFile("cafe_queries.sql");
}