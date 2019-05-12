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
  void printHead(int n, bool longVersion = false);
  void printTail(int n, bool longVersion = false);
  std::vector<Point> getRadius(double radius, double x, double y, double z);
  std::vector<Point> convert2Ft(const std::vector<Point> &intialPoints);
  std::vector<Point> convert2Meters(const std::vector<Point> &intialPoints);
  std::vector<Point> sortByClass(const std::vector<Point> &intialPoints);
  void outputASCII(std::string path);
  void outputLAS(std::string path);
  std::vector<Point> removeAbnormalZValues(double radius, double x, double y,
                                           double z);
};