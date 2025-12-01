#pragma once
#include <gl/glew.h>

class ShaderManager {
public:
    static void make_vertexShaders();
    static void make_fragmentShaders();
    static GLuint make_shaderProgram();
    
    static GLchar* vertexShaderSource;
    static GLchar* fragmentShaderSource;
    static GLuint vertexShader;
    static GLuint fragmentShader;
};
