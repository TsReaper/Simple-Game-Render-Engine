#include <cmath>
#include "math.h"

// Create a 4x4 transformation matrix
float* Math::createTransMatrix(float tX, float tY, float tZ, float rX, float rY, float rZ, float scale)
{
    // Initialize a 4x4 identity matrix;
    float* res = new float[4*4];
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            res[i*4+j] = (i == j);
    
    // Scaling
    float* scalingMatrix = new float[4*4] {
        scale, 0, 0, 0,
        0, scale, 0, 0,
        0, 0, scale, 0,
        0, 0, 0, 1
    };
    leftMulMatrix4(res, scalingMatrix);
    delete[] scalingMatrix;
    
    // Rotate Z
    float* rotateZMatrix = new float[4*4] {
        (float)cos(rZ), (float)-sin(rZ), 0, 0,
        (float)sin(rZ), (float)cos(rZ), 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    };
    leftMulMatrix4(res, rotateZMatrix);
    delete[] rotateZMatrix;
    
    // Rotate Y
    float* rotateYMatrix = new float[4*4] {
        (float)cos(rY), 0, (float)-sin(rY), 0,
        0, 1, 0, 0,
        (float)sin(rY), 0, (float)cos(rY), 0,
        0, 0, 0, 1
    };
    leftMulMatrix4(res, rotateYMatrix);
    delete[] rotateYMatrix;
    
    // Rotate X
    float* rotateXMatrix = new float[4*4] {
        1, 0, 0, 0,
        0, (float)cos(rX), (float)sin(rX), 0,
        0, (float)-sin(rX), (float)cos(rX), 0,
        0, 0, 0, 1
    };
    leftMulMatrix4(res, rotateXMatrix);
    delete[] rotateXMatrix;
    
    // Translation
    float* translationMatrix = new float[4*4] {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        tX, tY, tZ, 1
    };
    leftMulMatrix4(res, translationMatrix);
    delete[] translationMatrix;
    
    return res;
}

// Create a 4x4 projection matrix
float* Math::createProjMatrix(float ratio, float fov, float zNear, float zFar)
{
    return new float[4*4] {
        1/(float)tan(fov/2)/ratio, 0, 0, 0,
        0, 1/(float)tan(fov/2), 0, 0,
        0, 0, -(zFar+zNear)/(zFar-zNear), -1,
        0, 0, -2*zFar*zNear/(zFar-zNear), 0
    };
}

// Calculate A = B*A, where A and B are both 4x4 matrices
void Math::leftMulMatrix4(float* A, float* B)
{
    float res[16] = {0};
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            for (int k = 0; k < 4; k++)
                res[j*4+i] += B[k*4+i] * A[j*4+k];
    for (int i = 0; i < 16; i++)
        A[i] = res[i];
}