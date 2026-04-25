#pragma once

#include "Terminal.hpp"

#include <memory>


class HomePage : public Terminal
{
    public:

        HomePage();
        ~HomePage();

    protected:

        virtual void PreInputLog();
};

extern std::shared_ptr<Terminal> trm_homepage;