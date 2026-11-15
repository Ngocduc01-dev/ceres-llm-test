// FILE: u0489_test.cc
#include "gtest/gtest.h"
#include "ceres/stl_util.h"

namespace ceres {

// P1: node 1: đúng
TEST(STLDeleteElementsTest, NullContainer) {
  STLDeleteElements<std::vector<int*>>(nullptr);
}

// P2: node 1: sai
TEST(STLDeleteElementsTest, NonNullContainer) {
  std::vector<int*> container;
  container.push_back(new int(10));
  container.push_back(new int(20));
  container.push_back(new int(30));
  STLDeleteElements(&container);
}

}  // namespace ceres
