#include "HomePage.hpp"

#include <iostream>

#include "../Init.hpp"

std::shared_ptr<Terminal> trm_homepage;



HomePage::HomePage()
: Terminal()
{

}


HomePage::~HomePage()
{

}


bool HomePage::HandleCommands()
{
    if (cmdarr.size() == 0) return false;
    if (cmdarr[0] == "exit") {
        if (cmdarr.size() == 1) return true;
        else std::cerr << "Unrecognized argument \'"+cmdarr[1]+"\'.\n";
    }
    else if (cmdarr[0] == "help") cmd_help();
    else if (cmdarr[0] == "goto") cmd_goto();
    else {
        std::cerr << "Unrecognized command \'"+cmdarr[0]+"\'. Enter \'help\' for a list of commands.\n";
    }


    return false;
}


void HomePage::PreInputLog()
{
    std::cout << "Home Page> ";
}


void HomePage::cmd_help()
{
    if (cmdarr.size() > 1) std::cerr << "Unrecognized argument \'"+cmdarr[1]+"\'.\n";
    else
    {
        std::cout <<    "\nWelcome to the Home Page. Here are a list of commands:\n\n"<<
                        "help\t\t-\tShow this page\n"<<
                        "exit\t\t-\tExit the application\n"<<
                        "goto <flag>\t-\tGo to another page. Replace <flag> with the name of the desired page.\n"<<
                        "<available pages>\n"<<
                        "- register\n"<<
                        "- inventory\n"<<
                        "- owner\n"<<
                        "\n";
    }
}


void HomePage::cmd_goto()
{
    if (cmdarr.size() != 2) std::cerr << "Invalid argument count for \'goto\' command.\n";
    else
    {
        Terminal::SwitchToTerminal(cmdarr[1]);
    }
}