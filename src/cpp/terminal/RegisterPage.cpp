#include "RegisterPage.hpp"

#include <iostream>

#include "HomePage.hpp"
#include "InventoryPage.hpp"
#include "OwnerPage.hpp"
#include "../Init.hpp"
#include "../database/CafeDatabase.hpp"

std::shared_ptr<Terminal> trm_register;


RegisterPage::RegisterPage()
: Terminal()
{

}


RegisterPage::~RegisterPage()
{

}


bool RegisterPage::HandleCommands()
{
    if (cmdarr.size() == 0) return false;
    if (cmdarr[0] == "exit") {
        if (cmdarr.size() == 1) return true;
        else std::cerr << "Unrecognized argument \'"+cmdarr[1]+"\'.\n";
    }
    else if (cmdarr[0] == "help") cmd_help();
    else if (cmdarr[0] == "goto") cmd_goto();
    else if (cmdarr[0] == "addsale") cmd_addsale();
    else if (cmdarr[0] == "addcustomer") cmd_addcustomer();
    else if (cmdarr[0] == "viewsales") cmd_viewsales();
    else if (cmdarr[0] == "refundsale") cmd_refundsale();
    else if (cmdarr[0] == "viewmenu") cmd_viewmenu();
    else {
        std::cerr << "Unrecognized command \'"+cmdarr[0]+"\'. Enter \'help\' for a list of commands.\n";
    }


    return false;
}


void RegisterPage::PreInputLog()
{
    std::cout << "Register> ";
}


void RegisterPage::cmd_help()
{
    if (cmdarr.size() > 1) std::cerr << "Unrecognized argument \'"+cmdarr[1]+"\'.\n";
    else
    {
        std::cout <<    "\nWelcome to the register. Here are a list of commands:\n\n"<<
                        "help\t\t-\tShow this page\n"<<
                        "exit\t\t-\tExit the application\n"<<
                        "\nviewsales\t-\tview all logged sales\n"<<
                        "viewmenu\t-\tview menu items\n"<<
                        "\nrefundsale <arg>\t-\tRefunds a sale, removing it from the reigster\n"<<
                        "<arguments>\n"<<
                        "- arg1: sale id. user \'viewsales\' to find the id of the sale you want to refund\n"<<
                        "\naddsale <args>\t-\tTender a sale to a customer. Add arguments to log the sale\n"<<
                        "<arguments>\n"<<
                        "- arg1: item sold\n"<<
                        "- arg2: current month\n"<<
                        "- arg3: current day\n"<<
                        "- arg4: current year\n"<<
                        "- arg5: customer's phone number (optional)\n"<<
                        "\naddcustomer <args>\t-\tRegister a new customer to our system. Add arguments to save customer information.\n"<<
                        "<arguments>\n"<<
                        "- arg1: customer name\n"<<
                        "- arg2: customer email\n"<<
                        "- arg3: customer phone number\n"<<
                        "\ngoto <flag>\t-\tGo to another page. Replace <flag> with the name of the desired page.\n"<<
                        "<available pages>\n"<<
                        "- home\n"<<
                        "- inventory\n"<<
                        "- owner\n"<<
                        "\n";
    }
}


void RegisterPage::cmd_addsale()
{
    if (cmdarr.size() != 5 && cmdarr.size() != 6) std::cerr << "Invalid argument count for \'addsale\' command.\n";
    else
    {
        Date date = {std::stoi(cmdarr[2]),std::stoi(cmdarr[3]),std::stoi(cmdarr[4])};
        if (cmdarr.size() == 5) cafeDatabase.AddSale(cmdarr[1], date);
        else cafeDatabase.AddSale(cmdarr[1], date, cmdarr[5]);
    }
}


void RegisterPage::cmd_goto()
{
    if (cmdarr.size() != 2) std::cerr << "Invalid argument count for \'goto\' command.\n";
    else
    {
        if (cmdarr[1] == "home") {
            terminal = trm_homepage;
        }
        else if (cmdarr[1] == "inventory") {
            terminal = trm_inventory;
        }
        else if (cmdarr[1] == "owner") {
            terminal = trm_owner;
        }
        else std::cerr << "Unrecognized page \'"+cmdarr[1]+"\'.\nAvailable pages:\n- home\n- inventory\n- owner\n";
    }
}


void RegisterPage::cmd_addcustomer()
{
    if (cmdarr.size() != 4) std::cerr << "Invalid argument count for \'addcustomer\' command.\n";
    else
    {
        cafeDatabase.AddCustomer(cmdarr[1], cmdarr[2], cmdarr[3]);
    }
}


void RegisterPage::cmd_viewsales()
{
    if (cmdarr.size() > 1) std::cerr << "Invalid argument count for \'viewsales\' command.\n";
    else {
        cafeDatabase.QuerySales();
    }
}


void RegisterPage::cmd_refundsale()
{
    if (cmdarr.size() != 2) std::cerr << "Invalid argument count for \'refundsale\' command.\n";
    else {
        cafeDatabase.RefundSale(std::stoi(cmdarr[1]));
    }
}

void RegisterPage::cmd_viewmenu()
{
    if (cmdarr.size() > 1) std::cerr << "Invalid argument count for \'viewmenu\'\n";
    else {
        cafeDatabase.QueryMenu();
    }
}