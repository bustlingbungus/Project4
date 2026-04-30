#pragma once

#include <string>

class SQLDatabase
{
    public:

        SQLDatabase(std::string database_name);
        ~SQLDatabase();
    
        void ExecSQL(std::string sql, bool pipe_output = false, std::string pipe_filename = "a.txt");

        // Pipes a .sql file directly into mysql via stdin.
        // Set use_database=false when the file itself creates the database (e.g. cafe_db.sql).
        void ExecSQLFile(std::string filename, bool use_database = true);

    protected:
        

        std::string database = "None";
};
