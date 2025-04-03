#ifndef QR_GENERATOR_H
#define QR_GENERATOR_H

#include <string>
#include <vector>
#include <memory>

struct QrCodeData {
    std::vector<unsigned char> data;
    int width;
};

class QrService {
public:
    static std::unique_ptr<QrCodeData> generate(const std::string& data);
};

#endif // QR_GENERATOR_H
