#pragma once

#include <string>

class SQLDatabase
{
    public:

        SQLDatabase(std::string database_name);
        ~SQLDatabase();

        void RunSQLFile(std::string filename);
    
    protected:

        std::string sql_source_path = "None";
        std::string sql_username = "None";
        std::string sql_password = "None";

        std::string database = "None";

    private:

        void Init();

        bool is_initialized = false;

};
