#include <sstream>
#include "SvgWriter.h"

std::string SvgWriter::generateSvg(const std::vector<unsigned char>& qrData, int qrSize, int scale) {
    const int imageSize = qrSize * scale;
    std::ostringstream svg;

    // Header + BG
    svg << "<?xml version=\"1.0\" standalone=\"no\"?>\n"
        << "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" "
        << "width=\"" << imageSize << "\" height=\"" << imageSize << "\" "
        << "viewBox=\"0 0 " << qrSize << " " << qrSize << "\">\n"
        << "<rect width=\"100%\" height=\"100%\" fill=\"white\"/>\n"
        << "<g fill=\"black\">\n";

    // QR Data
    writeQrData(svg, qrData, qrSize);

    // Closes the <g> and <svg> tags
    svg << "</g>\n</svg>\n";

    return svg.str();
}

void SvgWriter::writeQrData(std::ostringstream& svg, const std::vector<unsigned char>& qrData, int qrSize) {
    for (int y = 0; y < qrSize; ++y) {
        for (int x = 0; x < qrSize; ++x) {
            int index = y * qrSize + x;
            if (qrData[index] & 0x01) {
                svg << "<rect x=\"" << x << "\" y=\"" << y << "\" width=\"1\" height=\"1\" />\n";
            }
        }
    }
}
