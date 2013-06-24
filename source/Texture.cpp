#include "Texture.h"
#include <stdexcept>

static GLenum TextureFormatForBitmapFormat(backlash::Bitmap::E_FORMAT format) {
    switch (format) {
        case backlash::Bitmap::E_FORMAT_GREYSCALE: return GL_LUMINANCE;
        case backlash::Bitmap::E_FORMAT_GREYSCALEALPHA: return GL_LUMINANCE_ALPHA;
        case backlash::Bitmap::E_FORMAT_RGB: return GL_RGB;
        case backlash::Bitmap::E_FORMAT_RGBA: return GL_RGBA;
        default: throw std::runtime_error("Unrecognised Bitmap::Format");
    }
}

// Initializing a texture object
backlash::Texture::Texture(const backlash::Bitmap& bitmap, GLint minMagFiler, GLint wrapMode) :
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
                    TextureFormatForBitmapFormat(bitmap.Format()),
                    (GLsizei)bitmap.Width(),
                    (GLsizei)bitmap.Height(),
                    0,
                    TextureFormatForBitmapFormat(bitmap.Format()),
                    GL_UNSIGNED_BYTE,
                    bitmap.PixelBuffer());

    // unbinding the name 
    glBindTexture(GL_TEXTURE_2D, 0);
}

backlash::Texture::~Texture() {
    glDeleteTextures(1, &mObject);
}

GLuint backlash::Texture::Object() const {
    return mObject;
}

GLfloat backlash::Texture::OriginalWidth() const {
    return mOriginalWidth;
}

GLfloat backlash::Texture::OriginalHeight() const {
    return mOriginalHeight;
}