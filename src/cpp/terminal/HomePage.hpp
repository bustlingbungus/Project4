#pragma once

#include "Terminal.hpp"

#include <memory>


class HomePage : public Terminal
{
    public:

        HomePage();
        ~HomePage();

        virtual bool HandleCommands();

    protected:

        virtual void PreInputLog();

        void PrintCommands();
};

extern std::shared_ptr<Terminal> trm_homepage;