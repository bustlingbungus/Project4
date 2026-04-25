#pragma once

#include <vector>
#include <string>

class Terminal
{
    public:

        Terminal();
        ~Terminal();

        void free();


        void GetUserCommand();

        virtual bool HandleCommands();

    protected:

        virtual void PreInputLog();

        std::vector<std::string> cmdarr;

    private:

        void ParseInputBuffer();
        
        std::string input_buffer;
};
