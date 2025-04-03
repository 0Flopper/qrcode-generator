#include "PngWriter.h"
#include <iostream>

void PngWriter::writeImage(const std::vector<unsigned char>& qrData, int qrSize, int scale, std::vector<unsigned char>& buffer) {
    int imageSize = qrSize * scale;

    png_structp pngPtr = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (!pngPtr) {
        std::cerr << "Erro ao criar estrutura PNG!" << std::endl;
        return;
    }

    png_infop infoPtr = png_create_info_struct(pngPtr);
    if (!infoPtr) {
        std::cerr << "Erro ao criar info do PNG!" << std::endl;
        png_destroy_write_struct(&pngPtr, nullptr);
        return;
    }

    if (setjmp(png_jmpbuf(pngPtr))) {
        std::cerr << "Erro durante a geração do PNG!" << std::endl;
        png_destroy_write_struct(&pngPtr, &infoPtr);
        return;
    }

    png_set_write_fn(pngPtr, &buffer, [](png_structp pngPtr, png_bytep data, png_size_t length) {
        auto* buf = reinterpret_cast<std::vector<unsigned char>*>(png_get_io_ptr(pngPtr));
        buf->insert(buf->end(), data, data + length);
    }, nullptr);

    png_set_IHDR(pngPtr, infoPtr, imageSize, imageSize, 8, PNG_COLOR_TYPE_GRAY, PNG_INTERLACE_NONE,
                 PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);

    png_write_info(pngPtr, infoPtr);
    writeImageRows(pngPtr, qrData.data(), qrSize, scale);
    png_write_end(pngPtr, infoPtr);
    png_destroy_write_struct(&pngPtr, &infoPtr);
}

void PngWriter::writeImageRows(png_structp pngPtr, const unsigned char* data, int qrSize, int scale) {
    int imageSize = qrSize * scale;

    for (int y = 0; y < qrSize; ++y) {
        for (int i = 0; i < scale; ++i) {
            std::vector<unsigned char> row(imageSize, 255);  // Linha branca

            for (int x = 0; x < qrSize; ++x) {
                bool isBlack = data[y * qrSize + x] & 1; // Mantendo a cor correta
                std::fill_n(row.begin() + (x * scale), scale, isBlack ? 0 : 255);
            }

            png_write_row(pngPtr, row.data());
        }
    }
}
