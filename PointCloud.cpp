#include "PointCloud.hpp"

using namespace std;

/*
** Default Constructor
*/
PointCloud::PointCloud() { fileLoaded = false; }

/*
** Constructor
** takes in the path of the .las and then calls read
*/
PointCloud::PointCloud(const string &path) { read(path); }

/*
** extractFlagVals
** Input: 8 bit flags, number of bits to extract, position to extract from
** Output: int values that flags represent
*/
unsigned short int PointCloud::extractFlagVals(uint8_t flags, int bits,
                                               int pos) {
  return (((1 << bits) - 1) & (flags >> (pos)));
}

/*
** read
** Input: path to .las in format 1.2
** Output: header is filled, points are filled
** Notes: all point record formats specified by ASPRS are
** taken into account. points will have null members
** depending on the point record format
*/
void PointCloud::read(const string &path) {
  ifstream inLAS(path, ios::binary);

  // read las header - verifiy it is 1.2
  if (inLAS.is_open()) {
    inLAS.read((char *)&header, sizeof(header));
    if ((int)header.headerSize != sizeof(header)) {
      throw runtime_error("Header does not match 1.2 las format");
    }
  } else {
    throw runtime_error("LAS not found");
  }
  inLAS.seekg(header.pointDataOffset);
  // define a new array to hold raw point records
  // in one of 4 formats specificed by ASPRS
  if ((int)header.pointDataRecordFormat == 0) {
    PointRecord0 rawPoint;
    for (uint32_t i = 0; i < header.numberOfPoints; i++) {
      inLAS.read((char *)&rawPoint, sizeof(PointRecord0));
      // convert raw point record to a generic point type
      Point p = {0,
                 ((double)rawPoint.x * header.scaleX) + header.offX,
                 ((double)rawPoint.y * header.scaleY) + header.offY,
                 ((double)rawPoint.z * header.scaleZ) + header.offZ,
                 (unsigned short int)rawPoint.intensity,
                 (unsigned short int)(((1 << 3) - 1) & (rawPoint.flags >> (0))),
                 (unsigned short int)(((1 << 3) - 1) & (rawPoint.flags >> (3))),
                 (unsigned short int)(((1 << 1) - 1) & (rawPoint.flags >> (6))),
                 (bool)(((1 << 1) - 1) & (rawPoint.flags >> (7))),
                 (unsigned short int)rawPoint.classification,
                 (short int)rawPoint.scanAngleRank,
                 (unsigned char)rawPoint.userData,
                 (unsigned short int)rawPoint.pointSourceId,
                 (double)NULL,
                 (unsigned short int)NULL,
                 (unsigned short int)NULL,
                 (unsigned short int)NULL};
      points.push_back(p);
      if (!inLAS.good()) {
        throw runtime_error("LAS point reading failed");
      }
    }
  } else if ((int)header.pointDataRecordFormat == 1) {
    PointRecord1 rawPoint;
    for (uint32_t i = 0; i < header.numberOfPoints; i++) {
      inLAS.read((char *)&rawPoint, sizeof(PointRecord1));
      // convert raw point record to a generic point type
      Point p = {1,
                 ((double)rawPoint.x * header.scaleX) + header.offX,
                 ((double)rawPoint.y * header.scaleY) + header.offY,
                 ((double)rawPoint.z * header.scaleZ) + header.offZ,
                 (unsigned short int)rawPoint.intensity,
                 (unsigned short int)(((1 << 3) - 1) & (rawPoint.flags >> (0))),
                 (unsigned short int)(((1 << 3) - 1) & (rawPoint.flags >> (3))),
                 (unsigned short int)(((1 << 1) - 1) & (rawPoint.flags >> (6))),
                 (bool)(((1 << 1) - 1) & (rawPoint.flags >> (7))),
                 (unsigned short int)rawPoint.classification,
                 (short int)rawPoint.scanAngleRank,
                 (unsigned char)rawPoint.userData,
                 (unsigned short int)rawPoint.pointSourceId,
                 rawPoint.gpsTime,
                 (unsigned short int)NULL,
                 (unsigned short int)NULL,
                 (unsigned short int)NULL};
      points.push_back(p);
      if (!inLAS.good()) {
        throw runtime_error("LAS point reading failed");
      }
    }
  } else if ((int)header.pointDataRecordFormat == 2) {
    PointRecord2 rawPoint;
    for (uint32_t i = 0; i < header.numberOfPoints; i++) {
      inLAS.read((char *)&rawPoint, sizeof(PointRecord2));
      // convert raw point record to a generic point type
      Point p = {2,
                 ((double)rawPoint.x * header.scaleX) + header.offX,
                 ((double)rawPoint.y * header.scaleY) + header.offY,
                 ((double)rawPoint.z * header.scaleZ) + header.offZ,
                 (unsigned short int)rawPoint.intensity,
                 (unsigned short int)(((1 << 3) - 1) & (rawPoint.flags >> (0))),
                 (unsigned short int)(((1 << 3) - 1) & (rawPoint.flags >> (3))),
                 (unsigned short int)(((1 << 1) - 1) & (rawPoint.flags >> (6))),
                 (bool)(((1 << 1) - 1) & (rawPoint.flags >> (7))),
                 (unsigned short int)rawPoint.classification,
                 (unsigned char)rawPoint.scanAngleRank,
                 (unsigned char)rawPoint.userData,
                 (unsigned short int)rawPoint.pointSourceId,
                 (double)NULL,
                 (unsigned short int)rawPoint.red,
                 (unsigned short int)rawPoint.green,
                 (unsigned short int)rawPoint.blue};
      points.push_back(p);
      if (!inLAS.good()) {
        throw runtime_error("LAS point reading failed");
      }
    }
  } else if ((int)header.pointDataRecordFormat == 3) {
    PointRecord3 rawPoint;
    inLAS.read((char *)&rawPoint, sizeof(PointRecord3));
    // convert raw point record to a generic point type
    Point p = {3,
               ((double)rawPoint.x * header.scaleX) + header.offX,
               ((double)rawPoint.y * header.scaleY) + header.offY,
               ((double)rawPoint.z * header.scaleZ) + header.offZ,
               (unsigned short int)rawPoint.intensity,
               (unsigned short int)(((1 << 3) - 1) & (rawPoint.flags >> (0))),
               (unsigned short int)(((1 << 3) - 1) & (rawPoint.flags >> (3))),
               (unsigned short int)(((1 << 1) - 1) & (rawPoint.flags >> (6))),
               (bool)(((1 << 1) - 1) & (rawPoint.flags >> (7))),
               (unsigned short int)rawPoint.classification,
               (short int)rawPoint.scanAngleRank,
               (unsigned char)rawPoint.userData,
               (unsigned short int)rawPoint.pointSourceId,
               rawPoint.gpsTime,
               (unsigned short int)rawPoint.red,
               (unsigned short int)rawPoint.green,
               (unsigned short int)rawPoint.blue};
    points.push_back(p);
    if (!inLAS.good()) {
      throw runtime_error("LAS point reading failed");
    }
  } else {
    throw runtime_error("Unknown record format");
  }
  fileLoaded = true;
}

/*
** printHeader
** print all info in las header
*/
void PointCloud::printHeader() {
  int prec = 3;
  cout << fixed << setprecision(prec);
  cout << "magic = ";
  for (int i = 0; i < 4; i++) {
    cout << header.magic[i];
  }
  cout << endl;
  cout << "fileSourceID = " << (int)header.fileSourceID << endl;
  cout << "globalEncoding = " << (int)header.globalEncoding << endl;
  if (header.guidData1) {
    cout << "guidData1 = " << (long)header.guidData1 << endl;
  }
  if (header.guidData2) {
    cout << "guidData2 = " << (long)header.guidData2 << endl;
  }
  if (header.guidData1) {
    cout << "guidData3 = " << (long)header.guidData3 << endl;
  }

  if (header.guidData4[0]) {
    cout << "guidData4: ";
    for (int i = 0; i < 8; i++) {
      cout << (char)header.guidData4[i] << " ";
    }
    cout << endl;
  }
  cout << "version = " << (int)header.versionMaj << "."
       << (int)header.versionMin << endl;
  cout << "systemIdentifier: ";
  for (int i = 0; i < 32; i++) {
    cout << (char)header.systemIdentifier[i];
  }
  cout << endl;
  cout << "genSoftware: ";
  for (int i = 0; i < 32; i++) {
    cout << header.genSoftware[i];
  }
  cout << endl;
  if (header.creationYear) {
    cout << "creationDay = " << (int)header.creationDay
         << ", creationYear = " << (int)header.creationYear << endl;
  }
  cout << "headerSize = " << (int)header.headerSize << endl;
  cout << "pointDataOffset = " << (long)header.pointDataOffset << endl;
  cout << "numVarLenRecords = " << (long)header.numVarLenRecords << endl;
  cout << "pointDataRecordFormat = " << (int)header.pointDataRecordFormat
       << endl;
  cout << "pointDataRecordLen = " << (int)header.pointDataRecordLen << endl;
  cout << "numberOfPoints = " << (long)header.numberOfPoints << endl;
  cout << "numPointsByReturn: ";
  for (int i = 0; i < 5; i++) {
    cout << i << ":" << (long)header.numPointsByReturn[i] << " ";
  }
  cout << endl;
  cout << setw(10) << "scaleX = " << setw(12) << header.scaleX << "\t";
  cout << setw(10) << "scaleY = " << setw(12) << header.scaleY << "\t";
  cout << setw(10) << "scaleZ = " << setw(12) << header.scaleZ << endl;
  cout << setw(10) << "offX = " << setw(12) << header.offX << "\t";
  cout << setw(10) << "offY = " << setw(12) << header.offY << "\t";
  cout << setw(10) << "offZ = " << setw(12) << header.offZ << endl;
  cout << setw(10) << "minX = " << setw(12) << header.minX << "\t";
  cout << setw(10) << "minY = " << setw(12) << header.minY << "\t";
  cout << setw(10) << "minZ = " << setw(12) << header.minZ << endl;
  cout << setw(10) << "maxX = " << setw(12) << header.maxX << "\t";
  cout << setw(10) << "maxY = " << setw(12) << header.maxY << "\t";
  cout << setw(10) << "maxZ = " << setw(12) << header.maxZ << endl;
}
/*
** printHead
** print the first n coordinates
*/
void PointCloud::printHead(int n, bool longVerision) {
  char sep = ',';
  int prec = 3;
  assert(fileLoaded);
  if (!longVerision) {
    cout << "x" << sep << "y" << sep << "z" << endl;
    for (vector<Point>::iterator it = points.begin(); it != points.cbegin() + n;
         ++it) {
      cout << fixed << setprecision(prec) << it->x << sep << it->y << sep
           << it->z << endl;
    }
  } else {
    cout << "x" << sep << "y" << sep << "z" << sep << "intensity" << sep
         << "returnNum" << sep << "numOfReturns" << sep << "scanDirection"
         << sep << "edge" << sep << "class" << sep << "scanAngleRank" << sep
         << "userData" << sep << "pointSourceId" << sep << "gpsTime" << sep
         << "red" << sep << "green" << sep << "blue" << endl;
    for (vector<Point>::iterator it = points.begin(); it != points.cbegin() + n;
         ++it) {
      cout << fixed << setprecision(prec) << it->x << sep << it->y << sep
           << it->z << sep << it->intensity << sep << it->returnNum << sep
           << it->numOfReturns << sep << it->scanDirection << sep << it->edge
           << sep << it->classification << sep << it->scanAngleRank << sep
           << it->userData << sep << it->pointSourceId << sep << it->gpsTime
           << sep << it->red << sep << it->blue << sep << it->green << endl;
    }
  }
  cout << "maxsize: " << points.max_size() << endl;
}

/*
** printTailXYZ
** print the last n coordinates
*/
void PointCloud::printTail(int n, bool longVersion) {
  char sep = ',';
  int prec = 3;
  assert(fileLoaded);
  if (!longVersion) {
    cout << "x" << sep << "y" << sep << "z" << endl;
    for (vector<Point>::reverse_iterator it = points.rbegin();
         it != points.crbegin() + n; ++it) {
      cout << fixed << setprecision(prec) << it->x << sep << it->y << sep
           << it->z << endl;
    }
  } else {
    cout << "x" << sep << "y" << sep << "z" << sep << "intensity" << sep
         << "returnNum" << sep << "numOfReturns" << sep << "scanDirection"
         << sep << "edge" << sep << "class" << sep << "scanAngleRank" << sep
         << "userData" << sep << "pointSourceId" << sep << "gpsTime" << sep
         << "red" << sep << "green" << sep << "blue" << endl;
    for (vector<Point>::reverse_iterator it = points.rbegin();
         it != points.crbegin() + n; ++it) {
      cout << fixed << setprecision(prec) << it->x << sep << it->y << sep
           << it->z << sep << it->intensity << sep << it->returnNum << sep
           << it->numOfReturns << sep << it->scanDirection << sep << it->edge
           << sep << it->classification << sep << it->scanAngleRank << sep
           << it->userData << sep << it->pointSourceId << sep << it->gpsTime
           << sep << it->red << sep << it->blue << sep << it->green << endl;
    }
  }
}

/*
** pointsPerSqUnit
** Output: Returns the number of points per square unit
** calculated based on the las header
*/
double PointCloud::pointsPerSqUnit() {
  assert(fileLoaded);
  double x = header.maxX - header.minX;
  double y = header.maxY - header.minY;
  return header.numberOfPoints / (x * y);
}

/*
** optimalBinSize
** Input: the desired points per bin
**        the points per square unit of the dataset
** Output: returns the square size of a bin
** Notes: this is meant to divide the dataset only roughly,
** the division of bins is based on 2D measurements
*/
int PointCloud::optimalBinSize(long pointsPerBin, double pointsPerSqUnit) {
  return ceil(sqrt(pointsPerBin / pointsPerSqUnit));
}