#ifndef PNG_WRITER_SERVICE_H
#define PNG_WRITER_SERVICE_H

#include "qrencode.h"
#include <png.h>
#include <vector>
#include <string>

class PNGWriterService {
public:
    static std::string saveToPNG(QRcode* qrcode, const std::string& filePath, int scale);
};

#endif
