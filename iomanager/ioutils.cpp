#include <ioutils.h>

bool IOUtils::readFileToBuffer(std::string filePath, std::vector<uint8_t> &buffer)
{
    std::ifstream file(filePath, std::ios::binary);

    if (file.fail()) {
        std::cout << "failed to read " << filePath << std::endl;
        return false;
    }

    file.seekg(0, std::ios::end);
    int size = file.tellg();
    file.seekg(0, std::ios::beg);

    //make sure we don't load the file header (if present)
    size -= file.tellg();

    //read the file
    buffer.resize(fileSize);
    file.read(&(buffer[0]), fileSize);
    file.close();

    return true;
}
