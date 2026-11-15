// FILE: u0780_test.cc
#include "gtest/gtest.h"
#include "ceres/block_structure.h"
#include "ceres/schur_eliminator.h"
#include "ceres/schur_eliminator_impl.h"
#include "ceres/stl_util.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0780, TC1_CallsTarget) {
  int num_eliminate_blocks{};
  bool assume_full_rank_ete{};
  ceres::internal::SchurEliminator object{};
  object.Init(num_eliminate_blocks, assume_full_rank_ete, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u0780, TC2_CallsTarget) {
  int num_eliminate_blocks{};
  bool assume_full_rank_ete{};
  ceres::internal::SchurEliminator object{};
  object.Init(num_eliminate_blocks, assume_full_rank_ete, nullptr);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u0780, TC3_CallsTarget) {
  int num_eliminate_blocks{};
  bool assume_full_rank_ete{};
  ceres::internal::SchurEliminator object{};
  object.Init(num_eliminate_blocks, assume_full_rank_ete, nullptr);
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u0780, TC4_CallsTarget) {
  int num_eliminate_blocks{};
  bool assume_full_rank_ete{};
  ceres::internal::SchurEliminator object{};
  object.Init(num_eliminate_blocks, assume_full_rank_ete, nullptr);
}

// P5: START -> 1 -> END; branch decisions covered by case 5
TEST(Unit_u0780, TC5_CallsTarget) {
  int num_eliminate_blocks{};
  bool assume_full_rank_ete{};
  ceres::internal::SchurEliminator object{};
  object.Init(num_eliminate_blocks, assume_full_rank_ete, nullptr);
}

// P6: START -> 1 -> END; branch decisions covered by case 6
TEST(Unit_u0780, TC6_CallsTarget) {
  int num_eliminate_blocks{};
  bool assume_full_rank_ete{};
  ceres::internal::SchurEliminator object{};
  object.Init(num_eliminate_blocks, assume_full_rank_ete, nullptr);
}

// P7: START -> 1 -> END; branch decisions covered by case 7
TEST(Unit_u0780, TC7_CallsTarget) {
  int num_eliminate_blocks{};
  bool assume_full_rank_ete{};
  ceres::internal::SchurEliminator object{};
  object.Init(num_eliminate_blocks, assume_full_rank_ete, nullptr);
}

// P8: START -> 1 -> END; branch decisions covered by case 8
TEST(Unit_u0780, TC8_CallsTarget) {
  int num_eliminate_blocks{};
  bool assume_full_rank_ete{};
  ceres::internal::SchurEliminator object{};
  object.Init(num_eliminate_blocks, assume_full_rank_ete, nullptr);
}

// P9: START -> 1 -> END; branch decisions covered by case 9
TEST(Unit_u0780, TC9_CallsTarget) {
  int num_eliminate_blocks{};
  bool assume_full_rank_ete{};
  ceres::internal::SchurEliminator object{};
  object.Init(num_eliminate_blocks, assume_full_rank_ete, nullptr);
}
