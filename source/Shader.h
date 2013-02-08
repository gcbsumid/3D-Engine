#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <string>

namespace mogl {

    // Represents a compiled OpenGL shader

    class Shader {
    public:
        // Creates a shader from a text file.
        static Shader ShaderFromFile(const std::string& filePath, GLenum shaderType);

        // Creates a shader from a string of shader source code
        Shader(const std::string& shaderCode, GLenum shaderType, const std::string& filePath);

        // returns the shader's object ID
        GLuint object() const;

        // Shader objects can be copied and assigned because they are reference counted like a shared pointer.
        Shader(const Shader& shader);
        Shader& operator =(const Shader& shader);
        ~Shader();

    private:
        GLuint mObject;
        unsigned* mRefCount;

        void Retain();
        void Release();

    };
}

#endif