#include "SQLDatabase.hpp"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>

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
    std::string cmd = "mysql";
    std::vector<std::string> cmdarr = {
        cmd,
        "--defaults-extra-file=my.cnf",
        database,
        "-e",
        sql,
    };


    // open a new file using the last 
    int saved_file_output_desc = -1;
    int output_file_desc = STDOUT_FILENO;

    if (pipe_output)
    {
        int new_file_desc = open(pipe_filename.c_str(), O_CREAT | O_TRUNC | O_WRONLY, S_IRUSR | S_IWUSR);
        if (new_file_desc < 0) std::cerr << "failed to pipe output!\n";
        else
        {
            // save current output file
            saved_file_output_desc = dup(output_file_desc);
            if (saved_file_output_desc < 0) std::cerr << "failed to pipe output!\n";
            else 
            {
                // change output to new file
                if (dup2(new_file_desc, output_file_desc) < 0) std::cerr << "failed to pipe output!\n";
                close(new_file_desc);
            }
        }
    }

    RunCommands(cmd, cmdarr);

    if (pipe_output)
    {
        if (dup2(saved_file_output_desc, output_file_desc) < 0) std::cerr << "failed to pipe output!\n";
        close(saved_file_output_desc);
    }
}