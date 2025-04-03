#include "QrService.h"
#include <qrencode.h>

std::unique_ptr<QrCodeData> QrService::generate(const std::string& data) {
    std::unique_ptr<QRcode, decltype(&QRcode_free)> qrcode(
        QRcode_encodeString(data.c_str(), 0, QR_ECLEVEL_Q, QR_MODE_8, 1), 
        QRcode_free
    );

    if (!qrcode) {
        return nullptr; // Falha ao gerar o QR code
    }

    auto qrData = std::make_unique<QrCodeData>();
    qrData->width = qrcode->width;
    qrData->data.assign(qrcode->data, qrcode->data + (qrcode->width * qrcode->width));

    return qrData;
}
