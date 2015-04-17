#include <bmploader.h>

GLuint BMPLoader::loadBMP_custom(std::string imagePath)
{
    unsigned int dataPosition;
    unsigned int width;
    unsigned int height;
    unsigned int imageSize;

    std::ifstream inStream(imagePath, std::ios::binary);
    std::vector<uint8_t> fileContents(
        (std::istreambuf_iterator<char>(inStream)),
        (std::istreambuf_iterator<char>())
    );

    //First 54 bytes are header data.

    //check if file begins with 'B' and 'M'
    if (fileContents[0] != 0x42 || fileContents[1] != 0x4d) {
        std::cout << "File does not contain valid BMP image data." << std::endl;
        return 0;
    }

    // dataPosition = (fileContents[0x0A] << 12) | (fileContents[0x0B] << 8) | (fileContents[0x0C] << 4) | fileContents[0x0D];
    dataPosition = 54;
    imageSize = (fileContents[0x22] << 12) | (fileContents[0x23] << 8) | (fileContents[0x24] << 4) | fileContents[0x25];
    width = (fileContents[0x12] << 12) | (fileContents[0x13] << 8) | (fileContents[0x14] << 4) | fileContents[0x15];
    height = (fileContents[0x16] << 12) | (fileContents[0x17] << 8) | (fileContents[0x18] << 4) | fileContents[0x19];

    if (imageSize == 0) {
        imageSize = width * height * 3;
    }

    uint8_t pixelData[imageSize];

    for (int i = 0; i < imageSize; i++) {
        pixelData[i] = fileContents[dataPosition + i];
    }

    //Create a new texture to hold the pixel data
    GLuint textureID;
    glGenTextures(1, &textureID);

    //Bind it
    glBindTexture(GL_TEXTURE_2D, textureID);

    //Fill it with the pixel data
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, pixelData);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glBindTexture(GL_TEXTURE_2D, 0);

    return textureID;
}
