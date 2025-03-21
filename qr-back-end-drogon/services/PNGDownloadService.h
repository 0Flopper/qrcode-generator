#ifndef PNG_DOWNLOAD_SERVICE_H
#define PNG_DOWNLOAD_SERVICE_H

#include "qrencode.h"
#include <png.h>
#include <string>

class PNGDownloadService {
public:
    static std::string saveToPNG(QRcode* qrcode, const std::string& filePath, int scale);
};

#endif
