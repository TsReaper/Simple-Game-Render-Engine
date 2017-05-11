#include "basicShader.h"

// Shader functions
const int BasicShader::SHADER_LOAD_LIGHT = 1;
const int BasicShader::SHADER_LOAD_CLIP = 2;
const int BasicShader::SHADER_BIND_TEX_NORM = 4;

// Constructor
BasicShader::BasicShader(const char* vertexFile, const char* fragmentFile, int _mode): ShaderProgram(vertexFile, fragmentFile)
{
    mode = _mode;
    // Bind VAO attributes and link program
    bindAttributes();
    glLinkProgram(programId);
    glValidateProgram(programId);
    getAllUniformLocs();
}

// Load transformation matrix into shader program
void BasicShader::loadTransMatrix(const float* matrix)
{
    loadMatrix4(transMatrixLoc, matrix);
}

// Load camera matrix into shader program
void BasicShader::loadCameraMatrix(const float* matrix)
{
    loadMatrix4(cameraMatrixLoc, matrix);
}

// Load projection matrix into shader program
void BasicShader::loadProjMatrix(const float* matrix)
{
    loadMatrix4(projMatrixLoc, matrix);
}

// Load light into shader program
void BasicShader::loadLight(float x, float y, float z, float r, float g, float b)
{
    loadVector3(lightPosLoc, x, y, z);
    loadVector3(lightColLoc, r, g, b);
}

// Load sky color into shader program
void BasicShader::loadSkyCol(float r, float g, float b)
{
    loadVector3(skyColLoc, r, g, b);
}

// Load clipping plane info into shader program
void BasicShader::loadClipping(float height, bool clipPositive)
{
    if (mode & SHADER_LOAD_CLIP)
    {
        loadFloat(clipHeightLoc, height);
        loadBool(clipPositiveLoc, clipPositive);
    }
}

// Get all uniform locations
void BasicShader::getAllUniformLocs()
{
    transMatrixLoc = getUniformLoc("transMatrix");
    cameraMatrixLoc = getUniformLoc("cameraMatrix");
    projMatrixLoc = getUniformLoc("projMatrix");
    
    if (mode & SHADER_LOAD_LIGHT)
    {
        lightPosLoc = getUniformLoc("lightPos");
        lightColLoc = getUniformLoc("lightCol");
    }
    
    skyColLoc = getUniformLoc("skyCol");
    
    if (mode & SHADER_LOAD_CLIP)
    {
        clipHeightLoc = getUniformLoc("clipHeight");
        clipPositiveLoc = getUniformLoc("clipPositive");
    }
}

// Bind VAO attributes
void BasicShader::bindAttributes()
{
    // Bind vertex position and texture coordinate
    bindAttribute(0, "position");
    
    if (SHADER_BIND_TEX_NORM)
    {
        bindAttribute(1, "textureCoord");
        bindAttribute(2, "norm");
    }
}
