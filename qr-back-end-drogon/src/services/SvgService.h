#ifndef SVG_SERVICE_H
#define SVG_SERVICE_H

#include <vector>
#include <string>

class SvgService {
public:
    static std::string generateSvgResponse(const std::vector<unsigned char>& qrData, int qrSize, int scale = 10);
};

#endif // SVG_SERVICE_H
