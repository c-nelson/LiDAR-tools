#include <iostream>
#include "PointCloud.hpp"

int main() {
  PointCloud pc(
      "/Users/christiannelson/Documents/LiDAR-tools/test-data/mingo.las");
  pc.printHeader();
  pc.printHeadXYZ(5);
  pc.printTailXYZ(8);
  return 0;
}