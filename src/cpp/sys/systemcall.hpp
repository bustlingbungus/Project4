#pragma once

#include <vector>
#include <string>

int RunCommands(std::string cmd, std::vector<std::string> cmdarr);

int RunCommandsWithFileInput(std::string cmd, std::vector<std::string> cmdarr, std::string input_file);

int setcwd(std::string dir);

std::string getcwd();