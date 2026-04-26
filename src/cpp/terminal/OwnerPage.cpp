#include "OwnerPage.hpp"

#include <iostream>

#include "HomePage.hpp"
#include "../Init.hpp"
#include "../database/CafeDatabase.hpp"

std::shared_ptr<Terminal> trm_owner;


OwnerPage::OwnerPage()
: Terminal()
{

}


OwnerPage::~OwnerPage()
{

}


bool OwnerPage::HandleCommands()
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
    else if (cmdarr[0] == "viewcustomers") cmd_viewcustomers();
    else if (cmdarr[0] == "viewsales") cmd_viewsales();
    else if (cmdarr[0] == "viewbalance") cmd_viewbalance();
    else if (cmdarr[0] == "setamount") cmd_setinventory_amount();
    else if (cmdarr[0] == "removeinventory") cmd_removeinventoryitem();
    else if (cmdarr[0] == "addmenu") cmd_addmenuitem();
    else if (cmdarr[0] == "removemenu") cmd_removemenuitem();
    else if (cmdarr[0] == "removecustomer") cmd_removecustomer();
    else if (cmdarr[0] == "refund") cmd_refundsale();
    else {
        std::cerr << "Unrecognized command \'"+cmdarr[0]+"\'. Enter \'help\' for a list of commands.\n";
    }


    return false;
}


void OwnerPage::cmd_help()
{

}


void OwnerPage::cmd_goto()
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


void OwnerPage::cmd_inventory()
{
    if (cmdarr.size() != 1) std::cerr << "Invalid arguent count for \'inventory\' command.\n";
    else {
        cafeDatabase.QueryIngredients();
    }
}

void OwnerPage::cmd_viewmenu()
{
    if (cmdarr.size() != 1) std::cerr << "Invalid arguent count for \'viewmenu\' command.\n";
    else {
        cafeDatabase.QueryMenu();
    }
}


void OwnerPage::cmd_viewmenuingredients()
{
    if (cmdarr.size() != 1) std::cerr << "Invalid arguent count for \'viewingredients\' command.\n";
    else {
        cafeDatabase.QueryMenuItemIngredients();
    }
}


void OwnerPage::cmd_viewcustomers()
{
    if (cmdarr.size() != 1) std::cerr << "Invalid arguent count for \'viewcustomers\' command.\n";
    else {
        cafeDatabase.QueryCustomers();
    }
}


void OwnerPage::cmd_viewsales()
{
    if (cmdarr.size() != 1) std::cerr << "Invalid arguent count for \'viewsales\' command.\n";
    else {
        cafeDatabase.QuerySales();
    }
}

void OwnerPage::cmd_viewbalance()
{
    if (cmdarr.size() != 1) std::cerr << "Invalid arguent count for \'viewbalance\' command.\n";
    else {
        cafeDatabase.QuerySaleTotal();
    }
}


void OwnerPage::cmd_setinventory_amount()
{
    if (cmdarr.size() != 3) std::cerr << "Invalid argument count for \'setamount\' command\n";
    else {
        cafeDatabase.AddIngredient(cmdarr[1], std::stof(cmdarr[2]));
    }
}