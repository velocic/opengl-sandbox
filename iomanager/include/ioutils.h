#ifndef IOUTILS_H
#define IOUTILS_H

#include <vector>
#include <fstream>
#include <iostream>

namespace IOUtils
{
    bool readFileToBuffer(std::string filePath, std::vector<char> &buffer);
}

#endif
