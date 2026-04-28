#pragma once

#include <string>

class SQLDatabase
{
    public:

        SQLDatabase(std::string database_name);
        ~SQLDatabase();
    
    protected:
        
        void ExecSQL(std::string sql);

        std::string database = "None";
};
