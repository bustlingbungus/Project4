#include "SQLDatabase.hpp"

#include <iostream>

#include "../sys/fileaccess.hpp"
#include "../sys/systemcall.hpp"



SQLDatabase::SQLDatabase(std::string database_name)
: database(database_name)
{
    
}


SQLDatabase::~SQLDatabase()
{
    database.clear();
}


void SQLDatabase::ExecSQL(std::string sql)
{
    std::string cmd = "mysql";
    std::vector<std::string> cmdarr = {
        cmd,
        "--defaults-extra-file=my.cnf",
        database,
        "-e",
        sql
    };

    RunCommands(cmd, cmdarr);
}