#include "SvgService.h"
#include "src/utils/SvgWriter.h"

std::string SvgService::generateSvgResponse(const std::vector<unsigned char> &qrData, int qrSize, int scale)
{
    return SvgWriter::generateSvg(qrData, qrSize, scale);
}
