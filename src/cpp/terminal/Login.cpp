#include "Login.hpp"

#include <iostream>

#include "../database/CafeDatabase.hpp"
#include "../sys/fileaccess.hpp"


std::shared_ptr<Login> trm_login;



Login::Login()
: Terminal()
{

}


Login::~Login()
{

}


void Login::PreInputLog()
{
    if (accept_password) std::cout << "Password: ";
    else std::cout << "Username: ";
}


bool Login::HandleCommands()
{
    if (cmdarr.size() == 0) return false;
    if (cmdarr[0] == "exit") {
        if (cmdarr.size() == 1) return true;
        else std::cerr << "Unrecognized argument \'"+cmdarr[1]+"\'.\n";
    }
    else if (accept_password) InterpretPassword();
    else InterpretUsername();

    return false;
}


void Login::InterpretUsername()
{
    if (cmdarr.size() != 1) std::cerr << "Please enter your (one word) username.\n";
    else
    {
        if (IsValidUsername())
        {
            accept_password = true;
            username = cmdarr[0];
        }
        else std::cout << "Unrecognized username.\n";
    }
}


void Login::InterpretPassword()
{
    if (cmdarr.size() != 1) std::cerr << "Please enter your (one word) password.\n";
    else
    {
        if (IsValidPassword())
        {
            user_access = GetAccessLevel();
            Terminal::SwitchToTerminal("home");
        }
        else std::cout << "Incorrect password.\n";
    }
    accept_password = false;
    username = "NULL";
}


bool Login::IsValidUsername()
{
    cafeDatabase.ExecSQL("\"CALL user_exists(\'"+cmdarr[0]+"\');\"", true);
    std::ifstream file = OpenFile("a.txt");
    if (!file) std::cerr << "Failed to interpret username.\n";
    else
    {
        std::string str;
        if ((file >> str >> str)) {
            if (std::stoi(str) == 1) return true;
        } else std::cerr << "Failed to read username result.\n";
    }

    return false;
}


bool Login::IsValidPassword()
{
    cafeDatabase.ExecSQL("\"CALL valid_password(\'"+username+"\',\'"+cmdarr[0]+"\');\"", true);
    std::ifstream file = OpenFile("a.txt");
    if (!file) std::cerr << "Failed to interpret username.\n";
    else
    {
        std::string str;
        if ((file >> str >> str)) {
            if (std::stoi(str) == 1) return true;
        } else std::cerr << "Failed to read password result.\n";
    }

    return false;
}


int Login::GetAccessLevel()
{
    cafeDatabase.ExecSQL("\"CALL get_access(\'"+username+"\');\"", true);
    std::ifstream file = OpenFile("a.txt");
    if (!file) std::cerr << "Failed to get access level.\n";
    else
    {
        std::string str;
        if ((file >> str >> str)) {
            return std::stoi(str);
        } else std::cerr << "Failed to read access level.\n";
    }

    return -1;
}