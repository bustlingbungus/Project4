#include "InventoryPage.hpp"

#include <iostream>

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
    std::cout <<"[ "<<cafeDatabase.CurrDate().to_string()<<" ] Inventory> ";
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
    if (cmdarr.size() > 1) std::cerr << "Unrecognized argument \'"+cmdarr[1]+"\'.\n";
    else
    {
        std::cout <<    "\nWelcome to the Inventory Page. Here are a list of commands:\n\n"<<
                        "help\t\t-\tShow this page\n"<<
                        "exit\t\t-\tExit the application\n"<<
                        "\ninventory\t-\tShow current amounts of inventory items\n"<<
                        "viewmenu\t-\tShows the menu items\n"<<
                        "viewingredients\t-\tShows the ingredients used by each menu item\n"<<
                        "viewsales\t-\tShows all sales on record\n"<<
                        "\nsetamount <args>\t-\tSet the amount of an inventory item. If the item is not currently in inventory, it will be added\n"<<
                        "<arguments>\n"<<
                        "- arg1: Ingredient label\n"<<
                        "- arg2: amount of the ingredient in stock\n"<<
                        "\ngoto <flag>\t-\tGo to another page. Replace <flag> with the name of the desired page.\n"<<
                        "<available pages>\n"<<
                        "- home\n"<<
                        "- register\n"<<
                        "- owner\n"<<
                        "\n";
    }
}


void InventoryPage::cmd_goto()
{
    if (cmdarr.size() != 2) std::cerr << "Invalid argument count for \'goto\' command.\n";
    else
    {
        Terminal::SwitchToTerminal(cmdarr[1]);
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