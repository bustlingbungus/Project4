#include "OwnerPage.hpp"

#include <iostream>

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


void OwnerPage::PreInputLog()
{
    std::cout << "Owner> ";
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
    else if (cmdarr[0] == "addingredient") cmd_addingredient();
    else if (cmdarr[0] == "employees") cmd_viewemployees();
    else if (cmdarr[0] == "addemployee") cmd_addemployee();
    else if (cmdarr[0] == "removeemployee") cmd_removeemployee();
    else {
        std::cerr << "Unrecognized command \'"+cmdarr[0]+"\'. Enter \'help\' for a list of commands.\n";
    }


    return false;
}


void OwnerPage::cmd_help()
{
    if (cmdarr.size() > 1) std::cerr << "Unrecognized argument \'"+cmdarr[1]+"\'.\n";
    else
    {
        std::cout <<    "\nWelcome to the Owner Page. Here are a list of commands:\n\n"<<
                        "help\t\t-\tShow this page\n"<<
                        "exit\t\t-\tExit the application\n"<<
                        "\ninventory\t-\tShow current amounts of inventory items\n"<<
                        "viewmenu\t-\tShows the menu items\n"<<
                        "viewingredients\t-\tShows the ingredients used by each menu item\n"<<
                        "viewcustomers\t-\tShows all customers on record, as well as how many points they have\n"<<
                        "viewsales\t-\tShows all sales on record\n"<<
                        "employees\t-\tShows all employees in system\n"<<
                        "viewbalance\t-\tShows the sum of all sale prices\n"<<
                        "\nsetamount <args>\t-\tSet the amount of an inventory item. If the item is not currently in inventory, it will be added\n"<<
                        "<arguments>\n"<<
                        "- arg1: Ingredient label\n"<<
                        "- arg2: amount of the ingredient in stock\n"<<
                        "\nremoveinventory <args>\t-\tRemove an item from our inventory\n"<<
                        "<arguments>\n"<<
                        "- arg1: Name of the item to remove\n"<<
                        "\naddmenu <args...>\t-\tAdds an item to the menu\n"<<
                        "<arguments>\n"<<
                        "- arg1: Name of the new menu item\n"<<
                        "- arg2: item price\n"<<
                        "- arg3: name of ingredient in this item\n"<<
                        "- arg4: amount of ingredient used\n"<<
                        "- args 3 and 4 may be repeated as many times as neccesary, for as many ingredients as the item uses.\n"<<
                        "\nremovemenu <args>\t-\tRemove an item from the menu\n"<<
                        "<arguments>\n"<<
                        "- arg1: Name of the item to remove\n"<<
                        "\nremovecustomer <args>\t-\tRemove a customer from our record\n"<<
                        "<arguments>\n"<<
                        "- arg1: Phone number of the customer to remove\n"<<
                        "\nrefund <args>\t-\tRefunds a sale. Use \'viewsales\' to find sale ids.\n"<<
                        "<arguments>\n"<<
                        "- arg1: id of the sale to refund\n"<<
                        "\naddingredient <args>\t-\tAdds an ingredient to the recipe of an existing menu item\n"<<
                        "<arguments>\n"<<
                        "- arg1: Name of the item you want to add an ingredient to\n"<<
                        "- arg2: Name of the ingredient to add\n"<<
                        "- arg3: Amount of the ingredient used in the recipe\n"<<
                        "\naddemployee <args>\t-\tAdds an employee to the system\n"<<
                        "<arguments>\n"<<
                        "- arg1: Employee username\n"<<
                        "- arg2: Employee password\n"<<
                        "- arg3: employee name\n"<<
                        "- arg4: access level. 1 = register, 2 = inventory, 3 = owner\n"<<
                        "\nremoveemployee <args>\t-\tRemoves an employee from the system\n"<<
                        "<arguments>\n"<<
                        "- arg1: Employee username\n"<<
                        "\ngoto <flag>\t-\tGo to another page. Replace <flag> with the name of the desired page.\n"<<
                        "<available pages>\n"<<
                        "- home\n"<<
                        "- register\n"<<
                        "- inventory\n"<<
                        "\n";
    }
}


void OwnerPage::cmd_goto()
{
    if (cmdarr.size() != 2) std::cerr << "Invalid argument count for \'goto\' command.\n";
    else
    {
        Terminal::SwitchToTerminal(cmdarr[1]);
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


void OwnerPage::cmd_viewemployees()
{
    if (cmdarr.size() != 1) std::cerr << "Invalid argument count for \'employees\' command.\n";
    else {
        cafeDatabase.QueryEmployees();
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


void OwnerPage::cmd_removeinventoryitem()
{
    if (cmdarr.size() != 2) std::cerr << "Invalid argument count for \'removeinventory\' command\n";
    else {
        cafeDatabase.RemoveIngredient(cmdarr[1]);
    }
}


void OwnerPage::cmd_addmenuitem()
{
    if (cmdarr.size() < 3) std::cerr << "Too few arguments for \'addmenu\' command.\n";
    else
    {
        std::vector<Ingredient> ingredients;
        for (int i = 4; i < cmdarr.size(); i += 2)
        {
            Ingredient ing = {cmdarr[i - 1], std::stof(cmdarr[i])};
            ingredients.push_back(ing);
        }

        cafeDatabase.AddMenuItem(cmdarr[1], std::stof(cmdarr[2]), ingredients);
    }
}


void OwnerPage::cmd_removemenuitem()
{
    if (cmdarr.size() != 2) std::cerr << "Incorrect argument count for \'removemenu\' command.\n";
    else {
        cafeDatabase.RemoveMenuItem(cmdarr[1]);
    }
}


void OwnerPage::cmd_removecustomer()
{
    if (cmdarr.size() != 2) std::cerr << "Incorrect argument count for \'removecustomer\' command.\n";
    else {
        cafeDatabase.RemoveCustomer(cmdarr[1]);
    }
}


void OwnerPage::cmd_refundsale()
{
    if (cmdarr.size() != 2) std::cerr << "Incorrect argument count for \'refund\' command.\n";
    else {
        cafeDatabase.RefundSale(std::stoi(cmdarr[1]));
    }
}


void OwnerPage::cmd_addingredient()
{
    if (cmdarr.size() != 4) std::cerr << "Incorrect argument count for \'addingredient\' command.\n";
    else {
        cafeDatabase.AddIngredient(cmdarr[1], cmdarr[2], std::stof(cmdarr[3]));
    }
}


void OwnerPage::cmd_addemployee()
{
    if (cmdarr.size() != 5) std::cerr << "Incorrect argument count for \'addemployee\' command.\n";
    else {
        cafeDatabase.AddEmployee(cmdarr[1], cmdarr[2], cmdarr[3], std::stoi(cmdarr[4]));
    }
}


void OwnerPage::cmd_removeemployee()
{
    if (cmdarr.size() != 2) std::cerr << "Incorrect argument count for \'removeemployee\' command.\n";
    else {
        cafeDatabase.RemoveEmployee(cmdarr[1]);
    }
}