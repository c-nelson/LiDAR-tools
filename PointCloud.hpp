#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

class PointCloud
{
private:
    // Header holds all information about las file
    // __attribute__ ((packed)) used so that struct is tightly packed
    struct __attribute__((packed)) Header
    {
        char magic[4];
        uint16_t fileSourceID;
        uint16_t globalEncoding;
        uint32_t guidData1;
        uint16_t guidData2;
        uint16_t guidData3;
        uint8_t guidData4[8];
        uint8_t versionMaj, versionMin;
        char systemIdentifier[32];
        char genSoftware[32];
        uint16_t creationDay, creationYear;
        uint16_t headerSize;
        uint32_t pointDataOffset;
        uint32_t numVarLenRecords;
        uint8_t pointDataRecordFormat;
        uint16_t pointDataRecordLen;
        uint32_t numberOfPoints;
        uint32_t numPointsByReturn[5];
        double scaleX, scaleY, scaleZ;
        double offX, offY, offZ;
        double minX, minY, minZ;
        double maxX, maxY, maxZ;
    };

public:
    PointCloud(const std::string &path);
    void read(const std::string &path);
    void printHeader();
};