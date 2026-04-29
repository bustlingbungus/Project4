#pragma once

#include <vector>
#include <string>
#include <memory>


class Terminal
{
    public:

        Terminal();
        ~Terminal();

        void free();


        void GetUserCommand();

        virtual bool HandleCommands();

        static bool InitTerminals();

        static void SwitchToTerminal(std::string trm_name);

    protected:

        virtual void PreInputLog();

        std::vector<std::string> cmdarr;

    private:

        void ParseInputBuffer();

        static bool has_access(std::string dst);
        
        std::string input_buffer;
};

extern std::shared_ptr<Terminal> terminal;
extern int user_access;