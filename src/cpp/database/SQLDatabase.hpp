#pragma once

#include <string>

class SQLDatabase
{
    public:

        SQLDatabase(std::string database_name);
        ~SQLDatabase();
    
        void ExecSQL(std::string sql, bool pipe_output = false, std::string pipe_filename = "a.txt");

    protected:
        
        std::string database = "None";
};
