#include "Terminal.hpp"

#include <iostream>

#include "HomePage.hpp"
#include "RegisterPage.hpp"
#include "InventoryPage.hpp"
#include "OwnerPage.hpp"
#include "Login.hpp"


std::shared_ptr<Terminal> terminal;
int user_access = -1;



Terminal::Terminal()
{

}


Terminal::~Terminal()
{
    free();
}


void Terminal::free()
{
    cmdarr.clear();
    input_buffer.clear();
}


void Terminal::GetUserCommand()
{
    PreInputLog();
    input_buffer.clear();
    std::getline(std::cin, input_buffer);
    ParseInputBuffer();
}


/**
 * Returns true if the input character is any type of whitespace character
 */
bool IsWhitespace(const char& ch)
{
    return ch == ' ' || ch == '\t' || ch == '\n' || ch == '\v' || ch == '\f' || ch == '\r';
}


bool Terminal::HandleCommands()
{
    if (cmdarr.size() > 0 && cmdarr[0] == "exit") return true;
    return false;
} 


void Terminal::PreInputLog()
{
    std::cout << "> ";
}


void Terminal::ParseInputBuffer()
{
    cmdarr.clear(); // reset command array

    int l = 0;
    int n = input_buffer.size();
    for (int i = 0; i < n; ++i)
    {
        char ch = input_buffer[i];

        // whitespace detected, if length is non-zero, add argument to command array
        if (IsWhitespace(ch))
        {
            int len = i - l;
            if (len > 0)
            {
                // get cmd as a substring and add to array
                std::string cmd = input_buffer.substr(l, len);
                cmdarr.push_back(cmd);
            }

            l = i + 1; // update length counter
        }
    }

    // after iterating, check if there is a final argument to add
    int len = n - l;
    if (len > 0)
        cmdarr.push_back(input_buffer.substr(l, len));
}


bool Terminal::InitTerminals()
{
    trm_homepage = std::make_shared<HomePage>();
    if (trm_homepage == nullptr) {
        std::cerr << "Failed to create homepage terminal.\n";
        return false;
    }
    
    trm_register = std::make_shared<RegisterPage>();
    if (trm_register == nullptr) {
        std::cerr << "Failed to create register terminal.\n";
        return false;
    }
    
    trm_inventory = std::make_shared<InventoryPage>();
    if (trm_inventory == nullptr) {
        std::cerr << "Failed to create inventory terminal.\n";
        return false;
    }
    
    trm_owner = std::make_shared<OwnerPage>();
    if (trm_owner == nullptr) {
        std::cerr << "Failed to create owner terminal.\n";
        return false;
    }
    
    trm_login = std::make_shared<Login>();
    if (trm_login == nullptr) {
        std::cerr << "Failed to create login terminal.\n";
        return false;
    }

    terminal = trm_login;
    return true;
}


void Terminal::SwitchToTerminal(std::string trm_name)
{
    if (!has_access(trm_name))
    {
        std::cout << "You lack access to the requested page.\n";
        return;
    }

    if (trm_name == "home") {
        terminal = trm_homepage;
    }
    else if (trm_name == "register") {
        terminal = trm_register;
    }
    else if (trm_name == "inventory") {
        terminal = trm_inventory;
    }
    else if (trm_name == "owner") {
        terminal = trm_owner;
    }
    else std::cerr << "Unrecognized page \'"+trm_name+"\'.\nAvailable pages:\n- home\n- register\n- inventory\n- owner\n";
}


bool Terminal::has_access(std::string dst)
{
    switch (user_access)
    {
        case 1:
            if (dst == "home") return true;
            if (dst == "register") return true;
            break;
        case 2:
            if (dst == "home") return true;
            if (dst == "register") return true;
            if (dst == "inventory") return true;
            break;
        case 3:
            if (dst == "home") return true;
            if (dst == "register") return true;
            if (dst == "inventory") return true;
            if (dst == "owner") return true;
            break;
        default:
            std::cerr << "Invalid access level\n";
    }
    return false;
}