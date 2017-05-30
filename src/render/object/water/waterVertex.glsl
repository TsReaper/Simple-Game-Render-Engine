#version 400 core

in vec3 position;

out vec4 passCoord;
out vec2 texCoord;
out vec3 toLightVec;
out vec3 toCameraVec;

uniform mat4 transMatrix;
uniform mat4 cameraMatrix;
uniform mat4 projMatrix;

uniform vec3 lightPos;

uniform float waterHeight;

const float SIZE = 1024;
const float SAMPLE_FAC = 10;

void main(void)
{
    vec4 worldCoord = transMatrix * vec4(SIZE*position.x, waterHeight, SIZE*position.z, 1.0);
    vec4 posToCam = cameraMatrix * worldCoord;

    gl_Position = passCoord = projMatrix * posToCam;
    texCoord = position.xz * SAMPLE_FAC;
    toLightVec = lightPos - worldCoord.xyz;
    toCameraVec = (inverse(cameraMatrix) * vec4(0.0, 0.0, 0.0, 1.0) - worldCoord).xyz;
}