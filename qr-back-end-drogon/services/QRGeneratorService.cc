#include "QRGeneratorService.h"

QRcode* QRGeneratorService::generate(const std::string& data) {
    return QRcode_encodeString(data.c_str(), 0, QR_ECLEVEL_Q, QR_MODE_8, 1);
}
