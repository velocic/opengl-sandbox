#include <ioutils.h>

bool IOUtils::readFileToBuffer(std::string filePath, std::vector<unsigned char> &buffer)
{
    std::ifstream file(filePath, std::ios::binary);

    if (file.fail()) {
        std::cout << "failed to read " << filePath << std::endl;
        return false;
    }

    file.seekg(0, std::ios::end);
    int fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    //make sure we don't load the file header (if present)
    fileSize -= file.tellg();

    //read the file
    buffer.resize(fileSize);
    file.read((char *)&(buffer[0]), fileSize);
    file.close();

    return true;
}

GLTexture IOUtils::loadPNG(std::string filePath)
{
    GLTexture texture = {};

    std::vector<unsigned char> rawPNG;
    std::vector<unsigned char> decodedPNG;
    unsigned long width;
    unsigned long height;

    if (!readFileToBuffer(filePath, rawPNG)) {
        std::cout << "Failed to load " << filePath << ". The file was likely not found." << std::endl;
        return texture;
    }

    int errorCode = decodePNG(decodedPNG, width, height, &(rawPNG[0]), rawPNG.size(), true);

    if (errorCode != 0) {
        std::cout << "decodePNG failed with error: " << errorCode << std::endl;
        return texture;
    }

    texture.width = width;
    texture.height = height;

    //Create a new empty texture on the GPU
    glGenTextures(1, &(texture.id));
    //Bind the empty texture so we can load data into it
    glBindTexture(GL_TEXTURE_2D, texture.id);
    //Load the actual texture data into the empty texture object on the GPU
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &(decodedPNG[0]));

    //Set some parameters related to our texture
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    //Set magnification filter
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //Set minification filter
    //Note: MipMapping is where multiple textures are generated at
    //progressively lower resolutions than the main texture.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    glEnable(GL_TEXTURE_2D);
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);

    return texture;
}
