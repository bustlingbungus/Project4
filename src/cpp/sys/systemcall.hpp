#pragma once

#include <vector>
#include <string>


int RunCommands(std::string cmd, std::vector<std::string> cmdarr);

int RunCommandsWithFileInput(std::string cmd, std::vector<std::string> cmdarr, std::string input_file);

int PipeOutput(std::string filename, int* output_file_desc, int* saved_output_file_desc);

int RestoreOutput(int* saved_output_file_desc, int* output_file_desc);