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

        void cmd_help(); // help
        void cmd_goto(); // goto
        void cmd_inventory(); // inventory
        void cmd_viewmenu(); // viewmenu
        void cmd_viewmenuingredients(); // viewingredients
        void cmd_viewcustomers(); // viewcustomers
        void cmd_viewsales(); // viewsales
        void cmd_viewemployees(); // employees

        void cmd_viewbalance(); // viewbalance

        void cmd_setinventory_amount(); // setamount, label, amount
        void cmd_removeinventoryitem(); // removeinventory, label
        void cmd_addmenuitem(); // addmenu, title, price, ...(ing_label, amount)...
        void cmd_removemenuitem(); // removemenu, title
        void cmd_removecustomer(); // removecustomer, phone
        void cmd_refundsale(); // refund, sale_id
        void cmd_addingredient(); // addingredient, item, ing, amount
        void cmd_addemployee(); // addemployee, username, password, name, access
        void cmd_removeemployee(); // removeemployee, username
};

extern std::shared_ptr<Terminal> trm_owner;