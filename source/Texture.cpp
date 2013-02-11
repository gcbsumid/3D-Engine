#include "Texture.h"
#include <stdexcept>

using namespace mogl;

static GLenum TextureFormatForBitmapFormat(Bitmap::E_FORMAT format) {
    switch (format) {
        case Bitmap::E_FORMAT_GREYSCALE: return GL_LUMINANCE;
        case Bitmap::E_FORMAT_GREYSCALEALPHA: return GL_LUMINANCE_ALPHA;
        case Bitmap::E_FORMAT_RGB: return GL_RGB;
        case Bitmap::E_FORMAT_RGBA: return GL_RGBA;
        default: throw std::runtime_error("Unrecognised Bitmap::Format");
    }
}

Texture::Texture(const Bitmap& bitmap, GLint minMagFiler, GLint wrapMode) :
    mOriginalWidth((GLfloat)bitmap.Width()),
    mOriginalHeight((GLfloat)bitmap.Height())
{
    glGenTextures(1, &mObject);
    glBindTexture(GL_TEXTURE_2D, mObject);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minMagFiler);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, minMagFiler);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
    glTexImage2D(GL_TEXTURE_2D,
                    0,
                    TextureFormatForBitmapFormat(bitmap.Format()),
                    (GLsizei)bitmap.Width(),
                    (GLsizei)bitmap.Height(),
                    0,
                    TextureFormatForBitmapFormat(bitmap.Format()),
                    GL_UNSIGNED_BYTE,
                    bitmap.PixelBuffer());
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