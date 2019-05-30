#ifndef POINT_CLOUD_STRUCTS_HPP_CNELSON
#define POINT_CLOUD_STRUCTS_HPP_CNELSON
#include <string>
// Header holds all information about las file
// __attribute__ ((packed)) used so that struct is tightly packed
// this only works for LLVM
// to compile on windows add "#pragma pack(1)"
struct __attribute__((packed)) Header {
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
  double maxX, minX;
  double maxY, minY;
  double maxZ, minZ;
};

struct __attribute__((packed)) PointRecord0 {
  uint32_t x, y, z;
  uint16_t intensity;
  uint8_t flags;  // bit 0, 1, 2 - return num; 3, 4, 5 num of returns; 6 -
                  // scan direction; 7 - edge of flightline
  uint8_t classification;
  uint8_t scanAngleRank;
  uint8_t userData;
  uint16_t pointSourceId;
};

struct __attribute__((packed)) PointRecord1 {
  uint32_t x, y, z;
  uint16_t intensity;
  uint8_t flags;  // bit 0, 1, 2 - return num; 3, 4, 5 num of returns; 6 -
                  // scan direction; 7 - edge of flightline
  uint8_t classification;
  uint8_t scanAngleRank;
  uint8_t userData;
  uint16_t pointSourceId;
  double gpsTime;
};

struct __attribute__((packed)) PointRecord2 {
  uint32_t x, y, z;
  uint16_t intensity;
  uint8_t flags;  // bit 0, 1, 2 - return num; 3, 4, 5 num of returns; 6 -
                  // scan direction; 7 - edge of flightline
  uint8_t classification;
  uint8_t scanAngleRank;
  uint8_t userData;
  uint16_t pointSourceId;
  uint16_t red;
  uint16_t green;
  uint16_t blue;
};

struct __attribute__((packed)) PointRecord3 {
  uint32_t x, y, z;
  uint16_t intensity;
  uint8_t flags;  // bit 0, 1, 2 - return num; 3, 4, 5 num of returns; 6 -
                  // scan direction; 7 - edge of flightline
  uint8_t classification;
  uint8_t scanAngleRank;
  uint8_t userData;
  uint16_t pointSourceId;
  double gpsTime;
  uint16_t red;
  uint16_t green;
  uint16_t blue;
};

struct Point {
  unsigned short int
      format;  // 0, 1, 2, 3 - corresponds with ASPRS point records
  double x, y, z;
  unsigned short int intensity;
  unsigned short int returnNum;
  unsigned short int numOfReturns;
  unsigned short int scanDirection;
  bool edge;
  unsigned short int classification;
  short int scanAngleRank;
  unsigned char userData;
  unsigned short int pointSourceId;
  double gpsTime;
  unsigned short int red;
  unsigned short int green;
  unsigned short int blue;
};
#endif