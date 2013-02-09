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

void Program::Use() const {
    glUseProgram(mObject);
}

bool Program::IsInUse() const {
    GLint currentProgram = 0;
    glGetIntegerv(GL_CURRENT_PROGRAM, &currentProgram);
    // returns whether the current program is this object
    return (currentProgram == (GLint)mObject);
}

void Program::Stop() const {
    assert(IsInUse());
    glUseProgram(0);
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

#define ATTRIB_N_UNIFORM_SETTERS(OGL_TYPE, TYPE_PREFIX, TYPE_SUFFIX) \
\
    void Program::SetAttrib(const GLchar* name, OGL_TYPE v0) \
        { assert(IsInUse()); glVertexAttrib ## TYPE_PREFIX ## 1 ## TYPE_SUFFIX (Attrib(name), v0); } \
    void Program::SetAttrib(const GLchar* name, OGL_TYPE v0, OGL_TYPE v1) \
        { assert(IsInUse()); glVertexAttrib ## TYPE_PREFIX ## 2 ## TYPE_SUFFIX (Attrib(name), v0, v1); } \
    void Program::SetAttrib(const GLchar* name, OGL_TYPE v0, OGL_TYPE v1, OGL_TYPE v2) \
        { assert(IsInUse()); glVertexAttrib ## TYPE_PREFIX ## 3 ## TYPE_SUFFIX (Attrib(name), v0, v1, v2); } \
    void Program::SetAttrib(const GLchar* name, OGL_TYPE v0, OGL_TYPE v1, OGL_TYPE v2, OGL_TYPE v3) \
        { assert(IsInUse()); glVertexAttrib ## TYPE_PREFIX ## 4 ## TYPE_SUFFIX (Attrib(name), v0, v1, v2, v3); } \
\
    void Program::SetAttrib1v(const GLchar* name, const OGL_TYPE* v) \
        { assert(IsInUse()); glVertexAttrib ## TYPE_PREFIX ## 1 ## TYPE_SUFFIX ## v (Attrib(name), v); } \
    void Program::SetAttrib2v(const GLchar* name, const OGL_TYPE* v) \
        { assert(IsInUse()); glVertexAttrib ## TYPE_PREFIX ## 2 ## TYPE_SUFFIX ## v (Attrib(name), v); } \
    void Program::SetAttrib3v(const GLchar* name, const OGL_TYPE* v) \
        { assert(IsInUse()); glVertexAttrib ## TYPE_PREFIX ## 3 ## TYPE_SUFFIX ## v (Attrib(name), v); } \
    void Program::SetAttrib4v(const GLchar* name, const OGL_TYPE* v) \
        { assert(IsInUse()); glVertexAttrib ## TYPE_PREFIX ## 4 ## TYPE_SUFFIX ## v (Attrib(name), v); } \
\
    void Program::SetUniform(const GLchar* name, OGL_TYPE v0) \
        { assert(IsInUse()); glUniform1 ## TYPE_SUFFIX (Uniform(name), v0); } \
    void Program::SetUniform(const GLchar* name, OGL_TYPE v0, OGL_TYPE v1) \
        { assert(IsInUse()); glUniform2 ## TYPE_SUFFIX (Uniform(name), v0, v1); } \
    void Program::SetUniform(const GLchar* name, OGL_TYPE v0, OGL_TYPE v1, OGL_TYPE v2) \
        { assert(IsInUse()); glUniform3 ## TYPE_SUFFIX (Uniform(name), v0, v1, v2); } \
    void Program::SetUniform(const GLchar* name, OGL_TYPE v0, OGL_TYPE v1, OGL_TYPE v2, OGL_TYPE v3) \
        { assert(IsInUse()); glUniform4 ## TYPE_SUFFIX (Uniform(name), v0, v1, v2, v3); } \
\
    void Program::SetUniform1v(const GLchar* name, const OGL_TYPE* v, GLsizei count) \
        { assert(IsInUse()); glUniform1 ## TYPE_SUFFIX ## v (Uniform(name), count, v); } \
    void Program::SetUniform2v(const GLchar* name, const OGL_TYPE* v, GLsizei count) \
        { assert(IsInUse()); glUniform2 ## TYPE_SUFFIX ## v (Uniform(name), count, v); } \
    void Program::SetUniform3v(const GLchar* name, const OGL_TYPE* v, GLsizei count) \
        { assert(IsInUse()); glUniform3 ## TYPE_SUFFIX ## v (Uniform(name), count, v); } \
    void Program::SetUniform4v(const GLchar* name, const OGL_TYPE* v, GLsizei count) \
        { assert(IsInUse()); glUniform4 ## TYPE_SUFFIX ## v (Uniform(name), count, v); }

ATTRIB_N_UNIFORM_SETTERS(GLfloat, , f);
ATTRIB_N_UNIFORM_SETTERS(GLdouble, , d);
ATTRIB_N_UNIFORM_SETTERS(GLint, I, i);
ATTRIB_N_UNIFORM_SETTERS(GLuint, I, ui);

void Program::SetUniformMatrix2(const GLchar* name, const GLfloat* v, GLsizei count, GLboolean transpose) {
    assert(IsInUse());
    glUniformMatrix2fv(Uniform(name), count, transpose, v);
}

void Program::SetUniformMatrix3(const GLchar* name, const GLfloat* v, GLsizei count, GLboolean transpose) {
    assert(IsInUse());
    glUniformMatrix3fv(Uniform(name), count, transpose, v);
}

void Program::SetUniformMatrix4(const GLchar*name, const GLfloat* v, GLsizei count, GLboolean transpose) {
    assert(IsInUse());
    glUniformMatrix4fv(Uniform(name), count, transpose, v);
}

void Program::SetUniform(const GLchar* name, const glm::mat2& m, GLboolean transpose) {
    assert(IsInUse());
    glUniformMatrix2fv(Uniform(name), 1, transpose, glm::value_ptr(m));
}

void Program::SetUniform(const GLchar* name, const glm::mat3& m, GLboolean transpose) {
    assert(IsInUse());
    glUniformMatrix3fv(Uniform(name), 1, transpose, glm::value_ptr(m));
}

void Program::SetUniform(const GLchar* name, const glm::mat4& m, GLboolean transpose) {
    assert(IsInUse());
    glUniformMatrix4fv(Uniform(name), 1, transpose, glm::value_ptr(m));
}

