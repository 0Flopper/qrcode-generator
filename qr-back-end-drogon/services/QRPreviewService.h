#ifndef QRPREVIEW_SERVICE_H
#define QRPREVIEW_SERVICE_H

#include <vector>
#include <qrencode.h>  // Biblioteca para gerar QR Codes
#include <png.h>

class QRPreviewService {
public:
    static std::vector<png_byte> generateQRPreview(QRcode* qrcode);
};

#endif
