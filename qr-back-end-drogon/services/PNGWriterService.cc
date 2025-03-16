#include "PNGWriterService.h"
#include <iostream>

// Função que salva o QR Code em formato PNG e retorna os dados da imagem em um buffer
std::vector<char> PNGWriterService::save(QRcode* qrcode) {
    // Cria um buffer para armazenar os dados da imagem PNG gerada
    std::vector<char> pngBuffer;

    // Verifica se o QR Code fornecido é válido
    if (!qrcode) {
        std::cerr << "QR Code inválido!" << std::endl;
        return pngBuffer;  // Retorna um buffer vazio em caso de erro
    }

    // Calcula o tamanho da imagem PNG com base no tamanho do QR Code
    int width = qrcode->width;
    int size = width * 10;  // Tamanho da imagem PNG será 10 vezes o tamanho do QR Code

    // Cria a estrutura PNG necessária para a escrita do arquivo PNG
    png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    png_infop info = png_create_info_struct(png);

    // Verifica se as estruturas foram criadas corretamente
    if (!png || !info) {
        // Libera as estruturas e exibe um erro caso falhe
        png_destroy_write_struct(&png, &info);
        std::cerr << "Erro ao criar estrutura PNG" << std::endl;
        return pngBuffer;  // Retorna um buffer vazio em caso de falha
    }

    // Define a compressão máxima para a imagem PNG
    png_set_compression_level(png, 9);

    // Define o cabeçalho da imagem PNG
    png_set_IHDR(png, info, size, size, 8, PNG_COLOR_TYPE_GRAY, PNG_INTERLACE_NONE,
                 PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);

    // Define uma função personalizada de escrita que armazena os dados no buffer
    png_set_write_fn(png, &pngBuffer, [](png_structp png, png_bytep data, png_size_t length) {
        std::vector<char>* buffer = static_cast<std::vector<char>*>(png_get_io_ptr(png));
        buffer->insert(buffer->end(), data, data + length);  // Insere os dados no buffer
    }, nullptr);

    // Aloca memória para armazenar as linhas da imagem PNG
    png_bytepp row_pointers = (png_bytepp)png_malloc(png, size * sizeof(png_bytep));

    // Preenche as linhas da imagem PNG com os dados do QR Code
    for (int y = 0; y < size; y++) {
        row_pointers[y] = (png_bytep)png_malloc(png, size);
        for (int x = 0; x < size; x++) {
            // Define a cor do pixel com base nos dados do QR Code
            row_pointers[y][x] = (qrcode->data[(y / 10) * width + (x / 10)] & 1) ? 0 : 255;
        }
    }

    // Define as linhas da imagem e escreve o arquivo PNG
    png_set_rows(png, info, row_pointers);
    png_write_png(png, info, PNG_TRANSFORM_IDENTITY, NULL);

    // Libera a memória alocada para as linhas da imagem PNG
    for (int y = 0; y < size; y++) {
        png_free(png, row_pointers[y]);
    }
    png_free(png, row_pointers);

    // Libera as estruturas PNG após a escrita
    png_destroy_write_struct(&png, &info);

    // Retorna o buffer contendo os dados da imagem PNG
    return pngBuffer;
}
