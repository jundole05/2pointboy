#include "ShaderManager.h"
#include <iostream>
using namespace std;

GLchar* ShaderManager::vertexShaderSource = nullptr;
GLchar* ShaderManager::fragmentShaderSource = nullptr;
GLuint ShaderManager::vertexShader = 0;
GLuint ShaderManager::fragmentShader = 0;

void ShaderManager::make_vertexShaders()
{
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    GLint result;
    GLchar errorLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
    if (!result)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, errorLog);
        cerr << "ERROR: vertex shader 컴파일 실패\n" << errorLog << endl;
    }
}

void ShaderManager::make_fragmentShaders()
{
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    GLint result;
    GLchar errorLog[512];
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);
    if (!result)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, errorLog);
        cerr << "ERROR: fragment shader 컴파일 실패\n" << errorLog << endl;
    }
}

GLuint ShaderManager::make_shaderProgram()
{
    GLuint ShaderProgramID;
    GLint result;
    GLchar errorLog[512];
    ShaderProgramID = glCreateProgram();
    glAttachShader(ShaderProgramID, vertexShader);
    glAttachShader(ShaderProgramID, fragmentShader);
    glLinkProgram(ShaderProgramID);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glGetProgramiv(ShaderProgramID, GL_LINK_STATUS, &result);
    if (!result) {
        glGetProgramInfoLog(ShaderProgramID, 512, NULL, errorLog);
  cerr << "ERROR: shader program 연결 실패\n" << errorLog << endl;
    }
    return ShaderProgramID;
}
