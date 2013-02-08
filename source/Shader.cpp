#include "Shader.h"
#include <stdexcept>
#include <fstream>
#include <string>
#include <cassert>
#include <sstream>

#include <iostream>

using namespace mogl;

Shader::Shader(const std::string& shaderCode, GLenum shaderType, const std::string& filePath):
    mObject(0),
    mRefCount(NULL)
{
    // create the shader object
    mObject = glCreateShader(shaderType);
    if(mObject == 0) {
        throw std::runtime_error("glCreateShader failed. It returned a null pointer.");
    }

    // set the source code
    const char* code = shaderCode.c_str();
    glShaderSource(mObject, 1, (const GLchar**) &code, NULL);


    // std::cout << code << std::endl;

    // compile
    glCompileShader(mObject);

    // throw exception if compiler error happened.
    GLint status;
    glGetShaderiv(mObject, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE) {
        std::stringstream msg;
        msg << "Compile Failure in shader: " << std::endl;
        msg << "\tFile Path: " << filePath << std::endl;

        GLint infoLogLength;
        glGetShaderiv(mObject, GL_INFO_LOG_LENGTH, &infoLogLength);
        char* strInfoLog = new char[infoLogLength + 1];
        glGetShaderInfoLog(mObject, infoLogLength, NULL, strInfoLog);
        msg << strInfoLog;
        delete[] strInfoLog;

        glDeleteShader(mObject); 
        mObject = 0;
        throw std::runtime_error(msg.str());
    }

    mRefCount = new unsigned;
    *mRefCount = 1;
}

Shader::Shader(const Shader& shader) :
    mObject(shader.mObject),
    mRefCount(shader.mRefCount)
{
    Retain();
}

Shader::~Shader() {
    if(mRefCount) {
        Release();
    }
}

GLuint Shader::object() const {
    return mObject;
}

Shader& Shader::operator=(const Shader& shader) {
    Release();
    mObject = shader.mObject;
    mRefCount = shader.mRefCount;
    Retain();
    return *this;
}

Shader Shader::ShaderFromFile(const std::string& filePath, GLenum shaderType) {
    // open file
    std::ifstream f;
    f.open(filePath.c_str(), std::ios::in | std::ios::binary);
    if(!f.is_open()) {
        throw std::runtime_error(std::string("Failed to open file: ") + filePath);
    }

    // read whole file into a string stream buffer
    std::stringstream code;
    code << f.rdbuf();

    // Return new shader
    Shader shader(code.str(), shaderType, filePath);
    return shader;
}

void Shader::Retain() {
    assert(mRefCount);
    *mRefCount += 1;
}

void Shader::Release() {
    assert(mRefCount && *mRefCount > 0);
    *mRefCount -= 1;
    if(*mRefCount == 0) {
        glDeleteShader(mObject);
        mObject = 0;
        delete mRefCount;
        mRefCount = NULL;
    }
}