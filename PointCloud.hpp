#include <fstream>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include "PointCloudStructs.hpp"

class PointCloud {
 private:
  Header header;
  bool fileLoaded;
  std::vector<Point> points;

 public:
  PointCloud();
  PointCloud(const std::string &path);
  void read(const std::string &path);
  void printHeader();
  void printHeadXYZ(int n);
  void printTailXYZ(int n);
  void printHeadLong(int n);
  void printTailLong(int n);
};