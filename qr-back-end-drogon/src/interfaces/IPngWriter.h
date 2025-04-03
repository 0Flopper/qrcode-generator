#ifndef IPNGWRITER_H
#define IPNGWRITER_H

#include <vector>

class IPngWriter {
public:
    virtual void writeImage(const std::vector<unsigned char>& qrData, int size, int scale, std::vector<unsigned char>& buffer) = 0;
    virtual ~IPngWriter() = default;
};

#endif // IPNGWRITER_H
