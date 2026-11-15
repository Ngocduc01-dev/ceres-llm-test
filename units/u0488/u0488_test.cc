// FILE: u0488_test.cc
#include <vector>

#include "gtest/gtest.h"
#include "ceres/stl_util.h"

// Path P1: START -> 1 -> END (node 1: sai, 0 lần lặp)
TEST(STLDeleteUniqueContainerPointersTest, ZeroElements) {
  std::vector<int*> v;
  ceres::STLDeleteUniqueContainerPointers(v.begin(), v.end());
}

// Path P2: START -> 1 -> 2 -> 1 -> END (node 1: đúng rồi sai, 1 lần lặp)
TEST(STLDeleteUniqueContainerPointersTest, OneElement) {
  std::vector<int*> v;
  v.push_back(new int(7));
  ceres::STLDeleteUniqueContainerPointers(v.begin(), v.end());
}

// Path P3: (1 -> 2) x2 -> 1 -> END (node 1: đúng x2 rồi sai, 2 lần lặp)
TEST(STLDeleteUniqueContainerPointersTest, TwoElements) {
  std::vector<int*> v;
  v.push_back(new int(3));
  v.push_back(new int(9));
  ceres::STLDeleteUniqueContainerPointers(v.begin(), v.end());
}

// Path P4: (1 -> 2) x3 -> 1 -> END (node 1: đúng x3 rồi sai, 3 lần lặp)
TEST(STLDeleteUniqueContainerPointersTest, ThreeElements) {
  std::vector<int*> v;
  v.push_back(new int(5));
  v.push_back(new int(2));
  v.push_back(new int(8));
  ceres::STLDeleteUniqueContainerPointers(v.begin(), v.end());
}

// Path P5: (1 -> 2) x4 -> 1 -> END (node 1: đúng x4 rồi sai, 4 lần lặp)
TEST(STLDeleteUniqueContainerPointersTest, FourElements) {
  std::vector<int*> v;
  v.push_back(new int(1));
  v.push_back(new int(6));
  v.push_back(new int(4));
  v.push_back(new int(10));
  ceres::STLDeleteUniqueContainerPointers(v.begin(), v.end());
}

// Path P6: (1 -> 2) x5 -> 1 -> END (node 1: đúng x5 rồi sai, 5 lần lặp)
TEST(STLDeleteUniqueContainerPointersTest, FiveElements) {
  std::vector<int*> v;
  v.push_back(new int(11));
  v.push_back(new int(3));
  v.push_back(new int(7));
  v.push_back(new int(2));
  v.push_back(new int(9));
  ceres::STLDeleteUniqueContainerPointers(v.begin(), v.end());
}
