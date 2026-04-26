#include "InventoryPage.hpp"

#include <iostream>

#include "HomePage.hpp"
#include "../Init.hpp"
#include "../database/CafeDatabase.hpp"


std::shared_ptr<Terminal> trm_inventory;


InventoryPage::InventoryPage()
: Terminal()
{

}


InventoryPage::~InventoryPage()
{

}


void InventoryPage::PreInputLog()
{
    std::cout << "Inventory> ";
}


bool InventoryPage::HandleCommands()
{
    if (cmdarr.size() == 0) return false;
    if (cmdarr[0] == "exit") {
        if (cmdarr.size() == 1) return true;
        else std::cerr << "Unrecognized argument \'"+cmdarr[1]+"\'.\n";
    }
    else if (cmdarr[0] == "help") cmd_help();
    else if (cmdarr[0] == "goto") cmd_goto();
    else if (cmdarr[0] == "inventory") cmd_inventory();
    else if (cmdarr[0] == "viewmenu") cmd_viewmenu();
    else if (cmdarr[0] == "viewingredients") cmd_viewmenuingredients();
    else if (cmdarr[0] == "viewsales") cmd_viewsales();
    else if (cmdarr[0] == "setamount") cmd_setinventory_amount();
    else {
        std::cerr << "Unrecognized command \'"+cmdarr[0]+"\'. Enter \'help\' for a list of commands.\n";
    }


    return false;
}


void InventoryPage::cmd_help()
{
    
}


void InventoryPage::cmd_goto()
{
    if (cmdarr.size() != 2) std::cerr << "Invalid argument count for \'goto\' command.\n";
    else
    {
        if (cmdarr[1] == "home") {
            terminal = trm_homepage;
        }
        else std::cerr << "Unrecognized page \'"+cmdarr[1]+"\'.\nAvailable pages:\n- home\n- inventory\n";
    }
}


void InventoryPage::cmd_inventory()
{
    if (cmdarr.size() != 1) std::cerr << "Invalid arguent count for \'inventory\' command.\n";
    else {
        cafeDatabase.QueryIngredients();
    }
}

void InventoryPage::cmd_viewmenu()
{
    if (cmdarr.size() != 1) std::cerr << "Invalid arguent count for \'viewmenu\' command.\n";
    else {
        cafeDatabase.QueryMenu();
    }
}


void InventoryPage::cmd_viewmenuingredients()
{
    if (cmdarr.size() != 1) std::cerr << "Invalid arguent count for \'viewingredients\' command.\n";
    else {
        cafeDatabase.QueryMenuItemIngredients();
    }
}


void InventoryPage::cmd_viewsales()
{
    if (cmdarr.size() != 1) std::cerr << "Invalid arguent count for \'viewsales\' command.\n";
    else {
        cafeDatabase.QuerySales();
    }
}


void InventoryPage::cmd_setinventory_amount()
{
    if (cmdarr.size() != 3) std::cerr << "Invalid argument count for \'setamount\' command\n";
    else {
        cafeDatabase.AddIngredient(cmdarr[1], std::stof(cmdarr[2]));
    }
}