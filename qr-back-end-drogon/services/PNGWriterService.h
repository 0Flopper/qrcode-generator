#ifndef PNG_WRITER_SERVICE_H
#define PNG_WRITER_SERVICE_H

#include <vector>
#include <png.h>
#include <qrencode.h>

class PNGWriterService {
public:
    static std::vector<char> save(QRcode* qrcode);
};

#endif
