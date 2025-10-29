#pragma once

class Texture
{
public:
    Texture();
    ~Texture();

    // Read the file to init the texture
    bool Init(const char* texturePath);

    // Use the corresponding texture
    void Use(GLuint shaderProgram, std::string textureName, GLuint unit);

private:
    //GLuint image;
    GLuint _imagePointer;
};