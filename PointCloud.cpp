#include "PointCloud.hpp"

using namespace std;

PointCloud::PointCloud() { fileLoaded = false; }

PointCloud::PointCloud(const string &path) { read(path); }

void PointCloud::read(const string &path) {
  ifstream inLAS(path, ios::binary);

  if (inLAS.is_open()) {
    inLAS.read((char *)&header, sizeof(header));
    if ((int)header.headerSize == sizeof(header)) {
      fileLoaded = true;
    } else {
      throw runtime_error("Header does not match 1.2 las format");
    }

  } else {
    throw runtime_error("LAS not found");
  }
}

void PointCloud::printHeader() {
  cout
      << "============================ HEADER INFO ============================"
      << endl;
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
  cout
      << "============================ HEADER  END ============================"
      << endl;
}