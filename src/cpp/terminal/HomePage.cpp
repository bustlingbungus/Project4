#include "HomePage.hpp"

#include <iostream>

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

    else if (cmdarr[0] == "help") {
        if (cmdarr.size() > 1) std::cerr << "Unrecognized argument \'"+cmdarr[1]+"\'.\n";
        else PrintCommands();
    }

    else if (cmdarr[0] == "goto")
    {
        if (cmdarr.size() != 2) std::cerr << "Invalid argument count for \'goto\' command.\n";
        else
        {
            if (cmdarr[1] == "register") {

            }
            else if (cmdarr[1] == "inventory") {

            }
            else std::cerr << "Unrecognized page \'"+cmdarr[1]+"\'.\nAvailable pages:\n- register\n- inventory\n";
        }
    }

    else {
        std::cerr << "Unrecognized command \'"+cmdarr[0]+"\'. Enter \'help\' for a list of commands.\n";
    }


    return false;
}


void HomePage::PreInputLog()
{
    std::cout << "Home Page> ";
}


void HomePage::PrintCommands()
{
    std::cout <<    "\nWelcome to the Home Page. Here are a list of commands:\n\n"<<
                    "help\t\t-\tShow this page\n"<<
                    "exit\t\t-\tExit the application\n"<<
                    "goto <flag>\t-\tGo to another page. Replace <flag> with the name of the desired page.\n"<<
                    "<available pages>\n"<<
                    "- register\n"<<
                    "- inventory\n"<<
                    "\n";
}