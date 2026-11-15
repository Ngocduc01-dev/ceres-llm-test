// FILE: u0529_test.cc
#include "gtest/gtest.h"
#include "ceres/parallel_utils.h"

namespace ceres {
namespace internal {

// P1: START -> 1 -> 2 -> 3 -> 4 -> END (node 1: đúng, node 3: đúng)
// Path P1: START -> CFG nodes -> END.
TEST(LinearIndexToUpperTriangularIndexTest, OddNJ0GreaterOrEqualI0) {
  int i = 0;
  int j = 0;
  LinearIndexToUpperTriangularIndex(2, 5, &i, &j);
}

// P2: START -> 1 -> 2 -> 3 -> 5 -> END (node 1: đúng, node 3: sai)
// Path P1: START -> CFG nodes -> END.
TEST(LinearIndexToUpperTriangularIndexTest, OddNJ0LessThanI0) {
  int i = 0;
  int j = 0;
  LinearIndexToUpperTriangularIndex(11, 5, &i, &j);
}

// P3: START -> 1 -> 6 -> 7 -> 8 -> END (node 1: sai, node 7: đúng)
// Path P1: START -> CFG nodes -> END.
TEST(LinearIndexToUpperTriangularIndexTest, EvenNJ0GreaterThanI0) {
  int i = 0;
  int j = 0;
  LinearIndexToUpperTriangularIndex(2, 4, &i, &j);
}

// P4: START -> 1 -> 6 -> 7 -> 9 -> END (node 1: sai, node 7: sai)
// Path P1: START -> CFG nodes -> END.
TEST(LinearIndexToUpperTriangularIndexTest, EvenNJ0LessOrEqualI0) {
  int i = 0;
  int j = 0;
  LinearIndexToUpperTriangularIndex(6, 4, &i, &j);
}

}  // namespace internal
}  // namespace ceres
