#include "fileaccess.hpp"

#include <iostream>



/**
 * Returns an input file stream of the filename specified. If the filename is invalid, 
 * output will evaluate `false` when typecasted to bool.
 */
std::ifstream OpenFile(std::string filename)
{
    return std::ifstream(filename);
}
