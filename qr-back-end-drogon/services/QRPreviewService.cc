#include "QRPreviewService.h"
#include <iostream>
#include <cstdio>
#include <png.h>

// Estrutura para armazenar o buffer de memória
struct PngMemoryBuffer {
    std::vector<png_byte> data;
};

// Função de escrita customizada para o libpng que insere os dados no buffer
static void pngMemoryWrite(png_structp png_ptr, png_bytep data, png_size_t length) {
    PngMemoryBuffer* memBuffer = reinterpret_cast<PngMemoryBuffer*>(png_get_io_ptr(png_ptr));
    memBuffer->data.insert(memBuffer->data.end(), data, data + length);
};

// Função que gera o PNG em memória para preview com tamanho fixo (scale fixo)
std::vector<png_byte> QRPreviewService::generateQRPreview(QRcode* qrcode) {
    std::vector<png_byte> emptyResult;
    if (!qrcode) {
        std::cerr << "QR code inválido!" << std::endl;
        return emptyResult;
    }
    
    int scale = 50;
    int size = qrcode->width;
    int imageSize = size * scale;

    // Cria as estruturas do libpng
    png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (!png_ptr) {
        std::cerr << "Erro ao criar estrutura PNG!" << std::endl;
        return emptyResult;
    }

    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) {
        std::cerr << "Erro ao criar info do PNG!" << std::endl;
        png_destroy_write_struct(&png_ptr, nullptr);
        return emptyResult;
    }

    // Configura tratamento de erro
    if (setjmp(png_jmpbuf(png_ptr))) {
        std::cerr << "Erro durante a geração do PNG em memória!" << std::endl;
        png_destroy_write_struct(&png_ptr, &info_ptr);
        return emptyResult;
    }

    // Inicializa o buffer de memória
    PngMemoryBuffer memBuffer;

    // Configura o png para escrever no buffer de memória
    png_set_write_fn(png_ptr, &memBuffer, pngMemoryWrite, nullptr);

    // Define cabeçalho da imagem
    png_set_IHDR(png_ptr, info_ptr, imageSize, imageSize, 8, PNG_COLOR_TYPE_GRAY,
                 PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
    png_write_info(png_ptr, info_ptr);

    // Escreve os dados da imagem, expandindo cada módulo do QR conforme o scale
    for (int y = 0; y < size; ++y) {
        for (int i = 0; i < scale; ++i) {  // Duplicar a linha scale vezes
            std::vector<png_byte> row(imageSize, 255);  // Linha branca
            for (int x = 0; x < size; ++x) {
                bool isBlack = qrcode->data[y * size + x] & 1;
                for (int j = 0; j < scale; ++j) {
                    row[(x * scale) + j] = isBlack ? 0 : 255;
                }
            }
            png_write_row(png_ptr, row.data());
        }
    }

    png_write_end(png_ptr, info_ptr);
    png_destroy_write_struct(&png_ptr, &info_ptr);

    // Retorna o buffer com os dados do PNG
    return memBuffer.data;
}


