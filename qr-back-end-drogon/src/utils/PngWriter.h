#ifndef PNG_WRITER_H
#define PNG_WRITER_H

#include <vector>
#include <png.h>

class PngWriter {
public:
    static void writeImage(const std::vector<unsigned char>& qrData, int qrSize, int scale, std::vector<unsigned char>& buffer);

private:
    static void writeImageRows(png_structp pngPtr, const unsigned char* data, int qrSize, int scale);
};

#endif // PNG_WRITER_H
