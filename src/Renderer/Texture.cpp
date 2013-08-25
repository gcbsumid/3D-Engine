// Standard Library 
#include <stdexcept>
#include <iostream>

// Backlash Library 
#include "Texture.h"
#include "../Util/defines.h"

static GLenum TextureFormatForBitmapFormat(backlash::Bitmap::E_FORMAT format, bool srgb) {
    switch (format) {
        case backlash::Bitmap::E_FORMAT_GREYSCALE: return GL_LUMINANCE;
        case backlash::Bitmap::E_FORMAT_GREYSCALEALPHA: return GL_LUMINANCE_ALPHA;
        case backlash::Bitmap::E_FORMAT_RGB: return (srgb ? GL_SRGB : GL_RGB);
        case backlash::Bitmap::E_FORMAT_RGBA: return (srgb ? GL_SRGB_ALPHA : GL_RGBA);
        default: throw std::runtime_error("Unrecognised Bitmap::Format");
    }
}

namespace backlash {
    // Initializing a texture object
    Texture::Texture(const Bitmap& bitmap, const std::string name, GLint minMagFiler, GLint wrapMode) :
        mName(name),
        mOriginalWidth((GLfloat)bitmap.Width()),
        mOriginalHeight((GLfloat)bitmap.Height()),
        mDiffuse(1.0f, 1.0f, 1.0f, 1.0f),
        mAmbient(1.0f, 1.0f, 1.0f, 1.0f),
        mSpecular(1.0f, 1.0f, 1.0f, 1.0f),
        mShininess(80.0f)
    {
        // generating a texture name
        glGenTextures(1, &mObject);

        // binding the name
        glBindTexture(GL_TEXTURE_2D, mObject);

        // setting parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minMagFiler);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, minMagFiler);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);

        // setting the data
        glTexImage2D(GL_TEXTURE_2D,
                        0,
                        TextureFormatForBitmapFormat(bitmap.Format(), true),
                        (GLsizei)bitmap.Width(),
                        (GLsizei)bitmap.Height(),
                        0,
                        TextureFormatForBitmapFormat(bitmap.Format(), false),
                        GL_UNSIGNED_BYTE,
                        bitmap.PixelBuffer());

        // unbinding the name 
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    Texture::~Texture() {
        glDeleteTextures(1, &mObject);
    }

    GLuint Texture::Object() const {
        return mObject;
    }

    GLfloat Texture::OriginalWidth() const {
        return mOriginalWidth;
    }

    GLfloat Texture::OriginalHeight() const {
        return mOriginalHeight;
    }

    std::string Texture::GetName() const {
        return mName;
    }

    void Texture::SetDiffuse(glm::vec4 diffuse) {
        mDiffuse = diffuse;
    } 

    void Texture::SetAmbient(glm::vec4 ambient) {
        mAmbient = ambient;
    } 

    void Texture::SetSpecular(glm::vec4 specular) {
        mSpecular = specular;
    } 

    // void Texture::SetEmission(glm::vec4 emission) {
    //     mEmission = emission;
    // } 

    void Texture::SetShininess(float shininess) {
        mShininess = shininess;
    }

    glm::vec4 Texture::GetDiffuse() const {
        return mDiffuse;
    }

    glm::vec4 Texture::GetAmbient() const {
        return mAmbient;
    }

    glm::vec4 Texture::GetSpecular() const {
        return mSpecular;
    }

    // glm::vec4 Texture::GetEmission() const {
    //     return mEmission;
    // }

    GLfloat Texture::GetShininess() const {
        return mShininess;
    }

    void Texture::BindTexture(Program* shader) {
        GLint tex = shader->Uniform("material.tex");
        GLint shininess = shader->Uniform("material.shininess");
        GLint specularColor = shader->Uniform("material.specularColor");

        // std::cout << "tex: " << tex << std::endl;
        // std::cout << "shininess: " << shininess << std::endl;
        // std::cout << "specularColor: " << specularColor << std::endl;

        glUniform1f(tex, 0);
        glUniform1f(shininess, mShininess);
        glUniform3f(specularColor, mSpecular[0], mSpecular[1], mSpecular[2]); // not sure if this is right though.

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, mObject);
    }

    void Texture::UnbindTexture() {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}