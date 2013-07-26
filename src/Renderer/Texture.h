#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>
#include <string>
#include "Bitmap.h"

namespace backlash {

    // Represents an OpenGL texture

    class Texture {
    public:
        // Creates a texture from a bitmap

        // The texture is loaded upside down because backlash::Bitmap pixel
        // data is ordered from the top row down, but OpenGl expects 
        // the data to be from the bottom row up.
        Texture(const Bitmap& bitmap, const string name, GLint minMagFiler = GL_LINEAR,
            GLint wrapMode = GL_CLAMP_TO_EDGE);


        // Deletes the texture object with glDeleteTextures
        ~Texture();

        // returns the texture object
        GLuint Object() const;

        // The original width in pixels of the bitmap this texture 
        // was made from
        GLfloat OriginalWidth() const;

        // The original height in pixels of the bitmap this texture
        // was made from
        GLfloat OriginalHeight() const;

        // The name of the current texture
        std::string GetName() const;

    private:
        std::string mName;
        GLuint mObject;
        GLfloat mOriginalWidth;
        GLfloat mOriginalHeight;

        // copying disabled 
        Texture(const Texture&);
        const Texture& operator=(const Texture&);
    };
}

#endif