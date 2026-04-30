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

        void cmd_help(); // help
        void cmd_goto(); // goto
        void cmd_addsale(); // addsale, item, (phone)
        void cmd_addcustomer(); // addcustomer, name, email, phone
        void cmd_viewsales(); // viewsales
        void cmd_refundsale(); // refundsale, sale_id
        void cmd_viewmenu(); // viewmenu

};

extern std::shared_ptr<Terminal> trm_register;