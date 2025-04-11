#ifndef SVG_WRITER_H
#define SVG_WRITER_H

#include <vector>
#include <string>

class SvgWriter {

public:
    static std::string generateSvg(const std::vector<unsigned char>& qrData, int qrSize, int scale);

private:
    static void writeQrData(std::ostringstream& svg, const std::vector<unsigned char>& qrData, int qrSize);
    
};

#endif // SVG_WRITER_H
