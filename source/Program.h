#ifndef PROGRAM_H
#define PROGRAM_H

#include "Shader.h"
#include <vector>

// stands for modern opengl
namespace mogl {

    class Program {
    public:
        Program(const std::vector<Shader>& shaders);
        ~Program();

        // returns the program's object ID 
        // as returned from glCreateProgram)
        GLuint object() const;

        // returns the attribute index for a given name
        // as returned from glGetAttribLocation
        GLint attrib(const GLchar* attribName) const;

        // returns the uniform index for a given name
        // as returned by glGetUniformLocation
        GLint uniform(const GLchar* uniformName) const;

    private:
        GLuint mObject;

        // removing the copying this object by removing the 
        // copy constructor and the equals operator
        Program(const Program&) {}
        const Program& operator=(const Program&) {}
    };
}

#endif