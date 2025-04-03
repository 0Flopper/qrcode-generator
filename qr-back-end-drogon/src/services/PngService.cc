#include "PngService.h"
#include "src/utils/PngWriter.h"

std::vector<unsigned char> PngService::generatePng(const std::vector<unsigned char>& qrData, int qrSize, int scale) {

    std::vector<unsigned char> pngBuffer;
    PngWriter::writeImage(qrData, qrSize, scale, pngBuffer);
    return pngBuffer;

}
