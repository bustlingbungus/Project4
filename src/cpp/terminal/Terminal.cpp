#include "Terminal.hpp"

#include <iostream>

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
