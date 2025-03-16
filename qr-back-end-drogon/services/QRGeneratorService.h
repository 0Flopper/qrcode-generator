#ifndef QR_GENERATOR_SERVICE_H
#define QR_GENERATOR_SERVICE_H

#include <string>
#include <qrencode.h>

class QRGeneratorService {
public:
    static QRcode* generate(const std::string& data);
};

#endif
