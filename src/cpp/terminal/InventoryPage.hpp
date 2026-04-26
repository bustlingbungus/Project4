#pragma once

#include "Terminal.hpp"

#include <memory>


class InventoryPage : public Terminal
{
    public:

        InventoryPage();
        ~InventoryPage();

        virtual bool HandleCommands();

    protected:

        virtual void PreInputLog();

        void cmd_help(); // help
        void cmd_goto(); // goto
        void cmd_inventory(); // inventory
        void cmd_viewmenu(); // viewmenu
        void cmd_viewmenuingredients(); // viewingredients
        void cmd_viewsales(); // viewsales

        void cmd_setinventory_amount(); // setamount, name, amount
};

extern std::shared_ptr<Terminal> trm_inventory;