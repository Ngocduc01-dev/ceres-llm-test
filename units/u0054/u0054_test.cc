// FILE: u0054_test.cc
#include <algorithm>
#include <array>
#include <cstddef>
#include <iterator>
#include <memory>
#include <tuple>
#include <type_traits>

// Storage là class private của FixedArray: mở quyền truy cập chỉ trong file test.
#define private public
#include "ceres/internal/fixed_array.h"
#undef private

#include "gtest/gtest.h"

namespace {

using FixedArrayInt20 = ceres::internal::FixedArray<int, 20>;
using StorageType = FixedArrayInt20::Storage;

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(FixedArrayStorageBeginTest, P1_ReturnsData) {
  FixedArrayInt20::allocator_type allocator;
  StorageType storage(3, allocator);  // n = 3, trong khoảng [1, 5]
  storage.begin();
}

}  // namespace
