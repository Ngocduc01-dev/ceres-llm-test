// FILE: u0327_test.cc
#include "gtest/gtest.h"
#include "ceres/line_search_direction.h"

class Unit0327Direction final : public ceres::internal::LineSearchDirection {
 public:
  bool NextDirection(const ceres::internal::LineSearchMinimizer::State&,
                     const ceres::internal::LineSearchMinimizer::State&,
                     ceres::internal::Vector*) override { return false; }
};

TEST(Unit_u0327, PathP1) {
  { Unit0327Direction target; }
}
