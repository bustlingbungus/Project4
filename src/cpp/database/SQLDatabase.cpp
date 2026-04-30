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


void SQLDatabase::ExecSQL(std::string sql, bool pipe_output, std::string pipe_filename)
{
    // assemble a command line of the form "mysql --defaults-extra-file=my.cnf database -e CODE"
    std::string cmd = "mysql";
    std::vector<std::string> cmdarr = {
        cmd,
        "--defaults-extra-file=my.cnf",
        database,
        "-e",
        sql,
    };


    // get current file descriptor (console), to pipe the output 
    int output_file_desc = STDOUT_FILENO;
    int saved_output_file_desc = -1;

    // if requested, pipe output to some file
    if (pipe_output) {
        if (PipeOutput(pipe_filename, &output_file_desc, &saved_output_file_desc) < 0)
            std::cerr << "Failed to pipe output\n";
    }

    // run the command line in a seperate proccess
    RunCommands(cmd, cmdarr);

    // restore output to console
    if (pipe_output) {
        if (RestoreOutput(&saved_output_file_desc, &output_file_desc) < 0) 
            std::cerr << "Failed to restore output to console\n";
    }
}