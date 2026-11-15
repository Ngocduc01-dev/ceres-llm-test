// FILE: u0487_test.cc
#include "gtest/gtest.h"
#include "ceres/stl_util.h"

namespace ceres {
namespace internal {

namespace {

// Tạo vector con trỏ int cấp phát động từ các giá trị cho trước.
std::vector<int*> MakePointers(const std::vector<int>& values) {
  std::vector<int*> result;
  for (size_t i = 0; i < values.size(); ++i) {
    result.push_back(new int(values[i]));
  }
  return result;
}

}  // namespace

// P1: node 1: sai (0 lần lặp)
TEST(STLDeleteContainerPointersTest, TC1_ZeroIterations) {
  std::vector<int*> v;
  STLDeleteContainerPointers(v.begin(), v.end());
}

// P2: node 1: đúng, sai (1 lần lặp)
TEST(STLDeleteContainerPointersTest, TC2_OneIteration) {
  std::vector<int*> v = MakePointers({17});
  STLDeleteContainerPointers(v.begin(), v.end());
}

// P3: node 1: đúng, đúng, sai (2 lần lặp)
TEST(STLDeleteContainerPointersTest, TC3_TwoIterations) {
  std::vector<int*> v = MakePointers({5, 83});
  STLDeleteContainerPointers(v.begin(), v.end());
}

// P4: node 1: đúng x3, sai (3 lần lặp, giá trị ở giữa)
TEST(STLDeleteContainerPointersTest, TC4_ThreeIterations) {
  std::vector<int*> v = MakePointers({29, 61, 4});
  STLDeleteContainerPointers(v.begin(), v.end());
}

// P5: node 1: đúng x4, sai (4 lần lặp = n-1)
TEST(STLDeleteContainerPointersTest, TC5_FourIterations) {
  std::vector<int*> v = MakePointers({12, 90, 37, 58});
  STLDeleteContainerPointers(v.begin(), v.end());
}

// P6: node 1: đúng x5, sai (5 lần lặp = n)
TEST(STLDeleteContainerPointersTest, TC6_FiveIterations) {
  std::vector<int*> v = MakePointers({71, 3, 46, 25, 99});
  STLDeleteContainerPointers(v.begin(), v.end());
}

}  // namespace internal
}  // namespace ceres
