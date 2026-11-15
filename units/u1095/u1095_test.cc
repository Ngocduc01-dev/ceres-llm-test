// FILE: u1095_test.cc
#include "gtest/gtest.h"
#include "ceres/types.h"

// P1: START -> 1 -> 2 (đúng) -> 3 -> END
TEST(StringToDoglegTypeTest, TraditionalDogleg) {
  ceres::DoglegType type = ceres::TRADITIONAL_DOGLEG;
  ceres::StringToDoglegType("traditional_dogleg", &type);
}

// P2: START -> 1 -> 2 (sai) -> 4 (đúng) -> 5 -> END
TEST(StringToDoglegTypeTest, SubspaceDogleg) {
  ceres::DoglegType type = ceres::TRADITIONAL_DOGLEG;
  ceres::StringToDoglegType("subspace_dogleg", &type);
}

// P3: START -> 1 -> 2 (sai) -> 4 (sai) -> 6 -> END
TEST(StringToDoglegTypeTest, UnknownDoglegType) {
  ceres::DoglegType type = ceres::TRADITIONAL_DOGLEG;
  ceres::StringToDoglegType("unknown_dogleg", &type);
}
