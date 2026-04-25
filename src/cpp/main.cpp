#include <iostream>

#include "sys/systemcall.hpp"
#include "database/CafeDatabase.hpp"
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



    cafeDatabase.AddCustomer("Jane_Doe", "janedoe@gmail.com", "8131231234");
    cafeDatabase.AddSale(
        "coffee", 
        (Date){9,11,2001},
        "8131231234"
    );
    cafeDatabase.AddSale(
        "coffee", 
        (Date){9,12,2001}
    );

    // cafeDatabase.RunSQLFile("cafe_queries.sql");
    cafeDatabase.QueryIngredients();
    cafeDatabase.QueryMenu();
    cafeDatabase.QueryCustomers();
    cafeDatabase.QuerySales();

    return 0;
}