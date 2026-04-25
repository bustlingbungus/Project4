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
        void cmd_addcustomer();
        void cmd_viewsales();
        void cmd_refundsale();

};

extern std::shared_ptr<Terminal> trm_register;