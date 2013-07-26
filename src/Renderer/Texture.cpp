#include "Texture.h"
#include <stdexcept>

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
        mOriginalHeight((GLfloat)bitmap.Height())
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
}