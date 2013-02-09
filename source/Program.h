#ifndef PROGRAM_H
#define PROGRAM_H

#include "Shader.h"
#include <vector>
#include <glm/gtc/type_ptr.hpp>

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

        void Use() const;

        bool IsInUse() const;

        void Stop() const;

        // returns the attribute index for a given name
        // as returned from glGetAttribLocation
        GLuint Attrib(const GLchar* attribName) const;

        // returns the uniform index for a given name
        // as returned by glGetUniformLocation
        GLint Uniform(const GLchar* uniformName) const;


        // Setters for attribute and uniform variables.
        // These are convenience methoods for the glVertexAttrib* and 
        // glUniformAttrib* functions
#define _MOGL_PROGRAM_ATTRIB_N_UNIFORM_SETTERS(OGL_TYPE)\
        void SetAttrib(const GLchar* attribName, OGL_TYPE v0); \
        void SetAttrib(const GLchar* attribName, OGL_TYPE v0, OGL_TYPE v1); \
        void SetAttrib(const GLchar* attribName, OGL_TYPE v0, OGL_TYPE v1, OGL_TYPE v2); \
        void SetAttrib(const GLchar* attribName, OGL_TYPE v0, OGL_TYPE v1, OGL_TYPE v2, OGL_TYPE v3); \
\
        void SetAttrib1v(const GLchar* attribName, const OGL_TYPE* v); \
        void SetAttrib2v(const GLchar* attribName, const OGL_TYPE* v); \
        void SetAttrib3v(const GLchar* attribName, const OGL_TYPE* v); \
        void SetAttrib4v(const GLchar* attribName, const OGL_TYPE* v); \
\
        void SetUniform(const GLchar* uniformName, OGL_TYPE v0); \
        void SetUniform(const GLchar* uniformName, OGL_TYPE v0, OGL_TYPE v1); \
        void SetUniform(const GLchar* uniformName, OGL_TYPE v0, OGL_TYPE v1, OGL_TYPE v2); \
        void SetUniform(const GLchar* uniformName, OGL_TYPE v0, OGL_TYPE v1, OGL_TYPE v2, OGL_TYPE v3); \
\
        void SetUniform1v(const GLchar* uniformName, const OGL_TYPE* v, GLsizei count=1); \
        void SetUniform2v(const GLchar* uniformName, const OGL_TYPE* v, GLsizei count=1); \
        void SetUniform3v(const GLchar* uniformName, const OGL_TYPE* v, GLsizei count=1); \
        void SetUniform4v(const GLchar* uniformName, const OGL_TYPE* v, GLsizei count=1); \

        _MOGL_PROGRAM_ATTRIB_N_UNIFORM_SETTERS(GLfloat)
        _MOGL_PROGRAM_ATTRIB_N_UNIFORM_SETTERS(GLdouble)
        _MOGL_PROGRAM_ATTRIB_N_UNIFORM_SETTERS(GLint)
        _MOGL_PROGRAM_ATTRIB_N_UNIFORM_SETTERS(GLuint)

        void SetUniformMatrix2(const GLchar* uniformName, const GLfloat* v, GLsizei count=1, GLboolean transpose=GL_FALSE);
        void SetUniformMatrix3(const GLchar* uniformName, const GLfloat* v, GLsizei count=1, GLboolean transpose=GL_FALSE);
        void SetUniformMatrix4(const GLchar* uniformName, const GLfloat* v, GLsizei count=1, GLboolean transpose=GL_FALSE);
        void SetUniform(const GLchar* uniformName, const glm::mat2& m, GLboolean transpose=GL_FALSE);
        void SetUniform(const GLchar* uniformName, const glm::mat3& m, GLboolean transpose=GL_FALSE);
        void SetUniform(const GLchar* uniformName, const glm::mat4& m, GLboolean transpose=GL_FALSE);



    private:
        GLuint mObject;

        // removing the copying this object by removing the 
        // copy constructor and the equals operator
        Program(const Program&);
        const Program& operator=(const Program&);
    };
}

#endif