#ifndef BITMAP_H
#define BITMAP_H

#include <string>

namespace backlash {
    // A bitmap image (a grid of pixels)

    class Bitmap {
    public:
        // Represent the number of channels per pixel and order the channels.
        enum E_FORMAT {
            E_FORMAT_GREYSCALE = 1,         // one byte
            E_FORMAT_GREYSCALEALPHA = 2,    // two bytes
            E_FORMAT_RGB = 3,               // three bytes
            E_FORMAT_RGBA = 4               // four bytes
        };

        // Creates a new image with the specified width, height, and format.

        // Note: Width and Height are in pixels. if pixels = null, it'll
        // contain garbage.

        Bitmap(unsigned width, unsigned height, E_FORMAT format, 
            const unsigned char* pixels = NULL);
        ~Bitmap();

        // load the given file onto a backlash bitmap/
        static Bitmap BitmapFromFile(std::string FilePath);

        // width in pixels
        unsigned Width() const;

        // height in pixels
        unsigned Height() const;

        // the pixel format of the bitmap
        E_FORMAT Format() const;

        // Pointer to the raw pixel data of the bitmap.
        unsigned char* PixelBuffer() const;

        // Returns a pointer to the start of the pixel at the given coordinates. 
        // The size of the pixel depends on the 'Format' of the image.
        unsigned char* GetPixel(unsigned int column, unsigned int row) const;

        // sets the raw pixel data at the given coordinates.
        void SetPixel(unsigned int column, unsigned int row, const unsigned char* pixel);


        // Reverses the row order of the pixels so the bitmap will
        // be upside down
        void FlipVertically();

        // Rotates the image 90 degrees counter clockwise.
        void Rotate90CounterClockwise();

        // Copies a rectangular area from the given source bitmap to this bitmap.
        //
        // If srcCol, srcRow, width, and hight are all zero, the entire source 
        // bitmap will be copied. (full width and height)
        //
        // If the source bitmap has a different format to the destination
        // bitmap, the pixels will be converted to match the destination
        // format.
        //
        // Will throw an exception if the source and destination bitmaps 
        // are the same or if the source and destination rectangles overlap.
        // If you want to copy a bitmap onto itself, then make a copy of 
        // the bitmap first.
        void CopyRectFromBitmap(const Bitmap& src, unsigned srcCol,
                                unsigned srcRow, unsigned destCol,
                                unsigned destRow, unsigned width,
                                unsigned height);

        // Copy construcctor 
        Bitmap(const Bitmap& bitmap);

        // Assignment operator
        Bitmap& operator = (const Bitmap& bitmap);

    private:
        E_FORMAT mFormat;
        unsigned mWidth;
        unsigned mHeight;
        unsigned char* mPixels;

        void Set(unsigned width, unsigned height, E_FORMAT format, const unsigned char* pixels);
        // static inline unsigned GetPixelOffset(unsigned col, unsigned row, unsigned width, unsigned height, E_FORMAT format);

    };
}

#endif