#ifndef IOUTILS_H
#define IOUTILS_H

#include <vector>
#include <fstream>
#include <iostream>

namespace IOUtils
{
    bool readFileToBuffer(std::string filePath, std::vector<uint8_t> &buffer);
}

#endif
