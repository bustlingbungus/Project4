#pragma once

#include "Terminal.hpp"

#include <memory>


class RegisterPage : public Terminal
{
    public:

        RegisterPage();
        ~RegisterPage();

        virtual bool HandleCommands();

    protected:

        virtual void PreInputLog();

        void cmd_help();
        void cmd_goto();
        void cmd_addsale();

};

extern std::shared_ptr<Terminal> trm_register;