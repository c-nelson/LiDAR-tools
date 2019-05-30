#include <iostream>
#include "PointCloud.hpp"

int main() {
  PointCloud pc(
      "/Users/christiannelson/dev/LiDAR-tools/test-data/dod012319.las");
  pc.printHeader();
  // pc.printHead(100, true);
  // pc.printTail(100, true);
  return 0;
}