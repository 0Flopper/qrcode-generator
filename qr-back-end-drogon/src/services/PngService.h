// PngService.h
#ifndef PNG_SERVICE_H
#define PNG_SERVICE_H

#include <vector>

class PngService {
public:
    static std::vector<unsigned char> generatePng(const std::vector<unsigned char>& qrData, int qrSize, int scale = 10);
};

#endif // PNG_SERVICE_H
