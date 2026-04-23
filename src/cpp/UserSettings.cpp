#include "UserSettings.hpp"

#include <iostream>

#include "sys/fileaccess.hpp"

UserSettings userSettings;

UserSettings::UserSettings()
{

}

UserSettings::~UserSettings()
{

}


void UserSettings::LoadSettings()
{
    std::ifstream file = OpenFile("settings.txt");
    if (!file || !file.is_open())
    {
        std::cerr << "Could not open settings file\n";
    }
    else
    {
        // iterate through each line.
        // When a label is found, it's respective value will be on the next line.
        // So, when a label is found, prepare its address to be loaded with the next value.
        
        std::string line;
        // pointers for each data type in config
        std::string* next_str = nullptr;

        // iterate through lines
        while (std::getline(file, line))
        {
            // there is a vale ready to be loaded
            if (next_str != nullptr)
            {
                *next_str = line;
                next_str = nullptr;
            }

            // check current line for labels
            else if (line == "sql_path")
                next_str = &sql_path;
            else if (line == "sql_username")
                next_str = &sql_username;
            else if (line == "sql_password")
                next_str = &sql_password;
        }
    }


    // since sql only correctly recognizes "/" in filenames (not "\"), we
    // need to replace all backslashes in the filenames with forward slashes.
    // fucking stupid shit
    for (int i = 0; i < sql_path.size(); ++i)
    {
        if (sql_path[i] == '\\') sql_path[i] = '/';
    }  
}