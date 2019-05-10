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
  std::vector<Point> getRadiusN(int n, double x, double y, double z);
  std::vector<Point> convert2Ft(std::vector<Point> intialPoints);
  std::vector<Point> convert2Meters(std::vector<Point> intial Points);
  std::vector<Point> sortByClass(std::vector<Point> intial Points);
};