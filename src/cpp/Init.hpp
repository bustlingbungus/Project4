#pragma once

#include <memory>

#include "terminal/Terminal.hpp"


extern std::shared_ptr<Terminal> terminal;


bool Init(int argc, char** argv);