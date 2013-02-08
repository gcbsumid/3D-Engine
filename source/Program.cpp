#include "Program.h"
#include <stdexcept>
#include <sstream>
#include <iostream>

using namespace mogl;

Program::Program(const std::vector<Shader> &shaders) 
    : mObject(0) 
{
    if (shaders.size() <= 0) {
        throw std::runtime_error("No Shaders were provided to create the program.");
    }   

    // Create the program Object
    mObject = glCreateProgram();
    if (mObject == 0) {
        throw std::runtime_error("glCreateProgram failed. There is no program object.");
    }

    // attach all the shaders
    for (int i = 0; i < shaders.size(); i++) {
            glAttachShader(mObject, shaders.at(i).object());
    }

    // link the shaders together
    glLinkProgram(mObject);

    // detach all the shaders
    for (int i = 0; i < shaders.size(); i++) {
        glDetachShader(mObject, shaders.at(i).object());
    }

    // throw exception if linking has failed.
    GLint status;
    glGetProgramiv(mObject, GL_LINK_STATUS, &status);
    if (status == GL_FALSE) {
        std::stringstream msg;
        msg << "Program link failure: ";

        GLint infoLogLength;
        glGetProgramiv(mObject, GL_INFO_LOG_LENGTH, &infoLogLength);
        char* strInfoLog = new char[infoLogLength + 1];
        glGetProgramInfoLog(mObject, infoLogLength, NULL, strInfoLog);
        msg << strInfoLog << std::endl;
        delete[] strInfoLog;

        glDeleteProgram(mObject);
        mObject = 0;
        throw std::runtime_error(msg.str().c_str());
    } 
}

Program::~Program() {
    if (mObject != 0) {
        glDeleteProgram(mObject);
    }
}

GLuint Program::Object() const {
    return mObject;
}

GLuint Program::Attrib(const GLchar* attribName) const {
    if (!attribName) {
        throw std::runtime_error("attribName was NULL.");
    }

    GLuint attrib = glGetAttribLocation(mObject, attribName);
    if (attrib == -1) {
        std::stringstream msg;
        msg << "Program attribute not found: " << attribName << std::endl;
        throw std::runtime_error(msg.str().c_str());
    }

    return attrib;
}

GLint Program::Uniform(const GLchar* uniformName) const {
    if (!uniformName) {
        throw std::runtime_error("uniformName was NULL");
    }

    GLint uniform = glGetUniformLocation(mObject, uniformName);
    if (uniform == -1) {
        std::stringstream msg;
        msg << "Program uniform not found: " << uniformName << std::endl;
        throw std::runtime_error(msg.str().c_str());
    }

    return uniform;
}