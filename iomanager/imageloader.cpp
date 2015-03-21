#include <imageloader.h>

GLTexture ImageLoader::loadPNG(std::string filePath)
{
    GLTexture texture = {};

    std::vector<unsigned char> rawPNG;
    std::vector<unsigned char> decodedPNG;
    unsigned long width;
    unsigned long height;

    IOUtils::readFileToBuffer(filePath, rawPNG);

    int errorCode = IOUtils::decodePNG(decodedPNG, width, height, &(rawPNG[0]), rawPNG.size());

    if (errorCode != 0) {
    }
}
