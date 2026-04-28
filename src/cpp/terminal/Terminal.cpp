#include "Terminal.hpp"

#include <iostream>

#include "HomePage.hpp"
#include "RegisterPage.hpp"
#include "InventoryPage.hpp"
#include "OwnerPage.hpp"


std::shared_ptr<Terminal> terminal;



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

    terminal = trm_homepage;
    return true;
}


void Terminal::SwitchToTerminal(std::string trm_name)
{
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