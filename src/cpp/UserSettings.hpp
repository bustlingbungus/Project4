#pragma once

#include <string>


class UserSettings
{
    public:

        UserSettings();
        ~UserSettings();

        std::string sql_path = "None";
        std::string sql_password = "None";
        std::string sql_username = "None";

        void LoadSettings();
};

extern UserSettings userSettings;