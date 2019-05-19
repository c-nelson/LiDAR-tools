#include <iostream>
#include "PointCloud.hpp"

int main() {
  PointCloud pc(
      "/Users/christiannelson/Documents/LiDAR-tools/test-data/mingo.las");
  pc.printHeader();
  pc.printHead(1000, true);
  // pc.printTail(8, true);
  return 0;
}