#include "Bitmap.h"
#include <stdexcept>

// uses stb_image to try load files
#define STBI_FAILURE_USERMSG
#include <stb_image.c>

inline unsigned char AverageRGB(unsigned char rgb[3]) {
    return (unsigned char)(((double)rgb[0] + (double)rgb[1] + (double)rgb[2]) / 3.0);
}

static void GreyscaleToGreyscaleAlpha(unsigned char* src, unsigned char* dest) {
    dest[0] = src[0];
    dest[1] = 255;
}

static void GreyscaleToRGB(unsigned char* src, unsigned char* dest) {
    dest[0] = src[0];
    dest[1] = src[0];
    dest[2] = src[0];
}

static void GreyscaleToRGBA(unsigned char* src, unsigned char* dest) {
    dest[0] = src[0];
    dest[1] = src[0];
    dest[2] = src[0];
    dest[3] = 255;
}

static void GreyscaleAlphaToGreyscale(unsigned char* src, unsigned char* dest) {
    dest[0] = src[0];
}

static void GreyscaleAlphaToRGB(unsigned char* src, unsigned char* dest) {
    dest[0] = src[0];
    dest[1] = src[0];
    dest[2] = src[0];
}

static void GreyscaleAlphaToRGBA(unsigned char* src, unsigned char* dest){
    dest[0] = src[0];
    dest[1] = src[0];
    dest[2] = src[0];
    dest[3] = src[1];
}

static void RGBToGreyscale(unsigned char* src, unsigned char* dest){
    dest[0] = AverageRGB(src);
}

static void RGBToGreyscaleAlpha(unsigned char* src, unsigned char* dest){
    dest[0] = AverageRGB(src);
    dest[1] = 255;
}

static void RGBToRGBA(unsigned char* src, unsigned char* dest){
    dest[0] = src[0];
    dest[1] = src[1];
    dest[2] = src[2];
    dest[3] = 255;
}

static void RGBAToGreyscale(unsigned char* src, unsigned char* dest){
    dest[0] = AverageRGB(src);
}

static void RGBAToGreyscaleAlpha(unsigned char* src, unsigned char* dest){
    dest[0] = AverageRGB(src);
    dest[1] = src[3];
}

static void RGBAToRGB(unsigned char* src, unsigned char* dest){
    dest[0] = src[0];
    dest[1] = src[1];
    dest[2] = src[2];
}

typedef void(*FormatConverterFunc)(unsigned char*, unsigned char*);

static FormatConverterFunc ConverterFuncForFormat(backlash::Bitmap::E_FORMAT srcFormat, backlash::Bitmap::E_FORMAT destFormat) {
    if(srcFormat == destFormat) {
        throw std::runtime_error("Just use memcpy if pixel formats are the same.");
    }

    switch(srcFormat) {
        case backlash::Bitmap::E_FORMAT_GREYSCALE: {
            switch(destFormat) {
                case backlash::Bitmap::E_FORMAT_GREYSCALEALPHA:   return GreyscaleToGreyscaleAlpha;
                case backlash::Bitmap::E_FORMAT_RGB:              return GreyscaleToRGB;
                case backlash::Bitmap::E_FORMAT_RGBA:             return GreyscaleToRGBA;
                default:
                    throw std::runtime_error("Unhandled bitmap format");
            }
            break;
        }
        case backlash::Bitmap::E_FORMAT_GREYSCALEALPHA: {
            switch(destFormat) {
                case backlash::Bitmap::E_FORMAT_GREYSCALE:    return GreyscaleAlphaToGreyscale;
                case backlash::Bitmap::E_FORMAT_RGB:          return GreyscaleAlphaToRGB;
                case backlash::Bitmap::E_FORMAT_RGBA:         return GreyscaleAlphaToRGBA;
                default:
                    throw std::runtime_error("Unhandled bitmap format");
            }
            break;
        }
        case backlash::Bitmap::E_FORMAT_RGB: {
            switch(destFormat) {
                case backlash::Bitmap::E_FORMAT_GREYSCALE:    return RGBToGreyscale;
                case backlash::Bitmap::E_FORMAT_GREYSCALEALPHA: return RGBToGreyscaleAlpha;
                case backlash::Bitmap::E_FORMAT_RGBA:         return RGBToRGBA;
                default:
                    throw std::runtime_error("Unhandled bitmap format");
            }
            break;
        }
        case backlash::Bitmap::E_FORMAT_RGBA: {
            switch(destFormat) {
                case backlash::Bitmap::E_FORMAT_GREYSCALE:    return RGBAToGreyscale;
                case backlash::Bitmap::E_FORMAT_GREYSCALEALPHA: return RGBAToGreyscaleAlpha;
                case backlash::Bitmap::E_FORMAT_RGB:          return RGBAToRGB;
                default:
                    throw std::runtime_error("Unhandled bitmap format.");
            }
            break;
        }
        default: 
            throw std::runtime_error("Unhandled bitmap format");
    }   
}

// Misc Functions
inline unsigned GetPixelOffset(unsigned col, unsigned row, unsigned width, unsigned height, backlash::Bitmap::E_FORMAT format) {
    return (row*width + col)*format;
}

inline bool RectsOverlap(unsigned srcCol, unsigned srcRow, unsigned destCol, unsigned destRow, unsigned width, unsigned height) {
    unsigned colDiff = srcCol > destCol ? srcCol - destCol : destCol - srcCol;
    if(colDiff < width) {
        return true;
    }

    unsigned rowDiff = srcRow > destRow ? srcRow - destRow : destRow - srcRow;
    if(rowDiff < height) {
        return true;
    }
    return false;
}

// backlash::Bitmap Class
backlash::Bitmap::Bitmap(unsigned width, unsigned height, E_FORMAT format, const unsigned char* pixels) :
    mPixels(NULL)
{
    Set(width, height, format, pixels);
}

backlash::Bitmap::~Bitmap() {
    if(mPixels) {
        free(mPixels);
    }
}

backlash::Bitmap backlash::Bitmap::BitmapFromFile(std::string filePath) {
    int width, height, channels;
    unsigned char* pixels = stbi_load(filePath.c_str(), &width, &height, &channels, 0);
    if(!pixels) {
        throw std::runtime_error(stbi_failure_reason());
    }

    backlash::Bitmap bmp(width, height, (E_FORMAT)channels, pixels);
    stbi_image_free(pixels);
    return bmp;
}

backlash::Bitmap::Bitmap(const backlash::Bitmap& other) :
    mPixels(NULL)
{
    Set(other.mWidth, other.mHeight, other.mFormat, other.mPixels);
}

backlash::Bitmap& backlash::Bitmap::operator=(const backlash::Bitmap& other) {
    Set(other.mWidth, other.mHeight, other.mFormat, other.mPixels);
    return *this;
}

unsigned int backlash::Bitmap::Width() const {
    return mWidth;
}

unsigned int backlash::Bitmap::Height() const {
    return mHeight;
}

backlash::Bitmap::E_FORMAT backlash::Bitmap::Format() const {
    return mFormat;
}

unsigned char* backlash::Bitmap::PixelBuffer() const {
    return mPixels;
}

unsigned char* backlash::Bitmap::GetPixel(unsigned int column, unsigned int row) const {
    if(column >= mWidth || row >= mHeight) {
        throw std::runtime_error("Pixel coordinate out of bounds");
    }

    return mPixels + GetPixelOffset(column, row, mWidth, mHeight, mFormat);
}

void backlash::Bitmap::SetPixel(unsigned int column, unsigned int row, const unsigned char* pixel) {
    unsigned char* myPixel = GetPixel(column, row);
    memcpy(myPixel, pixel, mFormat);
}

void backlash::Bitmap::FlipVertically() {
    unsigned long rowSize = mFormat * mWidth;
    unsigned char* rowBuffer = new unsigned char[rowSize];
    unsigned halfRows = mHeight/2;

    for(unsigned rowIdx = 0; rowIdx < halfRows; rowIdx++) {
        unsigned char* row = mPixels + GetPixelOffset(0, rowIdx, mWidth, mHeight, mFormat);
        unsigned char* oppositeRow = mPixels + GetPixelOffset(0, mHeight - rowIdx -1, mWidth, mHeight, mFormat);

        memcpy(rowBuffer, row, rowSize);
        memcpy(row, oppositeRow, rowSize);
        memcpy(oppositeRow, rowBuffer, rowSize);
    }

    delete rowBuffer;
}

void backlash::Bitmap::Rotate90CounterClockwise() {
    unsigned char* newPixels = (unsigned char*) malloc(mFormat*mWidth*mHeight);

    for(unsigned row = 0; row < mHeight; ++row) {
        for(unsigned col = 0; col < mWidth; ++col) {
            unsigned srcOffset = GetPixelOffset(col, row, mWidth, mHeight, mFormat);
            unsigned destOffset =GetPixelOffset(row, mWidth - col - 1, mHeight, mWidth, mFormat);
            memcpy(newPixels + destOffset, mPixels + srcOffset, mFormat);
        }
    }

    free(mPixels);
    mPixels = newPixels;

    unsigned swapTmp = mHeight;
    mHeight = mWidth;
    mWidth = swapTmp;
}

void backlash::Bitmap::CopyRectFromBitmap(const backlash::Bitmap& src, 
                                unsigned srcCol,
                                unsigned srcRow,
                                unsigned destCol,
                                unsigned destRow,
                                unsigned width,
                                unsigned height)
{
    if(srcCol == 0 && srcRow == 0 && width == 0 && height ==0) {
        width = src.Width();
        height = src.Height();
    }

    if(width == 0 || height == 0)
        throw std::runtime_error("Can't copy zero height/width rectangle");
    
    if(srcCol + width >= src.Width() || srcRow + height >= src.Height())
        throw std::runtime_error("Rectangle doesn't fit within source backlash::bitmap");

    if(destCol + width >= mWidth || destRow + height >= mHeight)
        throw std::runtime_error("Rectangle doesn't fit within destination bitmap");
    
    if(mPixels == src.mPixels && RectsOverlap(srcCol, srcRow, destCol, destRow, width, height))
        throw std::runtime_error("Source and destination are the same bitmap, and rects overlap. Not allowed!");
    
    FormatConverterFunc converter = NULL;
    if(mFormat != src.mFormat) {
        converter = ConverterFuncForFormat(mFormat, src.mFormat);
    }

    for(unsigned row = 0; row < height; ++row) {
        for(unsigned col = 0; col < width; ++col) {
            unsigned char* srcPixel = src.mPixels + GetPixelOffset(srcCol + col, srcRow + row, src.mWidth, src.mHeight, src.mFormat);
            unsigned char* destPixel = mPixels + GetPixelOffset(destCol + col, destRow + row, mWidth, mHeight, mFormat);
            
            if(converter){
                converter(srcPixel, destPixel);
            } else {
                memcpy(destPixel, srcPixel, mFormat);
            }
        }
    }
}

void backlash::Bitmap::Set(unsigned width, unsigned height, E_FORMAT format, const unsigned char* pixels) {
    if(width == 0) {
        throw std::runtime_error("Zero width bitmap.");
    }

    if(height == 0) {
        throw std::runtime_error("Zero height bitmap.");
    }

    if(format <= 0 || format > 4) {
        throw std::runtime_error("Invalid bitmap format.");
    }

    mWidth = width;
    mHeight = height;
    mFormat = format;

    size_t newSize = mWidth * mHeight * mFormat;
    if(mPixels) {
        mPixels = (unsigned char*)realloc(mPixels, newSize);
    } else {
        mPixels = (unsigned char*)malloc(newSize);
    }

    if(mPixels) {
        memcpy(mPixels, pixels, newSize);
    }
}