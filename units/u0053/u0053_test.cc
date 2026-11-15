// FILE: u0053_test.cc
#include <algorithm>
#include <array>
#include <cstddef>
#include <iterator>
#include <limits>
#include <memory>
#include <new>
#include <tuple>
#include <type_traits>
#include <utility>

#include "gtest/gtest.h"

#define private public
#include "ceres/internal/fixed_array.h"
#undef private

namespace ceres {
namespace internal {

// P1: START -> 1 -> END
TEST(FixedArrayStorageSizeTest, TC1_P1_Node1_Return) {
  using Array = FixedArray<int, 20>;
  const Array::size_type n = 3;  // n trong [0, 20], chọn với seed cố định
  Array::allocator_type alloc;
  Array::Storage storage(n, alloc);
  storage.size();
}

}  // namespace internal
}  // namespace ceres
