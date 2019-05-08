#include <iostream>
#include "PointCloud.hpp"

int main() {
  PointCloud pc(
      "/Users/christiannelson/Documents/LiDAR-tools/test-data/mingo.las");
  pc.printHeader();
  return 0;
}