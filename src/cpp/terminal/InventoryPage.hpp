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

        void cmd_help();
        void cmd_goto();
        void cmd_inventory();
        void cmd_viewmenu();
        void cmd_viewmenuingredients();
        void cmd_viewsales();

        void cmd_setinventory_amount();
};

extern std::shared_ptr<Terminal> trm_inventory;