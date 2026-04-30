#include "systemcall.hpp"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>

#ifdef _WIN32 // windows
#include <windows.h>
#include <direct.h>
#elif defined(__unix__) || defined(__linux__) || defined(__APPLE__) // unix OS
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#endif // _WIN32



/**
 * Uses system calls to execute the desired command, and passing an array
 * of arguments onto the command line.
 * 
 * \note For most OS, cmdarr[0] should be the same as cmd. 
 * cmd should be the entire path to the command being executed.
 * 
 * \param cmd The command being executed
 * \param cmdarr Array of arguments being put on the command line
 * 
 * \return `0` for successful execution. 
 * \return `-1` for all errors
 */
int RunCommands(std::string cmd, std::vector<std::string> cmdarr)
{
#ifdef _WIN32 // windows 

    // convert the argument array into a single command line string
    std::string cmdline = "";
    for (std::string& cmd : cmdarr) cmdline += cmd + ' ';

    // set up structure for new process
    PROCESS_INFORMATION processInfo;
    ZeroMemory(&processInfo, sizeof(processInfo));
    STARTUPINFO startupInfo;
    ZeroMemory(&startupInfo, sizeof(startupInfo));
    startupInfo.cb = sizeof(startupInfo);

    // create child process using the command line
    if (CreateProcess(
        NULL, 
        (LPSTR)cmdline.c_str(),
        NULL,
        NULL,
        FALSE,
        0,
        NULL,
        NULL,
        &startupInfo,
        &processInfo))
    {
        // wait the the child process to finish executing
        WaitForSingleObject(processInfo.hProcess, INFINITE);
        // close child process when done
        CloseHandle(processInfo.hProcess);
        CloseHandle(processInfo.hThread);
    }   
    else // process failed to create
    {
        std::cerr << "Failed to execute command \'" << cmdline << "\'\n";
        return -1;
    }

    return 0;

#elif defined(__unix__) || defined(__linux__) || defined(__APPLE__) // unix OS

    // convert cmdarr to null a terminated char** array for execv
    const char** c_cmdarr = (const char**)malloc((cmdarr.size() + 1) * sizeof(const char*));
    if (c_cmdarr == NULL) {
        std::cerr << "`malloc` failure.\n";
        return -1;
    }
    // copy command array as c strings
    for (int i = 0; i < cmdarr.size(); ++i) c_cmdarr[i] = cmdarr[i].c_str();
    c_cmdarr[cmdarr.size()] = NULL; // add null terminator

    // create a new process to call execv in
    pid_t p = fork();
    if (p < 0) 
    {
        std::cerr << "Failed to execute command \'" << cmd << "\'\n";
        free(c_cmdarr);
        return -1;
    }
    else
    {
        // execute commands in child branch
        if (p == 0)
        {
            execvp(cmd.c_str(), (char* const*)c_cmdarr);
            exit(0);
        }
        // wait for child in parent branch
        else
        {
            int status;
            waitpid(p, &status, 0);
        }
    }

    free(c_cmdarr);
    return 0;

#else
    std::cerr << "Unsupported operating system\n";
    return -1;
#endif // _WIN32
}


/**
 * Changes cout output location to any provided filename, so that console logs print to that 
 * file rather than the console.
 * 
 * \param filename Name of the new output location
 * \param output_file_desc File descriptor of the current output location. `STDOUT_FILENO` for the console
 * \param saved_output_file_desc Current output description will be saved here, so you can maintain the reference after the swap occurs
 * 
 * \returns The file descriptor for the new output location. -1 If there was an error
 */
int PipeOutput(std::string filename, int* output_file_desc, int* saved_output_file_desc)
{
    // open new output file
    int new_file_desc = open(filename.c_str(), O_CREAT | O_TRUNC | O_WRONLY, S_IRUSR | S_IWUSR);
    if (new_file_desc < 0) return -1;
    else
    {
        // save current output file
        *saved_output_file_desc = dup(*output_file_desc);
        if (*saved_output_file_desc < 0) return -1;
        else 
        {
            // change output to new file
            if (dup2(new_file_desc, *output_file_desc) < 0) return -1;
            close(new_file_desc);
        }
    }
    return new_file_desc;
}


/**
 * Same as RunCommands, but redirects the child process's stdin from the
 * given file. Used for piping SQL files directly into mysql.
 */
int RunCommandsWithFileInput(std::string cmd, std::vector<std::string> cmdarr, std::string input_file)
{
#ifdef _WIN32
    std::cerr << "RunCommandsWithFileInput not supported on Windows\n";
    return -1;
#elif defined(__unix__) || defined(__linux__) || defined(__APPLE__)
    const char** c_cmdarr = (const char**)malloc((cmdarr.size() + 1) * sizeof(const char*));
    if (c_cmdarr == NULL) {
        std::cerr << "`malloc` failure.\n";
        return -1;
    }
    for (int i = 0; i < (int)cmdarr.size(); ++i) c_cmdarr[i] = cmdarr[i].c_str();
    c_cmdarr[cmdarr.size()] = NULL;

    pid_t p = fork();
    if (p < 0) {
        std::cerr << "Failed to execute command '" << cmd << "'\n";
        free(c_cmdarr);
        return -1;
    }
    else if (p == 0) {
        // redirect stdin from the SQL file
        int fd = open(input_file.c_str(), O_RDONLY);
        if (fd >= 0) {
            dup2(fd, STDIN_FILENO);
            close(fd);
        }
        execvp(cmd.c_str(), (char* const*)c_cmdarr);
        exit(1);
    }
    else {
        int status;
        waitpid(p, &status, 0);
    }

    free(c_cmdarr);
    return 0;
#else
    std::cerr << "Unsupported operating system\n";
    return -1;
#endif
}


/**
 * Restores an altered output location to the descriptor saved in `saved_output_file_desc`.
 *
 * \param saved_output_file_desc File descriptor of an old output location
 * \param output_file_desc Location for descriptor to be stored
 *
 * \returns 0 for success, -1 for failure
 */
int RestoreOutput(int* saved_output_file_desc, int* output_file_desc)
{
    if (dup2(*saved_output_file_desc, *output_file_desc) < 0) return -1;
    close(*saved_output_file_desc);
    return 0;
}