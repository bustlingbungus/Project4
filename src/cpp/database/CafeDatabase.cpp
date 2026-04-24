#include "CafeDatabase.hpp"

#include <iostream>

#include "../sys/fileaccess.hpp"
#include "../sys/systemcall.hpp"


CafeDatabase cafeDatabase;



CafeDatabase::CafeDatabase()
: SQLDatabase("cafe_db")
{

}


CafeDatabase::~CafeDatabase()
{

}


void CafeDatabase::ResetSQLDatabase()
{
    // drops database and creates tables
    RunSQLFile("cafe_db.sql");
    // add procedures
    RunSQLFile("procedures.sql");

    // add initial table entries

    // ingredients
    AddIngredient("Sugar", 10.00);
    AddIngredient("coffee grounds", 15.00);
    AddIngredient("tea leave", 4.00);
    AddIngredient("milk", 16.00);
    AddIngredient("creamer", 8.00);
    AddIngredient("almond milk", 8.00);
}


void CafeDatabase::AddIngredient(std::string label, float amount)
{
    std::string cmd = "mysql";
    std::vector<std::string> cmdarr = {
        cmd,
        "-u",
        sql_username,
        "-p",
        "cafe_db",
        "-e",
        "\"CALL add_ingredient(\'" + label + "\', " + std::to_string(amount) + ", @unused);\"",
        "--password=" + sql_password
    };

    RunCommands(cmd ,cmdarr);
}