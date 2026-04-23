#include "misc.hpp"

#include <vector>
#include <iostream>

#include "UserSettings.hpp"
#include "sys/systemcall.hpp"

void RunSQLFile(std::string filename, std::string database)
{
    std::string cmd = "mysql";
    std::vector<std::string> cmdarr = {
        cmd,
        "-u",
        userSettings.sql_username,
        "-p",
        database,
        "-e",
        "\"SOURCE " + userSettings.sql_path + "/" + filename + ";\"",
        "--password=" + userSettings.sql_password
    };

    RunCommands(cmd, cmdarr);
}