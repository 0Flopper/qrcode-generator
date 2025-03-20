// Função que salva o QR Code em formato PNG e retorna o caminho do arquivo salvo
#include "PNGWriterService.h"
#include <iostream>

std::string PNGWriterService::saveToPNG(QRcode* qrcode, const std::string& fileName, int scale) {
    if (!qrcode) {
        std::cerr << "QR code inválido!" << std::endl;
        return "";
    }

    // Definir caminho do arquivo (garantindo que termine com .png)
    std::string filePath = "/tmp/" + fileName;
    if (filePath.find(".png") == std::string::npos) {
        filePath += ".png";  // Adiciona extensão caso não tenha
    }

    FILE* fp = fopen(filePath.c_str(), "wb");
    if (!fp) {
        std::cerr << "Erro ao abrir arquivo: " << filePath << std::endl;
        return "";
    }

    png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (!png) {
        std::cerr << "Erro ao criar estrutura PNG!" << std::endl;
        fclose(fp);
        return "";
    }

    png_infop info = png_create_info_struct(png);
    if (!info) {
        std::cerr << "Erro ao criar info do PNG!" << std::endl;
        png_destroy_write_struct(&png, nullptr);
        fclose(fp);
        return "";
    }

    if (setjmp(png_jmpbuf(png))) {
        std::cerr << "Erro ao inicializar escrita PNG!" << std::endl;
        png_destroy_write_struct(&png, &info);
        fclose(fp);
        return "";
    }

    png_init_io(png, fp);

    int size = qrcode->width;
    int imageSize = size * scale;

    png_set_IHDR(png, info, imageSize, imageSize, 8, PNG_COLOR_TYPE_GRAY, 
                 PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);

    png_write_info(png, info);

    std::vector<png_byte> row(imageSize, 255);  // Linha branca

    for (int y = 0; y < size; ++y) {
        for (int i = 0; i < scale; ++i) {  // Duplicar a linha `scale` vezes
            std::vector<png_byte> row(imageSize, 255);  // Linha branca
            for (int x = 0; x < size; ++x) {
                bool isBlack = qrcode->data[y * size + x] & 1;
                for (int j = 0; j < scale; ++j) {
                    row[(x * scale) + j] = isBlack ? 0 : 255;
                }
            }
            png_write_row(png, row.data());
        }
    }
    

    png_write_end(png, nullptr);
    png_destroy_write_struct(&png, &info);
    fclose(fp);

    return filePath;
}
