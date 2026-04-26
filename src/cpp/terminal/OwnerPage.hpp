#pragma once

#include "Terminal.hpp"

#include <memory>


class OwnerPage : public Terminal
{
    public:

        OwnerPage();
        ~OwnerPage();

        virtual bool HandleCommands();

    protected:

        virtual void PreInputLog();

        void cmd_help();
        void cmd_goto();
        void cmd_inventory();
        void cmd_viewmenu();
        void cmd_viewmenuingredients();
        void cmd_viewcustomers();
        void cmd_viewsales();

        void cmd_viewbalance();

        void cmd_setinventory_amount();
        void cmd_removeinventoryitem();
        void cmd_addmenuitem();
        void cmd_removemenuitem();
        void cmd_removecustomer();
        void cmd_refundsale();
};

std::shared_ptr<Terminal> trm_owner;