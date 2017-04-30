#include "modelTexture.h"

// Constructor
ModelTexture::ModelTexture(const char* _name, GLuint id)
{
    name = _name;
    textureId = id;
    reflectivity = 0;
    shineDamper = 1;
}

// Destructor
ModelTexture::~ModelTexture()
{
    glDeleteTextures(1, &textureId);
}

// Get texture name
const char* ModelTexture::getName() const
{
    return name.c_str();
}

// Get texture id
int ModelTexture::getId() const
{
    return textureId;
}

// Get reflectivity
float ModelTexture::getReflectivity() const
{
    return reflectivity;
}

// Get shine damper
float ModelTexture::getShineDamper() const
{
    return shineDamper;
}

// Set reflectivity
void ModelTexture::setReflectivity(float _reflectivity)
{
    reflectivity = _reflectivity;
}

// Set shine damper
void ModelTexture::setShineDamper(float _shineDamper)
{
    shineDamper = _shineDamper;
}
