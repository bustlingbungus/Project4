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


void HomePage::PreInputLog()
{
    std::cout << "Welcome to the home page> ";
}