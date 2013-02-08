#ifndef PROGRAM_H
#define PROGRAM_H

#include "Shader.h"
#include <vector>

// stands for modern opengl
namespace mogl {

    // represents an OpenGL program made by linking shaders
    class Program {
    public:
        // Creates a program by linking a list of shader objects
        Program(const std::vector<Shader>& shaders);
        ~Program();

        // returns the program's object ID 
        // as returned from glCreateProgram)
        GLuint Object() const;

        // returns the attribute index for a given name
        // as returned from glGetAttribLocation
        GLuint Attrib(const GLchar* attribName) const;

        // returns the uniform index for a given name
        // as returned by glGetUniformLocation
        GLint Uniform(const GLchar* uniformName) const;

    private:
        GLuint mObject;

        // removing the copying this object by removing the 
        // copy constructor and the equals operator
        Program(const Program&);
        const Program& operator=(const Program&);
    };
}

#endif