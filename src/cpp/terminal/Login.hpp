#pragma once

#include "Terminal.hpp"


class Login : public Terminal
{
    public:

        Login();
        ~Login();

        virtual bool HandleCommands();

    protected:

        virtual void PreInputLog();

        void InterpretUsername();
        void InterpretPassword();

        bool IsValidUsername();
        bool IsValidPassword();

        int GetAccessLevel();

        bool accept_password = false;
        std::string username = "NULL";
};

extern std::shared_ptr<Login> trm_login;